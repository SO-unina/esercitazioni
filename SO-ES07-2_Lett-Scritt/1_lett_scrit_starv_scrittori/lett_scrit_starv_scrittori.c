/************PROBLEMA DEI LETTORI SCRITTORI**********/
/****soluzione con attesa indefinita degli scrittori****/

/*Il programma sincronizza nell'accesso ad una zona di memoria condivisa.
  Parte dei processi esegue operazioni di esclusiva lettura,i restanti
  di esclusiva scrittura.

  Header file: header.h
  Programma chiamante: lett_starv_scritt.c
  Modulo delle procedure: procedure.c
  Direttive per la compilazione dei moduli:Makefile

*/


#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "header.h"


int main(){

        /************DICHIARAZIONE DELLE VARIABILI***************/

        int sem, id_shared, k, numsem, numlettori, numscrittori;
        key_t chiave = IPC_PRIVATE;
        key_t c_sem = IPC_PRIVATE;
        int status, numprocessi;
        pid_t pid;
        Buffer *buf;

        numlettori = 6;
        numscrittori = 6;
        int num_processi = numscrittori + numlettori;

        //richiesta del buffer
        id_shared=shmget(chiave, sizeof(Buffer), IPC_CREAT | 0664);
        printf("id_shared = %d\n", id_shared);
        buf = (Buffer*) (shmat(id_shared, 0, 0));
        buf->numlettori = 0;
        buf->messaggio = 0;

        //richiesta di due semafori ed inizializzazione
        sem=semget(c_sem, 2, IPC_CREAT | 0664);
        semctl(sem, MUTEXL, SETVAL, 1);
        semctl(sem, SYNCH, SETVAL, 1);

        //generazione di scrittori e lettori
        for (k=0; k<num_processi; k++) {

                pid=fork();

                if (pid == 0)  {                //processo figlio
                        if ( (k%2) == 0) {
                                printf("sono il figlio scrittore. Il mio pid %d \n", getpid());
                                Scrittore(sem, buf);	        
                        
                        } else {	
                                printf("sono il figlio lettore. Il mio pid %d\n", getpid());
                                Lettore(sem, buf);
                        }
                        exit(0);
                }


        }

        for (k=0; k<num_processi; k++){
                pid=wait(&status);
                if (pid==-1)
                        perror("errore");
                else
                        printf("Figlio n.ro %d e\' morto con status= %d\n", pid, status);
        }

        /********DEALLOCAZIONE SEMAFORI E MEMORIA CONDIVISA**********/

        shmctl(id_shared, IPC_RMID, 0);
        semctl(sem, 0, IPC_RMID);

        return 0;
}
