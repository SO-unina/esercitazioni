#ifndef HEADER_H
#define HEADER_H

#include "monitor_signal_continue.h"

struct LettScritt {
	int buffer;

	int numero_lettori;
	int numero_scrittori;

	Monitor m;
};

#define VARCOND_LETTORI 0
#define VARCOND_SCRITTORI 1

void Scrivi(struct LettScritt * ls, int valore);
int Leggi(struct LettScritt * ls);

#endif
