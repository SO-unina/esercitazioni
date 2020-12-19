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
        coda_risultati = msgget(IPC_PRIVATE, IPC_CREAT | 0664);
        printf("Coda coda_risultati create con desc: %d\n", coda_risultati);
    
        initServiceQueues();
            
        //creazione di una istanza di struttura monitor per operandi e per risultati
        // MonitorOperandi sarà usato dai thread generazione operandi
        MonitorOperandi * pc_op = malloc(sizeof(MonitorOperandi));
    
        //inizializzazione mutex e condition
        pthread_mutex_init(&pc_op->mutex,NULL);
    
        pthread_cond_init(&pc_op->ok_prod_operandi_cv,NULL);
        pthread_cond_init(&pc_op->ok_cons_operandi_cv,NULL);
    
        //inizializzazione delle variabili di stato
        pc_op->testa_operandi = 0;
        pc_op->coda_operandi = 0;
        pc_op->contatore_operandi = 0;
    
        //impostazione dei thread come joinable
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);	

        // genero processo prelievo risultati
        pid_t pid;
        pid = fork();
        if (pid == 0){
            printf("Processo prelievo risultati creato...PID: %d\n", getpid());
            //processo prelievo risultati
            preleva_risultati(coda_risultati);
        }
    
        // genero thread generazione operandi
        int k;
        for (k=0; k<NUM_THREADS_OPERANDI; k++)
                pthread_create(&threads_operandi[k], &attr, genera_operandi, (void *)pc_op);    
    
        // genero thread di calcolo
        
        for (k=0; k<NUM_THREADS_CALCOLO; k++) {

            printf("Sono il thread di calcolo, id %d\n", k);
            pthread_create(&threads_calcolo[k], &attr, calcola, (void *)pc_op);
            
        }

        for (k=0; k<NUM_THREADS_OPERANDI; k++) {
                pthread_join(threads_operandi[k], NULL);
                printf ("Thread gen operandi #%d terminato\n", k);
        }
    
        wait(NULL);
        printf ("Processo prelievo risultati terminato\n");

        for (k=0; k<NUM_THREADS_CALCOLO; k++){
                pthread_join(threads_calcolo[k], NULL);
                printf ("Thread di calcolo n.ro %d teriminato\n ", k);
        }

        /*deallocazione risorse*/	
        pthread_attr_destroy(&attr);
        pthread_mutex_destroy(&pc_op->mutex);
    
        pthread_cond_destroy(&pc_op->ok_prod_operandi_cv);
        pthread_cond_destroy(&pc_op->ok_cons_operandi_cv);
    
        free(pc_op);
    
        msgctl(coda_risultati, IPC_RMID, 0);
    
        removeServiceQueues();
    
        pthread_exit(0);
}

