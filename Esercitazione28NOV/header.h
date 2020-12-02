		/*-------HEADER FILE-------------*/

#define SYNCH 0
#define MUTEXL 1

#define MAX_STR_DIM 15

typedef struct {

        int numlettori;
        int numscrittori;
        char stringa [MAX_STR_DIM];

} Buffer;

void InizioLettura (int, Buffer*);
void FineLettura(int, Buffer*);
void InizioScrittura(int, Buffer*);
void FineScrittura(int, Buffer*);
