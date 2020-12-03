/*IMPLEMENTAZIONE DELLE PROCEDURE*/

#include "procedure.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

/* TBD: Definire delle macro per identificare le variabili condition */


void inizializza_prod_cons(PriorityProdCons* p){

	/* TBD: Inizializzare le variabili della struttura (testa, coda, ...) */

	/* TBD: Inizializzare il sotto-oggetto "Monitor", chiamando init_monitor(...).
	        Scegliere accuratamente il numero di variabili condition */

}

void rimuovi_prod_cons(PriorityProdCons* p){

	/* TBD: Deallocare il sotto-oggetto "Monitor", chiamando remove_Monitor(...). */
}


void produci_alta_prio(PriorityProdCons* p){

	int value;

	/* TBD: Effettuare l'ingresso nel monitor */

	//Aumenta il numero di produttori
	printf("Produttore 1 entrato nel monitor...\n");

	/* TBD: Sospendere qui il processo se il vettore di buffer è pieno */

	//Produco il valore
	value = rand() % 12 ;

	//Modifico il buffer
	p->buffer[p->testa] = value;
	p->testa = (p->testa + 1) % DIM;
	p->count++;

	//Il buffer non è vuoto
	printf("Produttore 1 con pid %d ha prodotto %d\n",getpid(),value);	
	
	/* TBD: Effettuare la signal_condition per i consumatori in attesa */
	
	/* TBD: Uscire dal monitor */
}

void produci_bassa_prio(PriorityProdCons* p){

	int value;
	
	/* TBD: Effettuare l'ingresso nel monitor */
	
	//Aumenta il numero di produttori
	printf("Produttore 2 entrato nel monitor...\n");
	
	/* TBD: Sospendere qui il processo se il vettore di buffer è pieno */

	//Produco il valore
	value = 13 + (rand() % 12) ;

	//Modifico il buffer
	p->buffer[p->testa] = value;
	p->testa = (p->testa + 1) % DIM;
	p->count++;

	//Il buffer non è vuoto
	printf("Produttore 2 con pid %d ha prodotto %d\n",getpid(),value);	

	/* TBD: Effettuare la signal_condition per i consumatori in attesa */

	/* TBD: Uscire dal monitor */

}

void consuma(PriorityProdCons* p){

	int value;

	/* TBD: Effettuare l'ingresso nel monitor */

	/* TBD: Sospendere qui il processo se il vettore di buffer è vuoto */


	value = p->buffer[p->coda];
	p->coda = (p->coda + 1) % DIM;
	p->count--;

	printf("Consumatore con pid %d ha consumato valore %d\n",getpid(),value);


	/* TBD: Effettuare la signal_condition per attivare un produttore.
	 *      Si attivi un produttore di priorità alta se presente, altrimenti,
	 *      si attivi un produttore di priorità bassa.
	 * 
	 * 		Per determinare se ci sono produttori ad alta priorità in attesa,
	 * 		si introduca una variabile "num_lettori_alta_priorita", che i produttori
	 *      incrementano subito prima di fare wait_condition(), e che decrementano
	 * 		subito dopo aver eseguito wait_condition().
	 * 
	 * 		In alternativa, utilizzare la funzione "queue_condition()".
	 */


	/* TBD: Uscire dal monitor */
}
