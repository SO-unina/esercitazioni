#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

#include "header.h"


int main() {

	printf("Processo P3 avviato\n");
	struct msg_calc m_r;
	float media_cum[2];
	//int n_intermedio[2];

	key_t queue  = ftok(FTOK_PATH_Q, FTOK_CHAR_Q);

	int id_queue = msgget(queue,IPC_CREAT|0644);
	
	printf("ID QUEUE: %d\n",id_queue);
	if(id_queue < 0) {
		perror("Msgget fallita");
		exit(1);
	}

	
	int i;
	for(i = 0; i < 22;i++){
		msgrcv(id_queue,(void *)&m_r,sizeof(struct msg_calc)-sizeof(long),0,0);
		printf("Ricevuto messaggio dal processo <%lu> ,con valore <%f>\n",m_r.processo,m_r.numero);
		if(m_r.processo == P1){
			//n_intermedio[P1-1]++;
			media_cum[P1-1]+=m_r.numero / 11;
		}else if(m_r.processo == P2){
			//n_intermedio[P2-1]++;
			media_cum[P2-1]+=m_r.numero / 11;
		}else{
			printf("Processo non riconosciuto\n");
		}
	}

	for(i =0; i < 2;i++){
		printf("<Media %d = %f>\n",i+1,media_cum[i]);
	}
	return 0;
}
