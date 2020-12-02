#include "procedure.h"

#include <stdio.h>

void Produci(struct ProdCons * pc, int valore) {

	enter_monitor( &(pc->m) );

	printf("Ingresso monitor - produzione\n");

	if( pc->buffer_occupato == 1 ) {

		printf("Sospensione - produzione\n");
		wait_condition( &(pc->m), VARCOND_PRODUTTORI );
		printf("Riattivazione - produzione\n");
	}

	pc->buffer = valore;
	pc->buffer_libero = 0;
	pc->buffer_occupato = 1;

	printf("Produzione (%d)\n", valore);

	signal_condition( &(pc->m), VARCOND_CONSUMATORI );

	leave_monitor( &(pc->m) );

	printf("Uscita monitor - produzione\n");
}

int Consuma(struct ProdCons * pc) {

	int valore;

	enter_monitor( &(pc->m) );

	printf("Ingresso monitor - consumazione\n");

	if( pc->buffer_libero == 1 ) {

		printf("Sospensione - consumazione\n");
		wait_condition( &(pc->m), VARCOND_CONSUMATORI );
		printf("Riattivazione - consumazione\n");
	}

	valore = pc->buffer;
	pc->buffer_libero = 1;
	pc->buffer_occupato = 0;

	printf("Consumazione (%d)\n", valore);

	signal_condition( &(pc->m), VARCOND_PRODUTTORI );

	leave_monitor( &(pc->m) );

	printf("Uscita monitor - consumazione\n");

	return valore;

}

