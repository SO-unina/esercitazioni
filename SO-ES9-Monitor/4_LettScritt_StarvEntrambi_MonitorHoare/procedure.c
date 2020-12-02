#include "procedure.h"

#include <unistd.h>
#include <stdio.h>


int Leggi(struct LettScritt * ls) {

	int valore;

	enter_monitor( &(ls->m) );

	printf("Lettura - ingresso monitor\n");

	if( ls->numero_scrittori > 0 ) {

		printf("Sospensione - lettura\n");
        // Nel caso signal_and_wait, lo scrittore segnala e va in attesa, e quindi può segnalare
        // solo un lettore invece di tutti come per la soluzione signal_and_continue.
		wait_condition( &(ls->m), VARCOND_LETTORI );
		printf("Riattivazione - lettura\n");
	}

	ls->numero_lettori++;

	printf("Numero lettori ++ : %d\n", ls->numero_lettori);

	/*
	 * NOTA: Ogni lettore riattiva il lettore successivo
	 * (il primo lettore attiva il secondo ancora in attesa;
	 * il secondo lettore attiva il terzo; etc.)
	 */

	signal_condition( &(ls->m), VARCOND_LETTORI );

	leave_monitor( &(ls->m) );



	// ...operazione lenta...
	sleep(2);

	valore = ls->buffer;

	printf("Lettura - valore [%d]\n", valore);



	enter_monitor( &(ls->m) );

	ls->numero_lettori--;

	printf("Numero lettori -- : %d\n", ls->numero_lettori);


	/*
	 * NOTA: l'ultimo lettore ad abbandonare la risorsa
	 * riattiva uno degli scrittori in attesa
	 */

	if( ls->numero_lettori == 0 ) {

		printf("Lettura - signal su scrittori\n");

		signal_condition( &(ls->m), VARCOND_SCRITTORI );
	}

	leave_monitor( &(ls->m) );

	printf("Lettura - uscita monitor\n");

	return valore;

}


void Scrivi(struct LettScritt * ls, int valore) {

	enter_monitor( &(ls->m) );

	printf("Scrittura - ingresso monitor\n");

	if(ls->numero_lettori > 0 || ls->numero_scrittori > 0) {

		printf("Scrittura - sospensione\n");
		wait_condition( &(ls->m), VARCOND_SCRITTORI );
		printf("Scrittura - riattivazione\n");
	}

	ls->numero_scrittori++;

	printf("Numero scrittori ++ : %d\n", ls->numero_scrittori);

	leave_monitor( &(ls->m) );


	// ...operazione lenta...
	sleep(1);

	ls->buffer = valore;

	printf("Scrittura - valore [%d]\n", valore);



	enter_monitor( &(ls->m) );

	ls->numero_scrittori--;

	printf("Numero scrittori -- : %d\n", ls->numero_scrittori);


	/*
	 * NOTA: per bilanciare la starvation, si verifica se ci
	 * sono scrittori in attesa, e se ne riattiva uno se presente.
	 * Altrimenti, si riattiva un lettore.
	 */

	if( queue_condition( &(ls->m), VARCOND_SCRITTORI ) ) {

		printf("Scrittura - signal su scrittori\n");

		signal_condition( &(ls->m), VARCOND_SCRITTORI );

	} else {

		/*
		 * NOTA: si effettua una singola signal_cond e si riattiva
		 * un solo un processo lettore. Per questo motivo,
		 * il primo lettore a svegliarsi dovrà fare anche lui una
		 * signal_cond per riattivare il secondo lettore in attesa;
		 * il secondo lettore dovrà riattivare il terzo lettore; etc.
		 */

		printf("Scrittura - signal su lettori\n");

		signal_condition( &(ls->m), VARCOND_LETTORI );
	}

	leave_monitor( &(ls->m) );

	printf("Scrittura - uscita monitor\n");
}

