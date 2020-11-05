#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>

int main(){

        key_t shm_key = IPC_PRIVATE;
 	int ds_shm = shmget(shm_key, sizeof(int),IPC_CREAT|0664);
 	
 	if(ds_shm < 0) { 
 		perror("errore shmget!");
 		exit(1); 
 	}

 	int * p = (int*) shmat(ds_shm, NULL, 0);
 	if(p==(void*)-1) { 
 		perror("errore shmget!");
 		exit(1); 
 	}

        printf("Dettagli shared memory creata:\n");
        printf("...chiave IPC shm: %d\n", shm_key);
        printf("...descrittore shm: %d\n", ds_shm);
        printf("...indirizzo dopo attach: %p\n", p);

 	key_t pid = fork();
 	if(pid==0) {
    	        // processo figlio
    	        *p = 123;
    	        exit(0);
 	} else if (pid > 0) {
    	        // processo padre
    	        wait(NULL);
    	        printf("Contenuto SHM: %d\n", *p);
 	}

        shmctl(ds_shm, IPC_RMID, NULL);

        return 0;
}
