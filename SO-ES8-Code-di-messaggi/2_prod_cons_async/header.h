				/*-----HEADER FILE----*/
#ifndef __HEADER
#define __HEADER
#define MESSAGGIO 1

typedef char msg [40];

typedef struct {
		long tipo;
		msg mess;
} Messaggio;

void Produttore(int queue,char* m);
void Consumatore(int queue);
void printMsgInfo(int queue);
#endif



