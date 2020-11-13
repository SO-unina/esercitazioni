				/*-----HEADER FILE----*/
#ifndef __HEADER
#define __HEADER
#define MESSAGGIO 1 /* posso usare un tipo di messaggio uguale a 0? No
                        perchè 0 è utilizzato dal sistema per indicare
                        ricevi il primo messaggio inserito nella coda
                    */



typedef char msg [40];

typedef struct {
		long tipo;
		msg mess;
} Messaggio;

void Produttore(int queue,char* m);
void Consumatore(int queue);
void printMsgInfo(int queue);
#endif



