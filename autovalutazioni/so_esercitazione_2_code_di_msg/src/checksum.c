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

void checksum(int queue_filter_checksum, int queue_checksum_visual){

        int ret, i, j, checksum;
        message mess;

        for (j=0; j<NUM_MESSAGES; j++){

                printf("[checksum] Ricevo dal processo Filter...\n");

                ret = msgrcv(queue_filter_checksum, &mess, sizeof(message) - sizeof(long), 0, IPC_NOWAIT);
                if(ret<0) {
                        if (errno == ENOMSG){
                                printf("Non ci sono più messaggi da ricevere dal processo filter...exit!\n");
                                break;
                        }
                        else{
                                perror("ERROR!!!");
                                exit(-1);
                        }
                }
                printf("[checksum] Calcolo CHECKSUM...\n");
                //calc checksum
                for (i=0; i<STRING_MAX_DIM-1; i++){
                        checksum += mess.stringa[i];
                }
                for (i=0; i<INT_MAX_DIM; i++){
                        checksum += mess.array[i];
                }

                mess.var = checksum;

                printf("[checksum] CHECKSUM: %d\n", mess.var);

                ret = msgsnd(queue_checksum_visual, &mess, sizeof(message) - sizeof(long), 0);
                if (ret<0){
                        perror("msgsnd msg1 on ds_queue_gen_filter FALLITA!");
                        exit(-1);
                }

                printf("[checksum] Invio messaggio di CHECKSUM al Visualizzatore...\n");
        }
        
        exit(0);
}

