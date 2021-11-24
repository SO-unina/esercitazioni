
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

void Lettore_Elaboratore (int sem, Buffer* buf, int len) {
    
    
    InizioLettura(sem, buf);
    
    /*********Lettura********/
    
    char convert[len];
    int i;
    
    for(i = 0; i < len; i++){
        convert[i] = buf->stringa[i] - 32;
    }
    convert[len] = '\0';
    printf("[elaboratore] Conversione della stringa '%s' -> %s\n", buf->stringa, convert);
    
    FineLettura(sem, buf);
    
    
}

int main(int argc, char * argv[]){
    
    
    int len = strtol(argv[1], NULL, 10);
    
    printf("[elaboratore] Sono l'ELABORATORE. Stringa len: %d, Il mio pid %d \n", len, getpid());
    
    int sem, id_shared, id_shared_str, k, numsem;
    
    key_t chiave_shm_buf = ftok(".", 'a');
    key_t c_sem = ftok(".", 'c');
    
    int status, numprocessi;
    
    Buffer *buf;
    
    //richiesta del buffer
    id_shared = shmget(chiave_shm_buf, sizeof(Buffer), 0);
    
    buf = (Buffer *) (shmat(id_shared, 0, 0));
    
    sem = semget(c_sem, 2, 0);
    
    int i;
    
    for(i=0; i<5; i++){
        Lettore_Elaboratore(sem, buf, len);
        sleep(1);
    }
    
    
    return 0;
}
