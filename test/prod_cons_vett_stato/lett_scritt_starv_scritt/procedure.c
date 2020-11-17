			/*-----IMPLEMENTAZIONE DELLE PROCEDURE-------*/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"
#include "semafori.h"


void InizioScrittura(int sem){

        Wait_Sem(sem, MUTEXS);
        buf->numscrittori = buf->numscrittori + 1;

        if (buf->numscrittori == 1)
                Wait_Sem(sem, SYNCH)

        Signal_Sem(sem, MUTEXS);

        Wait_Sem(sem, MUTEX);
}

void FineScrittura(int sem){

        Signal_Sem(sem, MUTEX);
        
        Wait_Sem(sem, MUTEXS);

        buf->numscrittori = buf->numscrittori - 1;

        if (buf->numscrittori == 0)
                Signal_Sem(sem, SYNCH);

        Signal_Sem(sem, MUTEXS);
}

void Scrittore(int sem, Buffer *buf){

        InizioScrittura(sem);

        struct timeval t1;
        struct timezone t2;
        gettimeofday(&t1, &t2); //per avere un valore diverso ad ogni produzione

        msg val = t1.tv_usec;
        buf->messaggio = val;

        FineScrittura(sem);
}


void InizioLettura(int sem, Buffer *buf){

        Wait_Sem(sem, MUTEXL);
        
        buf->numlettori = buf->numlettori + 1;

        if (buf->numlettori == 1)
                Wait_Sem(sem, SYNCH);

        Signal_Sem(sem, MUTEXL);
}

void FineLettura(int sem, Buffer *buf){

        Wait_Sem(sem, MUTEXL);
        buf->numlettori = buf->numlettori - 1;

        if (buf->numlettori == 0)
                Signal_Sem(sem, SYNCH);

        Signal_Sem(sem, MUTEXL);
}

void Lettore(int sem, Buffer *buf){

        InzioLettura(sem, buf);

        printf("LEggo %d\n", buf->messaggio);

        FineLettura(sem, buf);
}
