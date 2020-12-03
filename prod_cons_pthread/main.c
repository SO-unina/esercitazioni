#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include "header.h"

int main(){

        pthread_attr_t attr;
        pthread_t threads[NUM_THREADS];

        struct ProdCons *pc = malloc(sizeof(struct ProdCons));

        pthread_mutex_init(&pc->mutex, NULL);
        pthread_cond_init(&pc->ok_prod_cv, NULL);
        pthread_cond_init(&pc->ok_cons_cv, NULL);

        pc->ok_produzione = 1;
        pc->ok_consuma = 0;

        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

        int k;
        for (k=0; k<NUM_THREADS; k++){
                
                if(k%2){
                        pthread_create(&threads[k], &attr, Consumatore, (void *)pc);
                }
                else{
                        pthread_create(&threads[k], &attr, Produttore, (void *)pc);
                        
                }

        }

        for (k=0; k<NUM_THREADS; k++){
                pthread_join(threads[k], NULL);
        }

        pthread_attr_destroy(&attr);
        pthread_mutex_destroy(...)
        pthread_cond_destroy(...)
        pthread_cond_destroy(...)

        free(pc);

        pthread_exit(NULL);
}
