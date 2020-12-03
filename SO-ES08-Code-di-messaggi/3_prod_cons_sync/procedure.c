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

static int queue1;//statiche-->non è necessaria la loro visibilità fuori dal modulo
static int queue2;


// inizializzazione code di servizio
void initServiceQueues(){

     	queue1=msgget(IPC_PRIVATE,IPC_CREAT|0664);
	queue2=msgget(IPC_PRIVATE,IPC_CREAT|0664);
}

// rimozione code di servizio
void removeServiceQueues(){
	msgctl(queue1,IPC_RMID,0);
	msgctl(queue2,IPC_RMID,0);
}

// Send Sincrona
void SendSincr (Messaggio *m , int queue){
	Messaggio m1,m2;
	// costruzione messaggio RTS
	m1.tipo=REQUEST_TO_SEND;
	strcpy(m1.mess,"Richiesta di invio");
	// invio messaggio RTS
	msgsnd(queue1,&m1,sizeof(Messaggio)-sizeof(long),0);	
	// ricezione OTS
	msgrcv(queue2,&m2,sizeof(Messaggio)-sizeof(long),OK_TO_SEND,0);
	// invio messaggio
	msgsnd(queue,m,sizeof(Messaggio)-sizeof(long),0);
}

// Receive Bloccante
void ReceiveBloc (Messaggio *m, int queue, int tipomess){
	Messaggio m1,m2;	// ricezione messaggio RTS
	msgrcv(queue1,&m1,sizeof(Messaggio)-sizeof(long),REQUEST_TO_SEND,0);	// costruzione messaggio OTS
	m2.tipo=OK_TO_SEND;
	strcpy(m2.mess,"Ready to send");
	// invio messaggio OTS
	msgsnd(queue2,&m2,sizeof(Messaggio)-sizeof(long),0);
	// ricezione messaggio
	msgrcv(queue,m,sizeof(Messaggio)-sizeof(long),tipomess,0);
}

void Produttore(int queue, char * text) {
	Messaggio m;
	// costruzione del messaggio da trasmettere
	m.tipo=MESSAGGIO;
	strcpy(m.mess,text); 
	// invio messaggio
	SendSincr(&m,queue);
	printf("MESSAGGIO INVIATO: <%s>\n",m.mess);
}

void Consumatore(int queue) {
	Messaggio m;
	// ricezione messaggio
	ReceiveBloc(&m,queue,MESSAGGIO);
	printf("MESSAGGIO RICEVUTO: <%s>\n",m.mess);
}


