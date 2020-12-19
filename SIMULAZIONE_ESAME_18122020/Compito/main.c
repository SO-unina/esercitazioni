#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>

#include "header.h"

int coda_risultati;

#define NUM_THREADS_OPERANDI    2
#define NUM_THREADS_CALCOLO     3

int main(){

        pthread_attr_t attr;
        pthread_t threads_operandi[NUM_THREADS_OPERANDI];
        pthread_t threads_calcolo[NUM_THREADS_CALCOLO];

        srand(time(NULL)*getpid());

        // Creazione coda risultati
        coda_risultati = /* TBD */
        printf("Coda coda_risultati create con desc: %d\n", coda_risultati);
    
        initServiceQueues();
            
        //creazione di una istanza di struttura monitor per gli operandi
        // MonitorOperandi sarà usato dai thread generazione operandi
        MonitorOperandi * pc_op = /* TBD */
    
        //inizializzazione mutex e condition
        /* TBD */
    
        //inizializzazione delle variabili di stato
    
        /* TBD */
    
        //impostazione dei thread come joinable
        /* TBD */
    
        // genero processo prelievo risultati
    
        /* TBD */
    
        // genero thread generazione operandi
        /* TBD */
    
        // genero thread di calcolo
        /* TBD */
    
        /* TBD:  Join threads a wait processo*/
    
    
        /*deallocazione risorse*/	
        /* TBD */
    
        pthread_exit(NULL);
}

