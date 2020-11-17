#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

#include "semafori.h"
#include "procedure.h"

int main() {


	srand(time(NULL));

	key_t chiave = IPC_PRIVATE;

	int ds_shm = shmget(chiave, sizeof(int), IPC_CREAT|0664);

	if(ds_shm<0) { perror("SHM errore"); exit(1); }

	int * p;

	p = (int *) shmat(ds_shm, NULL, 0);



	key_t chiavesem = IPC_PRIVATE;

	int ds_sem = semget(chiavesem, 2, IPC_CREAT|0664);

	if(ds_sem<0) { perror("SEM errore"); exit(1); }

	
	*p=0;

    //SEMAFORI COOPERAZIONE tra 1 prod e 1 cons: NO COMPETIZIONE
	semctl(ds_sem, SPAZIO_DISPONIBILE, SETVAL, 1);
	semctl(ds_sem, MESSAGGIO_DISPONIBILE, SETVAL, 0);



	int pid = fork();

	if(pid==0) {
		//figlio consumatore

		printf("Inizio figlio consumatore\n");
		consumatore(p, ds_sem);
		exit(1);
	}


	pid = fork();

	if(pid==0) {
		//figlio produttore

		printf("Inizio figlio produttore\n");
		produttore(p, ds_sem);
		exit(1);
	}



	wait(NULL);
	printf("primo figlio terminato\n");

	wait(NULL);
	printf("secondo figlio terminato\n");

        shmctl(ds_shm, IPC_RMID, NULL);
       	semctl(ds_sem, 0, IPC_RMID);
        
        return 0;
}
