#include "monitor_hoare.h"

#define NUM_UTENTI 10
#define NUM_CONDITIONS 2

#define SYNCHL 0
#define SYNCHS 1

typedef struct {
	int temperatura;
	unsigned int umidita;
	unsigned short pioggia;
} meteo;

typedef struct {
	meteo meteo;
	
	/* TBD: aggiungere qui le variabili di stato per la sincronizzazione */
	
} Buffer;


void Servizio(Monitor* m, Buffer * buf);
void Utente(Monitor* m, Buffer * buf);
