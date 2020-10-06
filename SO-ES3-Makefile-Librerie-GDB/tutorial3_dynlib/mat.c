#include <stdio.h>
#include <stdlib.h>
#include "mat.h"

int somma(int* s,int d){
	int temp = 0;
	int i;
	for(i=0; i < d; i++){
		temp += s[i];
	}
	return temp;
}

int prod(int* s,int d){
	int temp = 1;
	int i;
	for(i=0; i < d; i++){
		temp *= s[i];
	}
	return temp;
}
