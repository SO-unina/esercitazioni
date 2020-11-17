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

int main(){

        
        key_t chiave = IPC_PRIVATE;
        

        int ds_shm = shmget(chiave, sizeof(int), IPC_CREAT | 0664);

        if (ds_shm<0){
        
                perror("err shm");
                exit(1);
        }

        int *p;

        p =  (int *) shmat(ds_shm, 0, 0);

        key_t chiavesem = IPC_PRIVATE;

        int ds_sem = semget(chiavesem, 2, IPC_CREAT | 0664);

        if (ds_sem < 0){
                perror("err sem");
                exit(1);

        }

        *p = 0;

        semctl(ds_sem, SPAZIO_DISPONIBILE, SETVAL, 1);
        semctl(ds_sem, MESSAGGIO_DISPONIBILE, SETVAL, 0);

        int pid = fork();

        if (pid == 0){
        
                printf("Sono il consumatore\n");
                consumatore(p, ds_sem);
                exit(1);
        }

        pid = fork();

        if (pid == 0){
 
                printf("Sono il produttore\n");
                produttore(p, ds_sem);
                exit(1);
        }

        wait(NULL);
        wait(NULL);

        //rimozione delle strutture semaforiche
        //rimozione della shm
        //


        return 0;
}
