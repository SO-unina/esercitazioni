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

void produttore(int *p, int ds_sem){

        Wait_Sem(ds_sem, SPAZIO_DISPONIBILE);

        //inizio sez. crit
        *p = rand() % 100;
        //fine sez. crit
        printf("valore prod: %d\n", *p);

        Signal_Sem(ds_sem, MESSAGGIO_DISPONIBILE);

}

void consumatore(int *p, int ds_sem){

        Wait_Sem(ds_sem, MESSAGGIO_DISPONIBILE);

        sleep(2);
        printf("Il valore consumato è: %d\n", *p);

        Signal_Sem(ds_sem, SPAZIO_DISPONIBILE);

}
