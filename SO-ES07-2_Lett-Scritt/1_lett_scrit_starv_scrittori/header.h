		/*-------HEADER FILE-------------*/

#define MUTEXL 0
#define SYNCH 1
#define NUM_VOLTE 6


typedef long  msg;

typedef struct {

        int numlettori;
        msg messaggio;
    
} Buffer;


void Lettore(int,Buffer*);
void Scrittore(int,Buffer*);
