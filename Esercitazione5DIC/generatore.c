#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "header.h"

void generatore(int ds_queue_gen_filter){

        message msg1, msg2;
        int i, ret;
        srand(time(NULL)*getpid());

        msg1.type = MSG_TYPE;
        msg2.type = MSG_TYPE;

        for (i=0; i<STRING_MAX_DIM-1; i++){

                msg1.stringa[i] = 'a' + (rand() % 26);
                msg2.stringa[i] = 'a' + (rand() % 26);

        }

        msg1.stringa[STRING_MAX_DIM-1] = '\0';
        msg2.stringa[STRING_MAX_DIM-1] = '\0';

        for(i=0; i<INT_MAX_DIM; i++){
                msg1.array[i] = rand() % 9;
                msg2.array[i] = rand() % 9;
        }
        msg1.var = 0;
        msg2.var = 0;

        ret = msgsnd(ds_queue_gen_filter, &msg1, sizeof(message) - sizeof(long), 0);
        if (ret<0){
                perror("msgsnd msg1 on ds_queue_gen_filter FALLITA!");
                exit(-1);
        }
        printf("[generatore] Messaggio msg1 INVIATO!\n");
        printf("[generatore] ...............msg1.stringa: %s\n", msg1.stringa);
        printf("[generatore] ...............msg1.array[0]: %d\n", msg1.array[0]);
        printf("[generatore] ...............msg1.array[1]: %d\n", msg1.array[1]);
        printf("[generatore] ...............msg1.var: %d\n", msg1.var);



        ret = msgsnd(ds_queue_gen_filter, &msg2, sizeof(message) - sizeof(long), 0);
        if (ret<0){
                perror("msgsnd msg1 on ds_queue_gen_filter FALLITA!");
                exit(-1);
        }
        printf("[generatore] Messaggio msg2 INVIATO!\n");
        printf("[generatore] ...............msg2.stringa: %s\n", msg2.stringa);
        printf("[generatore] ...............msg2.array[0]: %d\n", msg2.array[0]);
        printf("[generatore] ...............msg2.array[1]: %d\n", msg2.array[1]);
        printf("[generatore] ...............msg2.var: %d\n", msg2.var);

        exit(0);
}

