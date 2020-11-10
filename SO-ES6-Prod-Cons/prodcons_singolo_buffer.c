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

int main() {


	srand(time(NULL));

	key_t chiave = IPC_PRIVATE;

	int ds_shm = shmget(chiave, sizeof(int), IPC_CREAT|0664);

	if(ds_shm<0) { perror("SHM errore"); exit(1); }

	int * p;

	p = (int *) shmat(ds_shm, NULL, 0);



	key_t chiavesem = IPC_PRIVATE;

	int ds_sem = semget(chiavesem, 2, IPC_CREAT|0664);

	if(ds_sem<0) { perror("SEM errore"); exit(1); }

	
	*p=0;

    //SEMAFORI COOPERAZIONE tra 1 prod e 1 cons: NO COMPETIZIONE
	semctl(ds_sem, SPAZIO_DISPONIBILE, SETVAL, 1);
	semctl(ds_sem, MESSAGGIO_DISPONIBILE, SETVAL, 0);



	int pid = fork();

	if(pid==0) {
		//figlio consumatore

		printf("Inizio figlio consumatore\n");
		consumatore(p, ds_sem);
		exit(1);
	}


	pid = fork();

	if(pid==0) {
		//figlio produttore

		printf("Inizio figlio produttore\n");
		produttore(p, ds_sem);
		exit(1);
	}



	wait(NULL);
	printf("primo figlio terminato\n");

	wait(NULL);
	printf("secondo figlio terminato\n");


}
