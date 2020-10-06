// header file contenente la dichiarazione del tipo vettore
// e delle funzioni per leggerlo e scriverlo.
#ifndef VETTORE_H
#define VETTORE_H

const int nmax=100;		    // numero max di elementi
typedef int T;
typedef T Vettore [nmax];	// dichiarazione del tipo Vettore
				            // di elementi di tipo T

void LeggiElementi(Vettore, int &);
void StampaVettore(const Vettore,const int);

#endif
