		/*-------HEADER FILE-------------*/

#define MUTEX_NUMLETTORI 0
#define MUTEX_LETTORI_SCRITTORI 1
#define NUM_VOLTE 6


typedef long  msg;

typedef struct {

        int numlettori;
        msg messaggio;
    
} Buffer;


void Lettore(int,Buffer*);
void Scrittore(int,Buffer*);
