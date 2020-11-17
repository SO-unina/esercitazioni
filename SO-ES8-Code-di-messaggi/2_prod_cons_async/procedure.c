			/*-----IMPLEMENTAZIONE DELLE PROCEDURE-----*/

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include "header.h"
#include <time.h>

void Produttore(int queue, char * text) {
	Messaggio m;
	// costruzione del messaggio da trasmettere
	m.tipo=MESSAGGIO;
	strcpy(m.mess,text); 
	// invio messaggio
	msgsnd(queue,(void*)&m,sizeof(Messaggio)-sizeof(long),IPC_NOWAIT);
	printf("MESSAGGIO INVIATO: <%s>\n",m.mess);
}

void Consumatore(int queue) {
	Messaggio m;
	// ricezione messaggio
	msgrcv(queue,(void *) &m,sizeof(Messaggio)-sizeof(long),MESSAGGIO,0);
	printf("MESSAGGIO RICEVUTO: <%s>\n",m.mess);
	printMsgInfo(queue);
}

void printMsgInfo(int queue){
	struct msqid_ds mid;
	msgctl(queue,IPC_STAT,&mid);	
	char *time_sender = ctime(&mid.msg_stime);
	char *time_receiver = ctime(&mid.msg_rtime);	
	char *time_ctime = ctime(&mid.msg_ctime);
	printf("Time Sender: %sTime Receiver: %sTime Ctime: %s",time_sender,time_receiver,time_ctime);
	printf("Messages Number: %lu\n",mid.msg_qnum);
}
