#include "header.h"

/* Funzione che, per 10 volte, incrementa di uno la posizione molo,
    ovvero la posizione della nave,
    e tramite scrivi_molo effettua la modifica poi attende 3 secondi
 */

void * gestoreMolo (void * p){
	struct monitor* m = (struct monitor*) p;
	int i,s;
	s=m->molo;
	for(i=0; i<10; i++){
		s=s+1;
		scrivi_molo(m,s);
		printf("[C: Posizione della nave %d modificata. La nuova posizione è: %d]\n",m->id_nave,s);
		sleep(3);
	}
	pthread_exit(NULL);
}

//Funzione che controlla la posizione di un nave per tre volte
void * Viaggiatori (void * p){
	struct monitor* m = (struct monitor*) p;
	int i;
	int ris;
	for(i=0;i<3;i++){
		sleep(rand()%6+1);
		ris=leggi_molo(m);
		printf("[V]~La nave n.ro %d è nel molo %d\n", m->id_nave, ris);
	}
	pthread_exit(NULL);
}

int main() {
	
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	
	srand(time(NULL));

	struct monitor* m[5]; //l'array di monitor per gestire 5 navi

	pthread_t gestore_molo[5];//5 gestori molo
	pthread_t viagg[10];//10 viaggiatori	
	
	int i;

	//allocazione dei 4 monitor
	for(i=0;i<5;i++){
		m[i] = (struct monitor*) malloc(sizeof(struct monitor));
	}

	//inizializzazione
	for(i=0;i<5;i++){
		inizializza(m[i]);
	}

	//assegno un id ad ogni nave
	m[0]->id_nave=1;
	m[1]->id_nave=2;
	m[2]->id_nave=3;
	m[3]->id_nave=4;
    m[4]->id_nave=5;

	//creazione dei 4 threads capinave
	for(i=0;i<5;i++){
		pthread_create(&gestore_molo[i],NULL,gestoreMolo, (void*)  m[i]);
	}

	//creazione dei 10 threads viaggiatore
	for(i=0;i<10;i++){
		pthread_create(&viagg[i],NULL,Viaggiatori, (void*) m[rand() % 5]);
	}


	//join dei threads capitreno
	for(i=0;i<5;i++){
		pthread_join(gestore_molo[i],NULL);
		printf("gestoreMolo %d terminato\n",i+1);
	}

	//join dei threads viaggiatori
	for(i=0;i<10;i++){
		pthread_join(viagg[i],NULL);
		printf("Viaggiatore %d terminato\n",i+1);
	}

	//rimozione
	for(i=0;i<5;i++){
		rimuovi(m[i]);
	}

	//deallocazione monitor
	for(i=0;i<5;i++){
		free(m[i]);
	}

	return 0;
}	
