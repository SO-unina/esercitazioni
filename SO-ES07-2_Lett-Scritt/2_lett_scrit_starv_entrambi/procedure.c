			/*------IMPLEMENTAZIONE DELLE PROCEDURE--------*/

#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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
	
        Wait_Sem(sem,MUTEXS); //Indica agli scrittori che sto iniziando a scrivere, incremento
                                // numscrittori in mutua esclusione
        buf->numscrittori = buf->numscrittori + 1;
        
	    if (buf->numscrittori == 1) // se si tratta del primo scrittore blocca i lettori
            Wait_Sem(sem, SYNCH);

        Signal_Sem(sem,MUTEXS); //Rilascia il mutex per far entrare altri scrittori per potersi mettere in attesa
        Wait_Sem(sem,MUTEX); //Blocco eventuali scrittori per la scrittura vera e propria
}

void FineScrittura(int sem, Buffer* buf){

        Signal_Sem(sem,MUTEX); //Rilascio il mutex per gli scrittori che devono scrivere
        Wait_Sem(sem,MUTEXS); //Indica agli scrittori che sto terminando la scrittura, decremento
                                // numscrittori in mutua esclusione
        buf->numscrittori = buf->numscrittori - 1;

        if (buf->numscrittori == 0) //se sono l'ultimo scrittore devo rilasciare la risorsa per i lettori
     		Signal_Sem(sem, SYNCH);

        Signal_Sem(sem,MUTEXS); //rilascio il mutex per altri scrittori che vogliono iniziare la scrittura
}



void Scrittore(int sem, Buffer *buf){

	InizioScrittura(sem,buf);

        struct timeval t1;
    	struct timezone t2;
 	gettimeofday(&t1,&t2);    //valore diverso ad ogni scrittura
    	buf->messaggio =t1.tv_usec;
	sleep(1);
    	printf("Valore scritto: <%ld> \n", buf->messaggio);

        FineScrittura(sem,buf);
}

void Lettore (int sem, Buffer* buf) {

	InizioLettura(sem,buf);

	/*********Lettura********/
	sleep(1); // per simulare un ritardo di lettura
        printf("Valore letto=<%ld>, numero lettori=%d \n", buf->messaggio, buf->numlettori);
	
        FineLettura(sem,buf);
}


