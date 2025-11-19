#ifndef _CODA_RICHIESTE_H_
#define _CODA_RICHIESTE_H_

#include "semafori.h"

#define DIM 10
#define SPAZIO_DISP 0
#define MESSAGGIO_DISP 1
#define MUTEX_P 2
#define MUTEX_C 3
/* Nota: MUTEX_C è opzionale in questo esercizio,
 * c'è un solo consumatore */


typedef struct {
    unsigned int posizione;
    pid_t processo;
} richiesta;

typedef struct {
    int sem_id;
    int shm_id;
    richiesta vettore[DIM];
    int testa;
    int coda;
} coda_richieste;

coda_richieste * inizializza_coda();
void preleva_richiesta(coda_richieste *c, richiesta * r);
void inserisci_richiesta(coda_richieste *c, richiesta * r);
void rimuovi_coda(coda_richieste *c);

#endif
