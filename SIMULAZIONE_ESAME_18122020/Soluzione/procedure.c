#include "header.h"
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <string.h>

int coda_RTS;
int coda_OTS;
int coda_risultati;

// inizializzazione code di servizio
void initServiceQueues(){
    
    coda_RTS = msgget(IPC_PRIVATE,IPC_CREAT|0664);
    printf("Coda di servizio coda_RTS create con desc: %d\n", coda_RTS);
    
    coda_OTS = msgget(IPC_PRIVATE,IPC_CREAT|0664);
    printf("Coda di servizio coda_OTS create con desc: %d\n", coda_OTS);
}

// rimozione code di servizio
void removeServiceQueues(){
    msgctl(coda_RTS,IPC_RMID,0);
    msgctl(coda_OTS,IPC_RMID,0);
}

// Send Sincrona
void inserisci_risultato (Risultato *m , int queue){
    
    Risultato m1,m2;
    // costruzione messaggio RTS
    m1.tipo = REQUEST_TO_SEND;
    strcpy(m1.mess,"Richiesta di invio");
    // invio messaggio RTS
    msgsnd(coda_RTS, &m1, sizeof(Risultato) - sizeof(long), 0);
    printf("Messaggio TIPO: %lu MSG: '%s' inviato su coda di servizio %d\n", m1.tipo, m1.mess, coda_RTS);
    // ricezione OTS
    msgrcv(coda_OTS, &m2, sizeof(Risultato) - sizeof(long), OK_TO_SEND, 0);
    printf("Messaggio TIPO: %lu MSG: '%s' ricevuto su coda di servizio %d\n", m2.tipo, m2.mess, coda_OTS);
    // invio messaggio
    msgsnd(queue, m, sizeof(Risultato) - sizeof(long), 0);
    printf("Messaggio TIPO: %lu MSG: '%s' inviato su coda %d\n", m->tipo, m->mess, queue);
}

// Receive Bloccante
int preleva_risultato(Risultato *m, int queue, int tipomess){
    
    Risultato m1,m2;    // ricezione messaggio RTS
    msgrcv(coda_RTS, &m1, sizeof(Risultato) - sizeof(long), REQUEST_TO_SEND, 0);    // costruzione messaggio OTS
    printf("Messaggio TIPO: %lu MSG: '%s' ricevuto su coda di servizio %d\n", m1.tipo, m1.mess, coda_RTS);
    
    m2.tipo = OK_TO_SEND;
    strcpy(m2.mess, "Ready to send");
    // invio messaggio OTS
    msgsnd(coda_OTS, &m2, sizeof(Risultato) - sizeof(long), 0);
    printf("Messaggio TIPO: %lu MSG: '%s' inviato su coda di servizio %d\n", m2.tipo, m2.mess, coda_OTS);
    
    // ricezione messaggio
    msgrcv(queue, m, sizeof(Risultato) - sizeof(long), tipomess, 0);
    printf("Messaggio TIPO: %lu MSG: '%s' ricevuto su coda %d\n", m->tipo, m->mess, queue);
    
    return atoi(m->mess); //Nel caso in cui si scegliesse il tipo intero per il campo messaggio la chiamato ad atoi è non necessaria
}

void inserisci_operando(MonitorOperandi * m, int operando){

        pthread_mutex_lock(&m->mutex);

        while (m->contatore_operandi == DIM_BUFFER){
            pthread_cond_wait(&m->ok_prod_operandi_cv, &m->mutex);
        }

        m->operandi[m->coda_operandi] = operando;

        printf("[thread genera_operandi] Operando prodotto = %d\n", m->operandi[m->coda_operandi]);

        // update puntatore coda e testa devono essere fatte nel monitor!!!
        m->coda_operandi = (m->coda_operandi + 1) % DIM_BUFFER;

        m->contatore_operandi++;
        
        pthread_cond_signal(&m->ok_cons_operandi_cv);

        pthread_mutex_unlock(&m->mutex);

}

int * preleva_operando(MonitorOperandi * m){

        static int operando[2];

        pthread_mutex_lock(&m->mutex);

        //ERRORE: while (m->contatore_operandi == 0)
        while (m->contatore_operandi <= 1){
            pthread_cond_wait(&m->ok_cons_operandi_cv, &m->mutex);
        }

        operando[0] = m->operandi[m->testa_operandi];
        m->testa_operandi = (m->testa_operandi + 1) % DIM_BUFFER;
        /*
        m->contatore_operandi--;
        pthread_cond_signal(&m->ok_prod_operandi_cv);
        */
        operando[1] = m->operandi[m->testa_operandi];
        m->testa_operandi = (m->testa_operandi + 1) % DIM_BUFFER;
        /*
        m->contatore_operandi--;
        pthread_cond_signal(&m->ok_prod_operandi_cv);
         */
    
        m->contatore_operandi -= 2;
        pthread_cond_signal(&m->ok_prod_operandi_cv);

        pthread_mutex_unlock(&m->mutex);

        return operando;
}

void * genera_operandi(void *m){

        int i, op;

        MonitorOperandi * mon = (MonitorOperandi *)m;
        for (i=0; i<6; i++){
        
                // call inserisci_operando generato da 1 a 10
                op = 1 + rand() % 10;
                //printf("[thread genera_operandi] Operando generato: %d\n", op);
                inserisci_operando(mon, op);
                 
        }
        pthread_exit(0);
}

void preleva_risultati(int coda_risultati){

        int i, risultato, less=0, great=0;
    
        Risultato m;
    
        for (i=0; i<6; i++){
        
            
                //risultato = preleva_risultato(mon);
                risultato = preleva_risultato(&m, coda_risultati, RISULTATO_TYPE);
                printf("[processo preleva_risultati] Risultato prelevato: %d coda: %d\n", risultato, coda_risultati);
            
                if (risultato<=25)
                    less++;
                else
                    great++;
                 
        }

        printf("[processo preleva_risultati] STATS: Conteggio minore uguale: risultato: %d\n", less);
        printf("[processo preleva_risultati] STATS: Conteggio maggiore: %d\n", great);
        exit(0);
}


void * calcola(void *mon){

        int i, calc;
        int *op;

        // type casting da void *
        MonitorOperandi * mon_op = (MonitorOperandi *)mon;
        Risultato m;
    
        for (i=0; i<2; i++){
        
                // preleva operando
                op = preleva_operando(mon_op);
                int op1 = *op;
                int op2 = *(op+1);
                printf("[thread calcola] Preleva op1: %d op2: %d\n", op1, op2);

                // calcola
                calc = (op1*op1) + (op2*op2);

                printf("[thread calcola] Calcola somma dei quadrati (%d x %d) + (%d x %d) = %d\n", op1, op1, op2, op2, calc);
                // inserisci risultato
            
                printf("[thread calcola] Inserisci risultato: %d tramite send sincrona su coda: %d\n", calc, coda_risultati);
                sleep(1);
                //inserisci_risultato(mon_ris, calc);
            
                m.tipo = RISULTATO_TYPE;
                sprintf(m.mess, "%d", calc);
                inserisci_risultato(&m , coda_risultati);
        }
    
        pthread_exit(0);
}
