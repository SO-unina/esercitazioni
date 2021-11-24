#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "header.h"


int main(){

    /************DICHIARAZIONE DELLE VARIABILI***************/

    int id_sem, id_shared, id_shared_str, k, numsem;
    key_t chiave_shm_buf = ftok(".", 'a');
    key_t c_sem = ftok(".", 'c');
    int status, numprocessi;
    pid_t pid;
    Buffer *buf;

    int num_processi = 4;

    //richiesta del buffer
    id_shared = shmget(chiave_shm_buf, sizeof(Buffer), IPC_CREAT | 0664);
    printf("id_shared = %d\n", id_shared);
    buf = (Buffer *) (shmat(id_shared, 0, 0));

    srand(time(NULL)*getpid());

    int len = 10 + rand() % 5;
    char arg[10];
    sprintf(arg, "%d", len);

    buf->numlettori = 0;

    //richiesta di due semafori ed inizializzazione
    id_sem = semget(c_sem, 2, IPC_CREAT | 0664);
    semctl(id_sem, MUTEXL, SETVAL, 1);
    semctl(id_sem, SYNCH, SETVAL, 1);

    //generazione di scrittori e lettori
    pid = fork();

    if (pid == 0) {                //processo figlio
        execl("./generatore", "generatore", arg, NULL);
        perror("Errore nella execl elaboratore");
        exit(-1);
        
    }

    pid = fork();

    if (pid == 0) {                //processo figlio
        execl("./elaboratore", "elaboratore", arg, NULL);
        perror("Errore nella execl elaboratore");
        exit(-1);
    
    }


    pid = fork();

    if (pid == 0) {                //processo figlio
        execl("./analizzatore", "analizzatore", arg, NULL);
        perror("Errore nella execl elaboratore");
        exit(-1);
    
    }
    
    pid = fork();

    if (pid == 0) {                //processo figlio
        execl("./analizzatore", "analizzatore", arg, NULL);
        perror("Errore nella execl elaboratore");
        exit(-1);
    
    }

    
    
    for (k=0; k<num_processi; k++){
        pid = wait(&status);
        if (pid == -1)
            perror("errore");
        else
            printf ("Figlio n.ro %d e\' morto con status= %d \n ", pid, status);
    }
    
        /********DEALLOCAZIONE SEMAFORI E MEMORIA CONDIVISA**********/

        //free(buf->stringa);
        printf("Deallocazione risorse IPC...\n");
        shmctl(id_shared, IPC_RMID, 0);
        semctl(id_sem, 0, IPC_RMID);

        return 0;
}
