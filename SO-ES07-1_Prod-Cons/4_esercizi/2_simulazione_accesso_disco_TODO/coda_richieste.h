#ifndef _CODA_RICHIESTE_H_
#define _CODA_RICHIESTE_H_

#include "semafori.h"

#define DIM 10

/* TODO: definire le eventuali macro per indicizzare i semafori */

typedef struct {
    unsigned int posizione;
    pid_t processo;
} richiesta;

typedef struct {
    int sem_id;
    int shm_id;
 
    /* TODO: aggiungere pool di buffer e variabili per gestire la produzione e consumazione 
        in coda circolare
    */
 
} coda_richieste;

coda_richieste * inizializza_coda();
void preleva_richiesta(coda_richieste *c, richiesta * r);
void inserisci_richiesta(coda_richieste *c, richiesta * r);
void rimuovi_coda(coda_richieste *c);

#endif
