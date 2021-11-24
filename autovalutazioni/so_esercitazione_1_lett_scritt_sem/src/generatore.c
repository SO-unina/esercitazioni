

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

void Scrittore_Generatore (int sem, Buffer* buf, int len) {
    
    
    InizioScrittura(sem, buf);
    
    /*********Scrittura********/
    int i;
    srand(time(NULL));
    
    for(i = 0; i < len; i++){
        
        char randomletter = 'a' + (rand() % 26);
        buf->stringa[i] = randomletter;
        
    }
    buf->stringa[len+1] = '\0';
    
    printf("[generatore] Valore generato stringa: %s\n", buf->stringa);
    
    FineScrittura(sem, buf);
    
}

int main(int argc, char * argv[]){
    
    int len = strtol(argv[1], NULL, 10);
    
    int sem, id_shared, id_shared_str, k, numsem;
    
    printf("[generatore] Sono il GENERATORE. Stringa len: %d, Il mio pid %d \n", len, getpid());
    
    key_t chiave_shm_buf = ftok(".", 'a');
    key_t c_sem = ftok(".", 'c');
    
    int status, numprocessi;
    
    Buffer *buf;
    
    id_shared = shmget(chiave_shm_buf, sizeof(Buffer), 0);
    
    buf = (Buffer *) (shmat(id_shared, 0, 0));
    
    sem = semget(c_sem, 2, 0);
    
    int i;
    for(i=0; i<5; i++){
        Scrittore_Generatore(sem, buf, len);
        sleep(3);
    }
    
    return 0;
}


