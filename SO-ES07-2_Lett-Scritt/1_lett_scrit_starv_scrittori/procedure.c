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

/*********PROCEDURE DI LETTURA E SCRITTURA*********/

void InizioLettura(int sem, Buffer* buf){
    
    Wait_Sem(sem, MUTEXL); //Indica ai lettori che sto iniziando a leggere, incremento
    // numlettori in mutua esclusione
    buf->numlettori = buf->numlettori + 1;
    
    if (buf->numlettori == 1) //se si tratta del primo lettore blocca gli scrittori
        Wait_Sem(sem, SYNCH);
    
    Signal_Sem(sem, MUTEXL); //Rilascia il mutex per far entrare altri lettori
}

void FineLettura(int sem, Buffer* buf){
    
    Wait_Sem(sem, MUTEXL); //Indica ai lettori che sto terminando la lettura, decremento
    // numlettori in mutua esclusione
    buf->numlettori = buf->numlettori - 1;
    
    if (buf->numlettori == 0) //se sono l'ultimo lettore devo rilasciare la risorsa per gli scrittori
        Signal_Sem(sem, SYNCH);
    
    Signal_Sem(sem, MUTEXL); //rilascio il mutex per altri lettori
}


void InizioScrittura(int sem){
	Wait_Sem(sem, SYNCH);
}


void FineScrittura (int sem){
	Signal_Sem(sem, SYNCH);
}


void Scrittore(int sem, Buffer* buf) {

        InizioScrittura(sem);

        /*********Scrittura********/
        struct timeval t1;
        struct timezone t2;
        gettimeofday(&t1, &t2); //per avere un valore diverso ad ogni produzione
        msg val = t1.tv_usec;
        buf->messaggio = val;
        sleep(1);
        printf("Valore scritto=<%ld> \n", buf->messaggio);

        FineScrittura(sem);
}


void Lettore (int sem, Buffer* buf) {

        InizioLettura(sem, buf);

        /*********Lettura********/
        sleep(1); // per simulare un ritardo di lettura
        printf("Valore letto=<%ld>, numero lettori=%d \n", buf->messaggio, buf->numlettori);
        
        FineLettura(sem, buf);
}

