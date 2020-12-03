#include <pthread.h>

/*
#define OK_PROD 0
#define OK_CONS 1
*/ //NOONOOOOOOOOOOOOO

typedef long msg;

struct ProdCons{

        msg mess;

        int ok_produzione;
        int ok_consumo;

        //Monitor m; NOOOOOOOOOOOOOOO!
        //

        //mutex: accesso al monitor
        //
        pthread_mutex_t mutex;
        
        // var cond: posso produrre, posso consumare
        //
        pthread_cond_t ok_prod_cv;
        pthread_cond_t ok_cons_cv;

};

void *Consumatore(void *);
void *Produttore(void *);

void Produci(struct ProdCons *, msg m);
msg Consuma(struct ProdCons *);

void InizioConsumo(struct ProdCons *);
void InizioProduzione(struct ProdCons *);
void FineConsumo(struct ProdCons *);
void FineProduzione(struct ProdCons *);




