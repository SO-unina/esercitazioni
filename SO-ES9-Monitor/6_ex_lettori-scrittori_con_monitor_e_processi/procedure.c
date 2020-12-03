#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "header.h"

void InizioLettura(Monitor* m, Buffer * buf){
	
	/* TBD: Effettuare inizio lettura */

}

void FineLettura(Monitor* m, Buffer * buf) {

	/* TBD: Effettuare fine lettura */

}



//Procedure di inizio e fine scrittura

void InizioScrittura(Monitor* m,Buffer*buf){

	/* TBD: Effettuare inizio scrittura */
}

void FineScrittura(Monitor* m, Buffer*buf){

	/* TBD: Effettuare inizio scrittura */
}



void Servizio(Monitor* m, Buffer * buf){

	srand(time(0));

	int i;
	for(i=0; i<20; i++) {

		/* TBD: Richiamare InizioScrittura e FineScrittura */

		buf->meteo.temperatura = (rand()%101)-50;
		buf->meteo.umidita = rand()%101;
		buf->meteo.pioggia = rand()%2;

		printf("<%d> scrittura: Temperatura=%d, Umidità=%d, Pioggia=%s\n", getpid(), buf->meteo.temperatura, buf->meteo.umidita, (buf->meteo.pioggia ? "si" : "no") );

		sleep(2);
	}

}

void Utente(Monitor* m, Buffer * buf) {

	int i;
	for(i=0; i<10; i++) {
		
		/* TBD: Richiamare InizioLettura e FineLettura */

		printf("<%d> lettura: Temperatura=%d, Umidità=%d, Pioggia=%s\n", getpid(), buf->meteo.temperatura, buf->meteo.umidita, (buf->meteo.pioggia ? "si" : "no") );

		sleep(1);
	}

}


