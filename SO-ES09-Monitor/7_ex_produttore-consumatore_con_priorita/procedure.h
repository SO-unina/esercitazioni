#ifndef __PROCEDURE_H
#define __PROCEDURE_H

#include "monitor_signal_continue.h"

#define DIM 3

typedef struct{
	int buffer[DIM];
	
	/* TBD: Completare la definizione di questa struttura,
	 *      aggiungendo un sotto-oggetto Monitor, le variabili testa e coda,
	 *      ed eventualmente (a scelta dello studente) una variabile "contatore"
	 */
}PriorityProdCons;


void inizializza_prod_cons(PriorityProdCons* p);
void produci_alta_prio(PriorityProdCons* p );
void produci_bassa_prio(PriorityProdCons* p);
void consuma(PriorityProdCons* p);
void rimuovi_prod_cons(PriorityProdCons* p);

#endif
