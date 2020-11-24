#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "header.h"


int main() {

	printf("Processo P1 avviato\n");
	struct msg_calc m_p1;
	m_p1.processo = P1;

	key_t queue  = ftok(FTOK_PATH_Q, FTOK_CHAR_Q);

	int id_queue = msgget(queue,IPC_CREAT|0644);

	if(id_queue < 0) {
		perror("Msgget fallita");
		exit(1);
	}

	srand(time(NULL));

	
	int i;
	for(i = 0; i < 11;i++){
		m_p1.numero = generaFloat(0,10);
		printf("Invio messaggio: <%lu,%f>\n",m_p1.processo,m_p1.numero);	
		msgsnd(id_queue,(void *)&m_p1,sizeof(struct msg_calc)-sizeof(long),0);
		sleep(1);
	}
	
	return 0;
}
