//Libreria per la somma di due vettori

#include<iostream>
#include "lib.h"

using namespace std;

//Definizione funzione leggi_vettore
void leggi_vettore(int a[], const int n) {
	int i;

	cout<<"LEGGI VETTORE....\n";
	for (i=0;i<n;i++) {
		cout<<"Inserire elemento n.ro "<<i<<" : ";
		cin>>a[i];
	}
}

//Definizione funzione stampa_vettore
void stampa_vettore(const int a[], const int n) {
	int i;
	cout<<"STAMPA VETTORE....\n";
	for (i=0;i<n;i++) 
		cout<<"Elemento n.ro "<<i<<" : "<<a[i]<<endl;
}

//Definizione funzione somma_vettore
void somma_vettori(const int a[], const int b[], int c[], const int n) {
	int i;
	cout<<"SOMMA VETTORI....\n";
	for (i=0;i<n;i++) 
		c[i]=a[i]+b[i];
}

