#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

#include "procedure.h"
#include "semafori.h"


void produttore(struct prodcons * p, int ds_sem) {
    
    int indice = 0;
    
    
    Wait_Sem(ds_sem, SPAZIO_DISPONIBILE);
    
    
    Wait_Sem(ds_sem, MUTEX_P);
    
    while(indice <= DIM_BUFFER && p->stato[indice] != BUFFER_VUOTO) {
        indice++;
    }
    
    p->stato[indice] = BUFFER_INUSO;
    
    //qui devo rilasciare il mutex per i produttori...ERRORE se non lo faccio!!!!
    Signal_Sem(ds_sem, MUTEX_P);
    
    
    sleep(2);
    
    // genera valore tra 0 e 99
    p->buffer[indice] = rand() % 100;
    
    printf("Il valore prodotto = %d\n", p->buffer[indice]);
    
    
    p->stato[indice] = BUFFER_PIENO;
    
    Signal_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
}

void consumatore(struct prodcons * p, int ds_sem) {
    
    int indice = 0;
    
    
    Wait_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
    
    
    Wait_Sem(ds_sem, MUTEX_C);
    
    while(indice <= DIM_BUFFER && p->stato[indice] != BUFFER_PIENO) {
        indice++;
    }
    
    p->stato[indice] = BUFFER_INUSO;
    
    //qui devo rilasciare il mutex per i consumatori...ERRORE se non lo faccio!!!!
    Signal_Sem(ds_sem, MUTEX_C);
    
    
    sleep(2);
    
    printf("Il valore consumato = %d\n", p->buffer[indice]);
    
    
    p->stato[indice] = BUFFER_VUOTO;
    
    Signal_Sem(ds_sem, SPAZIO_DISPONIBILE);
}
