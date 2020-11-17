#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

#include "procedure.h"



int main() {


	key_t chiave = IPC_PRIVATE;

	int ds_shm = shmget(chiave, sizeof(struct prodcons), IPC_CREAT|0664);

	if(ds_shm<0) { perror("SHM errore"); exit(1); }

	struct prodcons * p;

	p = (struct prodcons *) shmat(ds_shm, NULL, 0);


	for(int i=0; i<DIM_BUFFER; i++) {
		p->stato[i] = BUFFER_VUOTO;
	}



	key_t chiavesem = IPC_PRIVATE;

	int ds_sem = semget(chiavesem, 4, IPC_CREAT|0664);

	if(ds_sem<0) { perror("SEM errore"); exit(1); }

	
    //SEMAFORI COOPERAZIONE tra i prod e i cons
	semctl(ds_sem, SPAZIO_DISPONIBILE, SETVAL, DIM_BUFFER);
	semctl(ds_sem, MESSAGGIO_DISPONIBILE, SETVAL, 0);

    //SEMAFORI COMPETIZIONE tra i prod e i cons
	semctl(ds_sem, MUTEX_C, SETVAL, 1);
	semctl(ds_sem, MUTEX_P, SETVAL, 1);



	for(int i=0; i<NUM_CONSUMATORI; i++) {

		int pid = fork();

		if(pid==0) {

			//figlio consumatore

			printf("Inizio figlio consumatore\n");

			// NOTA: il generatore di numeri pseudo-casuali
			// viene inizializzato in modo diverso per ogni
			// processo (usando il valore del PID e il tempo)
			srand(getpid()*time(NULL));

			consumatore(p, ds_sem);

			exit(1);
		}
	}




	for(int i=0; i<NUM_PRODUTTORI; i++) {

		int pid = fork();

		if(pid==0) {

			//figlio produttore

			printf("Inizio figlio produttore\n");

			// NOTA: il generatore di numeri pseudo-casuali
			// viene inizializzato in modo diverso per ogni
			// processo (usando il valore del PID e il tempo)
			srand(getpid()*time(NULL));

			produttore(p, ds_sem);

			exit(1);
		}
	}



	for(int i=0; i<NUM_PRODUTTORI; i++) {
		wait(NULL);
		printf("Figlio produttore terminato\n");
	}

	for(int i=0; i<NUM_CONSUMATORI; i++) {
		wait(NULL);
		printf("Figlio consumatore terminato\n");
	}
        
        shmctl(ds_shm, IPC_RMID, NULL);
        semctl(ds_sem, 0, IPC_RMID);

        return 0;

}
