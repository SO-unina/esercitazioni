#define MSG_TYPE 1
#define STRING_MAX_DIM 11
#define INT_MAX_DIM 2

#define NUM_GENERATORS 3
#define NUM_FILTER 1
#define NUM_CHECKSUM 1
#define NUM_VISUAL 1


typedef struct {
        
        long type;
        char stringa[STRING_MAX_DIM];
        int array[INT_MAX_DIM];
        int var;

} message;

void generatore(int);
void filtro(int , int);
void checksum(int , int);
void visualizzatore(int);
