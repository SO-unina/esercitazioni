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


void produttore(struct prodcons *p, int ds_sem){


        int indice = 0;

        Wait_Sem(ds_sem, SPAZIO_DISPONIBILE);

        Wait_Sem(ds_sem, MUTEX_P);

        while(indice <= DIM_BUFFER && p->stato[indice] != BUFFER_VUOTO)
                indice++;

        p->stato[indice] = BUFFER_INUSO;

        Signal_Sem(ds_sem, MUTEX_P);

        ///PRODUZIONE FUORI DALLA SEZ. CRITICA!!!!!!!!!!!!
        p->buffer[indice] = rand() % 100;

        printf("val prod : %d\n", p->buffer[indice]);
       
        p->stato[indice] = BUFFER_PIENO;
      
        Signal_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
}

void consumatore(struct prodcons *p, int ds_sem){


        int indice = 0;

        Wait_Sem(ds_sem, MESSAGGIO_DISPONIBILE);

        Wait_Sem(ds_sem, MUTEX_C);

        while (indice<= DIM_BUFFER && p->stato[indice] != BUFFER_PIENO)
                indice++;

        p->stato[indice] = BUFFER_INUSO;

        Signal_Sem(ds_sem, MUTEX_C);

        //cons
        //
        sleep(2);

        printf("val consumato: %d\n", p->buffer[indice]);

        p->stato[indice] = BUFFER_VUOTO;

        Signal_Sem(ds_sem, SPAZIO_DISPONIBILE);

}
