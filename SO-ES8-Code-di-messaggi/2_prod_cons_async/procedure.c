			/*-----IMPLEMENTAZIONE DELLE PROCEDURE-----*/

s

void Produttore(int queue, char * text) {
	Messaggio m;
	// costruzione del messaggio da trasmettere
	m.tipo=MESSAGGIO;
	strcpy(m.mess,text); 
	// invio messaggio
	msgsnd(queue,(void*)&m,sizeof(Messaggio)-sizeof(long),0);
    /*
        posso mettere IPC_NOWAIT nei flag? No perchè il produttore deve fermarsi se
        la coda è piena! Con il flag impostato a 0 il processo si blocca se la coda è piena.
     */
	printf("MESSAGGIO INVIATO: <%s>\n",m.mess);
}

void Consumatore(int queue) {
	Messaggio m;
	// ricezione messaggio
	msgrcv(queue,(void *) &m,sizeof(Messaggio)-sizeof(long),MESSAGGIO,0);
    /*
        posso usare una receive non bloccante? No perchè il consumatore si deve
        bloccare quando un produttore a prodotto!
     */
    
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
