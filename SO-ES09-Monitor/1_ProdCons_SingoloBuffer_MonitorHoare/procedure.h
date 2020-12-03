#ifndef HEADER_H
#define HEADER_H

#include "monitor_hoare.h"


struct ProdCons {
	int buffer;

	int buffer_libero; // 1 se libero, 0 se pieno
	int buffer_occupato; // 0 se libero, 1 se pieno

	Monitor m;
};

#define VARCOND_PRODUTTORI 0
#define VARCOND_CONSUMATORI 1

void Produci(struct ProdCons * pc, int valore);
int Consuma(struct ProdCons * pc);

#endif
