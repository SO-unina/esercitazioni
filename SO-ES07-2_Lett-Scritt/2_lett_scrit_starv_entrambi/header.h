#ifndef _HEADER_H_
#define _HEADER_H_

#define NUM_VOLTE 3
#define MUTEX_LETTORI_SCRITTORI 0
#define MUTEX_NUMSCRITTORI 1
#define MUTEX_NUMLETTORI 2
#define MUTEX_SCRITTORI  3

typedef long msg;

            
typedef struct {
 	  	 int numlettori;
 	  	 int numscrittori;
 	  	 msg messaggio;
} Buffer;



void InizioLettura (int, Buffer*);
void FineLettura(int, Buffer*);
void InizioScrittura(int, Buffer*);
void FineScrittura(int, Buffer*);
void Lettore(int, Buffer*);
void Scrittore(int, Buffer*);

#endif //_HEADER_H_
