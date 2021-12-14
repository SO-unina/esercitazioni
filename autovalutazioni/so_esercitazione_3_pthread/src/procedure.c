#include "header.h"



void inizializza(struct monitor* m){

	m->molo=0;
	m->id_nave=0;

	m->occupato=0;
	m->num_lettori=0;

	m->coda_lettori=0;
	m->coda_scrittori=0;

	pthread_mutex_init(&(m->mutex),NULL);
	pthread_cond_init(&(m->ok_aggiorna),NULL);
	pthread_cond_init(&(m->ok_leggi),NULL);
}

void rimuovi (struct monitor* m){
	pthread_mutex_destroy(&(m->mutex));
	pthread_cond_destroy(&(m->ok_aggiorna));
	pthread_cond_destroy(&(m->ok_leggi));
}


//SCRITTURA. AGGIORNAMENTO DELLA POSIZIONE DELLA NAVE
void scrivi_molo(struct monitor* m, int molo){

    //Completare con codice dello scrittore
    pthread_mutex_lock(&(m->mutex));
    
    while(m->occupato==1){
        m->coda_scrittori=m->coda_scrittori+1;
        pthread_cond_wait(&(m->ok_aggiorna),&(m->mutex));
        m->coda_scrittori=m->coda_scrittori-1;
    }
    
    m->occupato=1;
    
    pthread_mutex_unlock(&(m->mutex));
    
    
    
    // SCRITTURA
    m->molo=molo;
    
    
    
    pthread_mutex_lock(&(m->mutex));
    
    if(m->coda_scrittori>0)
        pthread_cond_signal(&(m->ok_aggiorna));
    
    else if(m->coda_lettori>0)
        pthread_cond_signal(&(m->ok_leggi));
    
    m->occupato=0;
    
    pthread_mutex_unlock(&(m->mutex));

}


//LETTURA. RESTITUISCE LA POSIZIONE DELLA NAVE
int leggi_molo(struct monitor* m){

	//Completare con codice del lettore
    pthread_mutex_lock(&(m->mutex));
    
    while(m->occupato==1 && m->num_lettori==0){
        
        m->coda_lettori=m->coda_lettori+1;
        pthread_cond_wait(&(m->ok_leggi),&(m->mutex));
        m->coda_lettori=m->coda_lettori-1;
        
    }
    
    m->occupato=1;
    
    m->num_lettori=m->num_lettori+1;
    
    pthread_cond_signal(&(m->ok_leggi));
    
    pthread_mutex_unlock(&(m->mutex));
    
    
    
    // LETTURA
    int ris=m->molo;
    
    
    
    pthread_mutex_lock(&(m->mutex));
    
    m->num_lettori=m->num_lettori-1;
    
    if(m->num_lettori==0){
        
        m->occupato=0;
        
        pthread_cond_signal(&(m->ok_aggiorna));
    }
    
    pthread_mutex_unlock(&(m->mutex));
    
    
    return ris;

}

