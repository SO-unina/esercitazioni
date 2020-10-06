// file di implementazione della libreria vettore.h

#include "vettore.h"
#include <iostream>
using namespace std;

// Funzione per la lettura degli elementi dell'elenco
void LeggiElementi(Vettore T,int & nelem) {

	do {
	cout<<"\n Inserisci il numero di elementi (n<100) dell' elenco : ";
	cin>>nelem;
	} while(nelem>100);

	for(int i=0;i<nelem;i++) {
		cout<<"\n V["<<i<<"]= ";
		cin>>T[i];
	}
}

// Funzione per la stampa degli elementi dell'elenco
void StampaVettore(const Vettore Vet, const int nelem) {

	for(int i=0;i<nelem;i++) {
		cout<<"\n V["<<i<<"]= "<<Vet[i];
	}
	cout<<"\n";
}

