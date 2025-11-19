#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdlib.h>

#include "coda_richieste.h"

coda_richieste *inizializza_coda()
{
    int shm_id;
    int sem_id;
    coda_richieste *c;

    // Creo un array semaforico di 4 elementi
    sem_id = /* TODO */

    // Semafori per la gestione della cooperazione
    semctl(/* TODO */);
    semctl(/* TODO */);

    // Semafori per la gestione della competizioni tra prod e cons
    semctl(/* TODO */);
    semctl(/* TODO */);

    // Creo shared memory per prod/cons
    shm_id = shmget(/* TODO */);

    if (shm_id < 0)
    {
        perror("Errore creazione SHM coda richieste");
        exit(1);
    }

    // Ottengo un puntatore alla shm
    c = /* TODO */

    if (c == (void *)-1)
    {
        perror("Errore attach SHM");
        exit(1);
    }

    c->testa = 0;
    c->coda = 0;
    c->shm_id = shm_id;
    c->sem_id = sem_id;

    return c;
}

// Agisco da consumatore
void preleva_richiesta(coda_richieste *c, richiesta *r) {

    /* TODO: Inizio gestione della concorrenza */
    printf("[%d] Consumazione in coda: %d\n", getpid(), c->coda);

    // Consumazione
    r->posizione = c->vettore[c->coda].posizione;
    r->processo = c->vettore[c->coda].processo;
    c->coda = (c->coda + 1) % DIM;

    /* TODO: Terminazione gestione della concorrenza */
}

// Agisco da produttore
void inserisci_richiesta(coda_richieste *c, richiesta *r)
{
    /* TODO: Inizio gestione della concorrenza */

    printf("[%d] Produzione in testa: %d\n", getpid(), c->testa);

    // Produzione
    c->vettore[c->testa].posizione = r->posizione;
    c->vettore[c->testa].processo = r->processo;
    c->testa = (c->testa + 1) % DIM;

    /* TODO: Terminazione gestione della concorrenza */
}

void rimuovi_coda(coda_richieste *c){

    /* TODO: Marcare come da eliminare shm e sem */

}
