/**********************************************
 Tutorial Loading Dinamico di una shared library
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>
#include "mat.h"

#define DIM 10

typedef struct arr_int{
	int* arr;
	int dim;
}arr_int_t;


void popola(arr_int_t* a){
	int i;
	srand(time(NULL));
	
	for(i = 0; i < a->dim; i++){
		a->arr[i] = (rand()% 4) + 1;
	}
}

void stampa(arr_int_t* a){
	int i;
	printf("( ");
	for(i=0;i < a->dim; i++){
		printf("%d ",a->arr[i]);
	}
	printf(" ) \n");
}

int main(int argc, char** argv){
	arr_int_t a;
	char cwd[1024];
	int (*fn)(int*,int);	
	char* error;
	int* s = malloc(DIM*sizeof(int));
	void* lib_handle;
	a.arr = s;
	a.dim = DIM;
	popola(&a);	
	
	//Dichiarazione variabili
	int sum;
	int p;
	//Prendiamo il path corrente
	getcwd(cwd,sizeof(cwd));
	//Richiamiamo la nostra libreria dinamicamente
	strcat(cwd,"/libmat.so");
	//Apriamo una libreria dinamica
	lib_handle = dlopen(cwd,RTLD_LAZY);
	if(!lib_handle){
		fprintf(stderr,"%s\n",dlerror());
		exit(1);
	}

	fn = dlsym(lib_handle,"somma");
	sum = (*fn)(a.arr,a.dim);

	fn = dlsym(lib_handle,"prod");
	p = (*fn)(a.arr,a.dim);
	stampa(&a);
	printf("Somma = %d\n",sum);
	printf("Prod = %d\n",p);
	free(s);
	dlclose(lib_handle);
	return 0;
}

