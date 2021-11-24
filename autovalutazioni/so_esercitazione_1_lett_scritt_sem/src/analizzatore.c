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
#include <time.h>

#include "header.h"

void Lettore_Analizzatore (int sem, Buffer* buf, int len) {

    InizioLettura(sem, buf);

    /*********Lettura********/

    int i;
    char invert[len];

    for (i=0; i<len; i++){

        invert[i] = buf->stringa[len-i-1];
    }

    invert[len] = '\0';
    
    printf("[analizzatore] Inversione della stringa '%s' -> '%s'\n", buf->stringa, invert);

    FineLettura(sem, buf);
}

int main(int argc, char * argv[]){
    
    int len = strtol(argv[1], NULL, 10);
   
    printf("Sono l'ANALIZZATORE. Stringa len: %d, Il mio pid %d \n", len, getpid());
    /************DICHIARAZIONE DELLE VARIABILI***************/
    
    int sem, id_shared, id_shared_str, k, numsem;

    
    key_t chiave_shm_buf = ftok(".", 'a');
    key_t c_sem = ftok(".", 'c');
    
    int status, numprocessi;
    
    Buffer *buf;
    
    id_shared = shmget(chiave_shm_buf, sizeof(Buffer), 0);
    
    buf = (Buffer *) (shmat(id_shared, 0, 0));
    
    sem = semget(c_sem, 2, 0);
    
    int i;
    
    
    for(i=0; i<5; i++){
        Lettore_Analizzatore(sem, buf, len);
        sleep(2);
    }
    
    return 0;
}
