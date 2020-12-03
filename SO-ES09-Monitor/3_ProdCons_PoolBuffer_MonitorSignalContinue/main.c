#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

#include "procedure.h"


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

	pc->numero_liberi = DIM;
	pc->numero_occupati = 0;

	int i;
	for(i = 0; i<DIM; i++) {
		pc->stato[i] = LIBERO;
	}


	pid_t pid;


	int j;
	for(j=0; j<2; j++) {

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





	for(j=0; j<2; j++) {


		pid = fork();
		
		if( pid == 0 ) {
			// figlio produttore
			printf("Inizio produttore\n");

			sleep(5);

			srand(time(NULL)*getpid());

			int valore = rand() % 10;

			Produci( pc, valore);

			printf("Produzione: %d\n", valore);
			
			exit(0);
		}
	}


	for(j=0; j<4; j++)
		wait(NULL);


	remove_monitor( &(pc->m) );

	shmctl( id_shm, IPC_RMID, 0);

}





