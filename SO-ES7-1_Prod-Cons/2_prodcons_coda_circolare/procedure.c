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
    
    //printf("produttore è fermo prima di wait\n");
    Wait_Sem(ds_sem, SPAZIO_DISPONIBILE);
    //printf("produttore si sblocca dopo la wait\n");
    
    
    Wait_Sem(ds_sem, MUTEX_P);
    
    
    sleep(2);
    
    // genera valore tra 0 e 99
    p->buffer[p->testa] = rand() % 100;
    
    printf("Il valore prodotto = %d\n", p->buffer[p->testa]);
    
    p->testa = (p->testa+1) % DIM_BUFFER;
    
    
    Signal_Sem(ds_sem, MUTEX_P);
    
    Signal_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
}

void consumatore(struct prodcons * p, int ds_sem) {
    
    //printf("consumatore è fermo prima di wait\n");
    Wait_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
    //printf("consumatore si sblocca dopo la wait\n");
    
    Wait_Sem(ds_sem, MUTEX_C);
    
    
    sleep(2);
    
    printf("Il valore consumato = %d\n", p->buffer[p->coda]);
    
    p->coda = (p->coda + 1) % DIM_BUFFER;
    
    
    Signal_Sem(ds_sem, MUTEX_C);
    
    Signal_Sem(ds_sem, SPAZIO_DISPONIBILE);
}
