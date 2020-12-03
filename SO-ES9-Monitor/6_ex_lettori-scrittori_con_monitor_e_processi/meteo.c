#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

int main(){

	/* TBD: Creare una variabile M di tipo "Monitor", e inizializzarla con init_monitor() */

	key_t id_meteo = shmget(IPC_PRIVATE,sizeof(Buffer),IPC_CREAT|0664);
	Buffer * buf = (Buffer*) (shmat(id_meteo,0,0));

	/* TBD: inizializzare la struttura Buffer */
	

	pid_t pid;

	int k;
	for (k=0; k<NUM_UTENTI; k++) {

		pid=fork();
		if (pid==0) {
			Utente(&M,buf);
			exit(0);
     	} else if(pid<0) {
			perror("fork");
		}
	}


	pid=fork();
	if (pid==0) {
		Servizio(&M,buf);
		exit(0);
	} else if(pid<0) {
		perror("fork");
	}


	int status;
	for (k=0; k<NUM_UTENTI+1; k++) {
		pid=wait(&status);
		if (pid==-1)
			perror("errore");
	}

	shmctl(id_meteo,IPC_RMID,0);

	/* TBD: Deallocare la variabile Monitor con remove_monitor() */

	return 0;
}
