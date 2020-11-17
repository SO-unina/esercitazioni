#define MUTEXL 0
#define MUTEXS 1
#define SYNCH 2
#define MUTEX 3

#define NUM_VOLTE 6

typedef long msg;

typedef struct {

        int numlettori;
        int numscrittori;
        msg messaggio;

} Buffer;

void Lettore(int, Buffer *);
void Scrittore(int, Buffer *);
