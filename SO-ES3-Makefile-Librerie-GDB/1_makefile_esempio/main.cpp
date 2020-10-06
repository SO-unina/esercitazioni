//Programma di esempio: somma di due vettori
// vers. 2.0
// File contenente il programma principale
#include <iostream>
#include "lib.h"

using namespace std;

int main (){
	//vettori
	int a[NMAX],b[NMAX],c[NMAX];
	//riempimento degli array
	int n;

	do {
		//Inserimento riempimento 
		cout<<"\nInserire il numero degli elementi : ";
		cin>>n;
	} while (n>30); //il riempimento deve essere minore o uguale alla cardinalita'
	
	leggi_vettore(a,n);
	leggi_vettore(b,n);

	somma_vettori(a,b,c,n);

	stampa_vettore(c,n);
	
	return 0;
}
