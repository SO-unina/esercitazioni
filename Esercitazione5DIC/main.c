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

int main(){

        pid_t pid;
        int ds_queue_gen_filter, ds_queue_filter_checksum, ds_queue_checksum_visual;
        int total_process = NUM_GENERATORS + NUM_FILTER + NUM_CHECKSUM + NUM_VISUAL;

        //create queues
        int key_queue_gen_filter = IPC_PRIVATE;
        int key_queue_filter_checksum = IPC_PRIVATE;
        int key_queue_checksum_visual = IPC_PRIVATE;

        ds_queue_gen_filter = msgget(key_queue_gen_filter, IPC_CREAT | 0644);
        ds_queue_filter_checksum = msgget(key_queue_filter_checksum, IPC_CREAT | 0644);
        ds_queue_checksum_visual = msgget(key_queue_checksum_visual, IPC_CREAT | 0644);
        
        printf("[master] Code create...\n");
        printf("[master] ...........ds_queue_gen_filter: %d\n", ds_queue_gen_filter);
        printf("[master] ...........ds_queue_filter_checksum: %d\n", ds_queue_filter_checksum);
        printf("[master] ...........ds_queue_checksum_visual: %d\n", ds_queue_checksum_visual);

        int i;

        for (i=0; i<NUM_GENERATORS; i++){
        
                pid = fork();

                if (pid == 0){
                
                        generatore(ds_queue_gen_filter);
                
                }        
        }        


        for (i=0; i<NUM_FILTER+NUM_CHECKSUM+NUM_VISUAL; i++){
                pid = fork();
                if (pid==0){
                        if (i==0){
                                filtro(ds_queue_gen_filter, ds_queue_filter_checksum);
                        }
                        else if (i==1){
                                checksum(ds_queue_filter_checksum, ds_queue_checksum_visual);
                        }
                        else if (i==2){
                                visualizzatore(ds_queue_checksum_visual);
                        }
                }
        }

       
        for (i=0; i<total_process; i++){
                wait(NULL);
        }

        msgctl(ds_queue_gen_filter, IPC_RMID, 0);
	msgctl(ds_queue_filter_checksum, IPC_RMID, 0);
	msgctl(ds_queue_checksum_visual, IPC_RMID, 0);

        printf("[master] Rimozione code OK!\n");

        return 0;
}
