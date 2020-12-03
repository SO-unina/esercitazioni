#include <stdio.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include "header.h"


void Produci(struct ProdCons *pc, msg m){

        //enter monitor -> enter_monitor(rif_mon)
        
        pthread_mutex_lock(&pc->mutex);

        //if(pc->ok_produzione==0){
        while(pc->ok_produzione == 0){
                pthread_cond_wait(&pc->ok_prod_cv, &pc->mutex);
        }

        //prod
        pc->mess = m;

        //update var cond
        pc->ok_produzione = 0;
        pc->ok_consumo = 1;

        //signal i consumatori
        //
        pthread_cond_signal(&pc->ok_cons_cv);

        //leave monitor
        pthread_mutex_unlock(&pc->mutex);

}

void Consuma(struct ProdCons *pc, msg m){


        pthread_mutex_lock(&pc->mutex);

        while(pc->ok_consumo == 0){
                pthread_cond_wait(&pc->ok_cons_cv, &pc->mutex);
        }

        printf("val cons: %d\n", pc->mess);

        pc->ok_produzione = 1;
        pc->ok_consumo = 0;

        pthread_cond_signal(&pc->ok_prod_cv);

        pthread_mutex_unlock(&pc->mutex);
}

void *Produttore (void *p){

        struct ProdCons *pc = (struct ProdCons *)p;

        int i;
        for (i=0; i<3; i++){
        
                struct timeval t1;
                struct timezone t2;

                gettimeofday(&t1, &t2);

                msg m = t1.tv_usec;

                Produci(pc, m);

        }

        pthread_exit(0);
}

void *Consumatore (void *p){

        struct ProdCons *pc = (struct ProdCons *)p;

        for (i=0; i<3; i++){
        
        
        
                msg m = Consuma(pc);
        
        }
        
        pthread_exit(0);
}
