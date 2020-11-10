#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

#define SPAZIO_DISPONIBILE 0
#define MESSAGGIO_DISPONIBILE 1
#define MUTEX_P 2
#define MUTEX_C 3

#define DIM_BUFFER 3

#define NUM_PRODUTTORI 5
#define NUM_CONSUMATORI 5

#define BUFFER_VUOTO 0
#define BUFFER_INUSO 1
#define BUFFER_PIENO 2


struct prodcons {
	int buffer[DIM_BUFFER];
	int stato[DIM_BUFFER];
};


void Wait_Sem(int semid, int semnum) {
	struct sembuf s;

	s.sem_flg = 0;
	s.sem_num = semnum;	// SPAZIO_DISPONIBILE oppure MESS_DISP
	s.sem_op = -1;

	int r = semop(semid, &s, 1);
	
	if(r<0) { perror("ERRORE signal"); }
}


void Signal_Sem(int semid, int semnum) {
	struct sembuf s;

	s.sem_flg = 0;
	s.sem_num = semnum;
	s.sem_op = 1;

	int r = semop(semid, &s, 1);

	if(r<0) { perror("ERRORE signal"); }
}



void produttore(struct prodcons * p, int ds_sem) {

	int indice = 0;


	Wait_Sem(ds_sem, SPAZIO_DISPONIBILE);


	Wait_Sem(ds_sem, MUTEX_P);

	while(indice <= DIM_BUFFER && p->stato[indice] != BUFFER_VUOTO) {
		indice++;
	}

	p->stato[indice] = BUFFER_INUSO;

    //qui devo rilasciare il mutex per i produttori...ERRORE se non lo faccio!!!!
	Signal_Sem(ds_sem, MUTEX_P);


	sleep(2);

	// genera valore tra 0 e 99
	p->buffer[indice] = rand() % 100;

	printf("Il valore prodotto = %d\n", p->buffer[indice]);


	p->stato[indice] = BUFFER_PIENO;

	Signal_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
}

void consumatore(struct prodcons * p, int ds_sem) {

	int indice = 0;


	Wait_Sem(ds_sem, MESSAGGIO_DISPONIBILE);


	Wait_Sem(ds_sem, MUTEX_C);

	while(indice <= DIM_BUFFER && p->stato[indice] != BUFFER_PIENO) {
		indice++;
	}

	p->stato[indice] = BUFFER_INUSO;

    //qui devo rilasciare il mutex per i consumatori...ERRORE se non lo faccio!!!!
	Signal_Sem(ds_sem, MUTEX_C);


	sleep(2);

	printf("Il valore consumato = %d\n", p->buffer[indice]);


	p->stato[indice] = BUFFER_VUOTO;

	Signal_Sem(ds_sem, SPAZIO_DISPONIBILE);
}

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


}
