// file di implementazione della libreira alg_ord.h

#include <iostream>
#include "alg_ord.h"

using namespace std;

void Ordina(Vettore , const int , const int);
void Separa(Vettore , const int , const int , int & , int & );
void swap(T & a, T & b);

//***************************************************
// Funzione di ordinamento per INSERZIONE
//***************************************************
void InsertionSort(Vettore V, const int n) {

	int i,j,k;
	T   temp;

	for(i=1;i<=n-1;i++) {
		// Salva V[i] in temp
		temp=V[i];
		// Ricerca il I elemento > di V[i] in V[0]..V[i-1]
		j=0;
		while((V[j] < V[i]) && (j < i)) j++;
		// V[i] va inserito in posizione j...
		// Prima, sposta V[j]..V[i-1] di una posiz. in avanti
		for (k=i-1;k>=j;k--) V[k+1]=V[k];
		// Inserisci temp in V[j]
		V[j]=temp;
	}
}

//***************************************************
// Funzione di ordinamento QUICKSORT
//***************************************************

// Funzione di ordinamento con doppio indice
void QuickSort(Vettore V, const int n) {
	Ordina(V,0,n-1);
}

// Funzione ricorsiva di ordinamento
void Ordina(Vettore V, const int primo, const int ultimo) {

	int s,d;

	Separa(V,primo,ultimo,s,d);
	if(primo<d) Ordina(V,primo,d);
        if(s<ultimo) Ordina(V,s,ultimo);
}

void Separa(Vettore V, const int primo, const int ultimo, int & i, int & j) {

	T   x;

	i=primo;
	j=ultimo;

	x=V[(primo+ultimo)/2];  // NB: in questo caso, l'elemento di
				// separazione scelto si trova nel mezzo

//	x=V[ultimo];            // in alternativa...

	do {
		while(V[i]<x) i++;
                while(x<V[j]) j--;
		if(i<=j) {
			swap(V[i],V[j]);
                        i++;
			j--;
		}
	}  while(i<=j);
}


// Funzione che esegue lo scambio
void swap(T & a, T & b) {

	T temp;

	temp=a;
	a=b;
	b=temp;
}


