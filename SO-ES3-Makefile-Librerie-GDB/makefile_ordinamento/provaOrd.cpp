#include "vettore.h"
#include "alg_ord.h"
#include <iostream>
using namespace std;


// Funzione main
int main(void) {
	int 	n;		// numero effettivo di elementi
	Vettore V;

	cout<<"\n\t\t Ordinamento di un elenco";
	cout<<"\n Metodi utilizzati: Insertion Sort e Quick Sort\n\n";
	LeggiElementi(V,n);
	InsertionSort(V,n);
	cout<<"\n Elenco ordinato con Insertion Sort: ";
	StampaVettore(V,n);
	LeggiElementi(V,n);
	QuickSort(V,n);
	cout<<"\n Elenco ordinato con Quick Sort: ";
	StampaVettore(V,n);
	return 0;
}

