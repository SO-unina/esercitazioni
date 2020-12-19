#include <pthread.h>

#ifndef HEADER_H
#define HEADER_H

#define DIM_BUFFER 5

/* TBD: Definire le macro per la comunicazione su coda sincrona */

extern int coda_RTS;
extern int coda_OTS;
extern int coda_risultati;

typedef struct {
    
    // pool di buffer condivisi
    int operandi[DIM_BUFFER];
    
    /* TBD: Aggiungere le variabili necessarie per la sincronizzazione */
    
} MonitorOperandi;

typedef struct {
    /* TBD: Definire la struttura messaggio */
} Risultato;

void inserisci_operando(MonitorOperandi * mo, int operando);
int *preleva_operando(MonitorOperandi * mo);

void inserisci_risultato(Risultato *m , int queue);
int preleva_risultato(Risultato *m, int queue, int tipomess);

void * genera_operandi(void *);
void * calcola(void *);
void preleva_risultati(int);

void initServiceQueues();
void removeServiceQueues();
    
#endif

