#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

#include "procedure.h"

#define NUM_PRODUTTORI 1
#define NUM_CONSUMATORI 1


int main() {

	key_t chiave_shm = IPC_PRIVATE;

	int id_shm = shmget( chiave_shm, sizeof(struct ProdCons), IPC_CREAT|0664);

	if( id_shm < 0 ) {
		perror("errore shm");
		exit(1);
	}


	struct ProdCons * pc = shmat( id_shm, NULL, 0);

	if( pc == (void*)-1 ) {
		perror("errore shmat");
		exit(1);
	}


	init_monitor( &(pc->m), 2 );

	pc->buffer_libero = 1;
	pc->buffer_occupato = 0;



	int j;
	pid_t pid;

	for(j=0; j<NUM_CONSUMATORI; j++) {

		pid = fork();

		if( pid == 0 ) {

			// figlio consumatore

			printf("Inizio consumatore\n");

			int valore = Consuma( pc );

			printf("Consumazione: %d\n", valore);

			exit(0);
		}
		else if( pid < 0 ) {
			perror("errore fork");
			exit(1);
		}
	}




	for(j=0; j<NUM_PRODUTTORI; j++) {

		pid = fork();
		
		if( pid == 0 ) {

			// figlio produttore

			printf("Inizio produttore\n");

			sleep(5);

			srand(time(NULL));

			int valore = rand() % 10;

			Produci( pc, valore);

			printf("Produzione: %d\n", valore);
			
			exit(0);
		}
		else if( pid < 0 ) {
			perror("errore fork");
			exit(1);
		}
	}



	for(j=0; j<NUM_CONSUMATORI+NUM_PRODUTTORI; j++) {
		wait(NULL);
	}

	remove_monitor( &(pc->m) );

	shmctl( id_shm, IPC_RMID, 0);

	return 0;
}





