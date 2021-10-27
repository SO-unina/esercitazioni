#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "semafori.h"



int main() {

	key_t k_shmem = IPC_PRIVATE;
	key_t k_sem = IPC_PRIVATE;

	int id_shmem = shmget(k_shmem, sizeof(int), IPC_CREAT|0664);

	if(id_shmem < 0) {
		perror("Errore SHMGET");
		exit(1);
	}


	int id_sem = semget(k_sem, 1, IPC_CREAT|0664); // QUANTI SEMAFORI HO?

	if(id_sem < 0) {
		perror("Errore SEMGET");
		exit(1);
	}


	int * ptr = shmat(id_shmem, 0, 0);

	if(ptr == (void *)-1) {
		perror("Errore SHMAT");
		exit(1);
	}


	semctl(id_sem,0,SETVAL,1);
	printf("SEMAFORO %d INIZIALIZZATO AD 1\n", id_sem);


	*ptr = 0;
	printf("VALORE INIZIALE: %d\n", *ptr);


	int i;
	for(i=0; i<2; i++) {	// CREA 2 PROCESSI FIGLI

		pid_t pid = fork();

		if(pid < 0) {
			perror("Errore FORK");
			exit(1);
		}

		if(pid==0) {
			// PROCESSO FIGLIO
			printf("Process[%d] PID=%d creato\n", i, getpid());
			int j;
			for(j=0; j<100; j++) {

				Wait_Sem(id_sem, 0);

				//INIZIO SEZIONE CRITICA

				int tmp = *ptr;
                                printf("Processo %d ha letto\n", i);
				
                                // CORRETTO: *ptr = tmp + 1;
                                // SBAGLIATO: *ptr++;
                                // SBAGLIATO: *(ptr)++;
                                // CORRETTO: (*ptr)++;

                                *ptr = tmp + 1;

                                printf("Processo %d ha incrementato\n", i);

				//FINE SEZIONE CRITICA

				Signal_Sem(id_sem, 0);

			}

			exit(0);
		}
	}


	for(i=0; i<2; i++) {
		wait(NULL);
	}


	printf("VALORE FINALE: %d\n", *ptr);//Quanto vale il valore finale?

	shmctl(id_shmem,IPC_RMID,0);
	semctl(id_sem,0,IPC_RMID);

	return 0;
}

