#include <pthread.h>

#ifndef HEADER_H
#define HEADER_H

#define DIM_BUFFER 5

/* N.B.: Gli identificativi per il tipo messaggio possono anche essere uguali
 * perchè stiamo usando code con descrittori diversi!
 */

#define REQUEST_TO_SEND 1
#define OK_TO_SEND 2

#define RISULTATO_TYPE 3

extern int coda_RTS;
extern int coda_OTS;
extern int coda_risultati;

typedef struct {
    
    // pool di buffer condivisi
    int operandi[DIM_BUFFER];
    
    // var condition
    pthread_cond_t ok_prod_operandi_cv;
    pthread_cond_t ok_cons_operandi_cv;
    
    pthread_mutex_t mutex;
    
    int testa_operandi;
    int coda_operandi;
    
    int contatore_operandi;
    
} MonitorOperandi;

typedef struct {
    long tipo;
    char mess[20]; // Il tipo del messaggio può anche essere un intero
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

