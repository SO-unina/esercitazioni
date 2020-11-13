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


void produttore(int * p, int ds_sem) {

	printf("produttore è fermo prima di wait\n");
	Wait_Sem(ds_sem, SPAZIO_DISPONIBILE);
	printf("produttore si sblocca dopo la wait\n");


	sleep(2);

	*p = rand() % 100;

	printf("Il valore prodotto = %d\n", *p);


	Signal_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
}

void consumatore(int * p, int ds_sem) {

	printf("consumatore è fermo prima di wait\n");
	Wait_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
	printf("consumatore si sblocca dopo la wait\n");


	sleep(2);
	printf("Il valore consumato = %d\n", *p);


	Signal_Sem(ds_sem, SPAZIO_DISPONIBILE);
}
