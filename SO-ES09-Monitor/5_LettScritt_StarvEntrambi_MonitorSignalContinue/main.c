#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

#include "procedure.h"

#define NUM_LETTORI 3
#define NUM_SCRITTORI 3

#define LETTURE 3
#define SCRITTURE 2

int main() {

	key_t chiave_shm = IPC_PRIVATE;

	int id_shm = shmget( chiave_shm, sizeof(struct LettScritt), IPC_CREAT|0664);

	if( id_shm < 0 ) {
		perror("errore shm");
		exit(1);
	}


	struct LettScritt * ls = shmat( id_shm, NULL, 0);

	if( ls == (void*)-1 ) {
		perror("errore shmat");
		exit(1);
	}


	init_monitor( &(ls->m), 2 );

	ls->numero_lettori = 0;
	ls->numero_scrittori = 0;



	pid_t pid;


	int j;
	for(j=0; j<NUM_LETTORI; j++) {

		pid = fork();

		if( pid == 0 ) {

			// figlio lettore

			printf("Inizio lettore\n");



			int k;

			for(k=0; k<LETTURE; k++) {

				int valore = Leggi( ls );

				sleep(1);
			}

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

			// figlio scrittore

			printf("Inizio scrittore\n");

			srand(time(NULL)*getpid());



			sleep(1);

			int k;

			for(k=0; k<SCRITTURE; k++) {

				int valore = rand() % 10;

				Scrivi(ls, valore);

				sleep(2);
			}

			exit(0);
		}
	}


	for(j=0; j<NUM_LETTORI+NUM_SCRITTORI; j++)
		wait(NULL);


	remove_monitor( &(ls->m) );

	shmctl( id_shm, IPC_RMID, 0);

}





