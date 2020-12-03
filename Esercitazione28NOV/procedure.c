			/*-----IMPLEMENTAZIONE DELLE PROCEDURE-------*/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"
#include "semafori.h"

//Procedure di inizio e fine lettura

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
    
    Signal_Sem(sem, MUTEXL); //rilascio il mutex per altri lettori che vogliono iniziare la lettura
}

//Procedure di inizio e fine scrittura

void InizioScrittura(int sem, Buffer* buf){
    
    Wait_Sem(sem, SYNCH);
    
}

void FineScrittura(int sem, Buffer* buf){
    
    Signal_Sem(sem, SYNCH);
}
