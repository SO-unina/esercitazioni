#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "header.h"


void generatore_produttore(struct ProdConsGen *pc){
        
    enter_monitor( &(pc->m) );

    printf("[generatore_produttore] Ingresso monitor - produzione\n");

    while( pc->num_elementi == DIM_QUEUE ) {
        wait_condition( &(pc->m), VARCOND_GEN_PRODUTTORI );
    }

    //produzione del messaggio
    
    // setto il tipo
    pc->msg[pc->testa].type = MSG_TYPE;
    
    int i;
    // popolo la stringa
    for (i=0; i<STRING_MAX_DIM-1; i++)
            pc->msg[pc->testa].stringa[i] = 'a' + (rand() % 26);

    pc->msg[pc->testa].stringa[STRING_MAX_DIM-1] = '\0';
    
    // popolo i due array
    for(i=0; i<INT_MAX_DIM; i++){
            pc->msg[pc->testa].array[i] = rand() % 9;
    }
    
    // inizializzo a 0 la var
    pc->msg[pc->testa].var = 0;
    
    printf("[generatore_produttore] Messaggio generato!\n");
    printf("[generatore_produttore] ...............msg1.stringa: %s\n", pc->msg[pc->testa].stringa);
    printf("[generatore_produttore] ...............msg1.array[0]: %d\n", pc->msg[pc->testa].array[0]);
    printf("[generatore_produttore] ...............msg1.array[1]: %d\n", pc->msg[pc->testa].array[1]);
    printf("[generatore_produttore] ...............msg1.var: %d\n", pc->msg[pc->testa].var);

    //update puntatore di testa
    pc->testa = (pc->testa+1) % DIM_QUEUE;
    pc->num_elementi++;
    
    //segnalo i generatori consumatori
    signal_condition( &(pc->m), VARCOND_GEN_CONSUMATORI );

    leave_monitor( &(pc->m) );
    
}

void generatore_consumatore(struct ProdConsGen *pc, int ds_queue_gen_filter){

    enter_monitor( &(pc->m) );

    while( pc->num_elementi == 0 ) {
        wait_condition( &(pc->m), VARCOND_GEN_CONSUMATORI );
    }
    
    //consumo (faccio una print) il messaggio e mando sulla coda ds_queue_gen_filter
    
    printf("[generatore_consumatore] Messaggio CONSUMATO!\n");
    printf("[generatore_consumatore] ...............msg1.stringa: %s\n", pc->msg[pc->coda].stringa);
    printf("[generatore_consumatore] ...............msg1.array[0]: %d\n", pc->msg[pc->coda].array[0]);
    printf("[generatore_consumatore] ...............msg1.array[1]: %d\n", pc->msg[pc->coda].array[1]);
    printf("[generatore_consumatore] ...............msg1.var: %d\n", pc->msg[pc->coda].var);
    
    int ret = msgsnd(ds_queue_gen_filter, &(pc->msg[pc->coda]), sizeof(message) - sizeof(long), 0);
    if (ret<0){
            perror("msgsnd del messaggio on ds_queue_gen_filter FALLITA!");
            exit(-1);
    }
    printf("[generatore_consumatore] Messaggio INVIATO!\n");
    
    //update puntatore di testa
    pc->coda = (pc->coda + 1) % DIM_QUEUE;
    pc->num_elementi--;
    
    //segnalo i generatori consumatori
    signal_condition( &(pc->m), VARCOND_GEN_PRODUTTORI );

    leave_monitor( &(pc->m) );

}

