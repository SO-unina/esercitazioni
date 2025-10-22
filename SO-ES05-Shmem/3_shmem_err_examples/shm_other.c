#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*

ATTENZIONE: questo programma viene eseguito da shm_flags

CASI POSSIBILI:

1) nell'eseguibile shm_flags imposto IPC_PRIVATE come chiave della shm -> questo programma NON potrà accedere alla stessa area di memoria!

	a - se in shm_other imposto IPC_PRIVATE, ottengo un errore di permission denied, perché provo ad accedere ad un'area di memoria privata dell'altro processo
	b - se in shm_other uso ftok (con IPC_CREAT, altrimenti ho errore!!), creo un segmento di memoria A PARTE e nel programma principale shm_flags non vedrò le modifiche apportate da questo programma (NB: p = 555 qui, ma vedrò 222)
	
2) nell'eseguibile shm_flags imposto ftok("./shm_flags", 'k') come chiave della shm -> questo programma POTRA' accedere alla stessa area di memoria!

	a - se qui imposto IPC_PRIVATE, creo un segmento a parte -> le modifiche non si vedranno nel programma principale (NB: *p = 555 qui, ma vedrò 222)
	b - se qui imposto ftok("./shm_flags", 'k') -> condivido correttamente l'area di memoria -> vedrò 555 anche in shm_flags  ##### <----- METODO CORRETTO PER LA CONDIVISIONE

*/

int main(int argc, char * argv[]) {
	/*
	// caso 1.a
	key_t key_shm = IPC_PRIVATE;
	int ds_shm = shmget(key_shm, sizeof(int), 0);
	
	// caso 1.b
	key_t key_shm = ftok("./shm_flags", 'k');													
	int ds_shm = shmget(key_shm, sizeof(int), IPC_CREAT | 0664);		
	
	//caso 2.a	
	key_t key_shm = IPC_PRIVATE;
	int ds_shm = shmget(key_shm, sizeof(int), IPC_CREAT | 0664);	
	*/
	//caso 2.b
	key_t key_shm = ftok("./shm_flags", 'k');													
	int ds_shm = shmget(key_shm, sizeof(int), 0);
						
	
	if (ds_shm < 0) {
		perror("Errore nella creazione del segmento di memoria condiviso"); 
		exit(1);
	}
	
	int * p = (int*) shmat(ds_shm, 0, 0);	// restituisce l'indirizzo di memoria del segmento, altrimenti -1 se c'è errore
	
	if (p == (void*)-1) {
		perror("Errore nel collegamento"); 
		exit(1);
	}				
	
	*p = 555;
	
	printf("[PROCESSO OTHER - %d] Valore della memoria: %d.\n", getpid(), *p);
	
	shmctl(ds_shm, IPC_RMID, 0);	// marca il segmento come "da rimuovere", ma rimuovi solo quando non vi sono più processi collegati
					// restituisce -1 in caso di fallimento

	return 0;
}
