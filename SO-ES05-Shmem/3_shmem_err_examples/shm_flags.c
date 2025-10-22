#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*

POSSIBILI CASI: 

a) IPC_PRIVATE -> solo padre e figli possono accedere al segmento -> altri processi (es: avviati tramite execl) non possono accedervi

b) chiave univoca generata con ftok -> chiunque conosca il valore della chiave può accedere a quel segmento di memoria 				### METODO CORRETTO

c) chiave cablata -> chiunque conosca il valore della chiave può accedere a quel segmento di memoria 


NB: se non uso execl e la memoria è condivisa tra padre e figlio, IPC_PRIVATE e ftok funzionano allo stesso modo!

____________________________________________________________________

1) shmget con solo IPC_CREAT e 0664 - ftok con chiave univoca

	- la memoria non esiste -> viene creata e recuperata -> deve essere fatto l'attach e deve essere inizializzata
	- la memoria esiste già -> viene recuperata automaticamente
	# un errore indica che c'è stato un problema nella creazione/recupero del segmento, MA NON VIENE GENERATO UN ERRORE SE LA MEMORIA ESISTE GIA'
	
2) shmget con IPC_CREAT, IPC_EXCL e 0664 - ftok con chiave univoca

	- la memoria non esiste -> viene creata e recuperata -> deve essere fatto l'attach e deve essere inizializzata
	# un errore indica che la memoria esiste già -> deve essere recuperata (shmget no flag) -> si deve fare l'attach ma non l'inizializzazione
		## un errore nella get indica un problema nel recupero del segmento
		
3) shmget senza flag - ftok con chiave univoca
	- se la memoria esiste, la recupero (vedi caso precedente)
	- se la memoria non esiste -> errore

*/

int main(int argc, char * argv[]) {

	//key_t key_shm = IPC_PRIVATE;
	key_t key_shm = ftok("./shm_flags", 'k'); // chiave univoca
	
	int ds_shm = shmget(key_shm, sizeof(int), IPC_CREAT | IPC_EXCL | 0664);					
	
	int * p;
	
	if (ds_shm < 0) {	// ERRORE: il segmento esiste già
	
		printf("[PROCESSO PADRE (FLAGS) (%d)] Il segmento esiste gia'!\n", getpid());
		ds_shm = shmget(key_shm, sizeof(int), 0);	// devo fare la get senza flag perché la shm esiste già e devo solo recuperarla
		
		if (ds_shm < 0) {
			perror("Errore nella get");
			exit(1);
		}
		
		p = (int*) shmat(ds_shm, 0, 0);	 //faccio la attach ma non inizializzo così da non rimuovere le informazioni già presenti
		if (p == (void*)-1) {
			perror("Errore nel collegamento"); 
			exit(1);
		}
	
	} else { // il segmento non esiste e viene creato
	
		printf("[PROCESSO PADRE (FLAGS) (%d)] Il segmento è stato creato!\n", getpid());
		
		p = (int*) shmat(ds_shm, 0, 0);
		if(p == (void*)-1) {
			perror("Errore nel collegamento");
			exit(1);
		}
		
		*p = 111; // memoria appena creata -> devo collegare e inizializzare
	
	}
				
	printf("\n[PROCESSO PADRE (FLAGS) (%d)] \n", getpid());
	printf("Dettagli shared memory creata:\n");
    	printf("...chiave IPC shm: %d\n", key_shm);
    	printf("...descrittore shm: %d\n", ds_shm);
    	printf("...indirizzo dopo attach: %p\n\n", p);
	
	printf("[PROCESSO PADRE (FLAGS) (%d)] Valore iniziale della memoria: %d.\n", getpid(), *p);
	
	pid_t pid = fork();
	
	if (pid == 0) {	// processo figlio
		
		// caso in cui non uso exec
		/*
		*p = 222;
		printf("[Figlio - %d] Valore corrente della memoria: %d.\n", getpid(), *p);
		exit(0);
		*/
		
		execl("./shm_other", "./shm_other", NULL); // usando execl con IPC_PRIVATE avrò errore
		
	} else if (pid > 0) {
		
		wait(NULL);
		
		printf("[PROCESSO PADRE (FLAGS) (%d)] Valore della memoria dopo l'esecuzione del processo figlio: %d.\n", getpid(), *p);
		
		*p = 333;
		
		printf("[PROCESSO PADRE (FLAGS) (%d)] Valore finale della memoria: %d.\n", getpid(), *p);
	
	}
	
	shmctl(ds_shm, IPC_RMID, 0); 	// marca il segmento come "da rimuovere", ma rimuovi solo quando non vi sono più processi collegati
					// restituisce -1 in caso di fallimento

	return 0;
}
