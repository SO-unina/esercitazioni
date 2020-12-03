## Semafori

I semafori sono variabili speciali (sostanzialmente dei contatori) utilizzate per la **cooperazione** e la **competizione** tra processi.
Due o più processi competono o cooperano attraverso l’uso di segnali, in modo tale che un processo può essere forzato a sospendersi in un determinato punto finché non riceve un segnale. 
I processi condividono tra loro una **istanza di semaforo** ``s``. Tramite questa variabile, un processo può inviare un segnale sul semaforo ``s`` tramite una procedura ``signal(s)``. Per ricevere un segnale sul semaforo ``s`` si invoca la primitiva ``wait(s)``: se il segnale non è stato ancora ricevuto, il processo si sospende.
Il modello contettuale semaforico è mostrato nella seguente figura:

<p align="center">
<img src="../images/semafori_modello.png" width="600">
</p>

L'uso classico di un semaforo è per implementare un meccanismo di **locking** che garantisca la mutua esclusione tra processi.

In particolare, è possibile implementare le operazioni di *wait* e *signal* grazie alle operazioni su strutture semaforiche.

### Strutture semaforiche nel kernel

Il kernel di Linux mantiene due strutture fondamentali per implementare un semaforo: ``sem`` e ``semid_ds``. 

In particolare, viene utilizzato un array di semafori (*semaphore set*), dove ogni semaforo è descritto dalla struttura ``sem``. La struttura ``sem`` è definita in ``linux/sem.h``:

```c
struct sem {
	short   sempid;         /* pid of last operation */
   	ushort  semval;         /* current value */
   	ushort  semncnt;        /* num procs awaiting increase in semval */
   	ushort  semzcnt;        /* num procs awaiting semval = 0 */
};
```

dove,

- ``sem_pid`` è il PID del processo che ha eseguito l'ultima operazione sul semaforo;
- ``sem_semval`` è il valore corrente del semaforo;
- ``sem_semncnt`` è il numero di processi che sono in attesa che una data risorsa diventi disponibile;
- ``sem_semzcnt`` è il numero di processi che sono in attesa che il valore del semaforo sia pari a ``0`` (i.e., utilizzo delle risorse pari al 100%).

Invece, la struttura ``semid_ds`` viene creata per ogni *semaphore set* all'interno del sistema.

```c
/* One semid data structure for each set of semaphores in the system. */
struct semid_ds {
	struct ipc_perm sem_perm;       /* permissions .. see ipc.h */
   	time_t          sem_otime;      /* last semop time */
   	time_t          sem_ctime;      /* last change time */
   	struct sem      *sem_base;      /* ptr to first semaphore in array */
   	struct wait_queue *eventn;
   	struct wait_queue *eventz;
   	struct sem_undo  *undo;         /* undo requests on this array */
   	ushort          sem_nsems;      /* no. of semaphores in array */
};
```

dove,

- ``sem_perm`` è un'istanza della struttura ``ipc_perm`` che è definita in  ``linux/ipc.h``. Qeusta struttura mantiene le informazioni sui permessi impostati per il semaforo;
- ``sem_otime`` è il tempo dell'ultima operazione ``semop()`` fatta;
- ``sem_ctime`` è il tempo dell'ultimo cambiamento fatto alla struttura in esame;
- ``sem_base`` è il puntatore al primo semaforo nell'array dei semafori
- ``sem_undo`` è il numero di richieste *undo* nell'array
- ``sem_nsems`` è il numerdo di semafori nell'array di semafori (*semaphore set*).

### Operazioni su un semaforo

#### Creazione: ``semget()``

La funzione che permette di creare un nuovo semaforo (o meglio un *semaphore set*) è la system call ``semget()``:

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semget(key_t key, int nsems, int semflg);
```

Tale funzione restituisce l'identificatore (il descrittore) del *semaphore set* associato alla chiave specificata in ``key`` (ottenibile cablando un valore, con ``IPC_PRIVATE``, o con ``ftok()``). Un nuovo array di ``nsems `` semafori verrà creato in accordo ai flag specificati in ``semflg`` (vedere il significato dei flag in [IPC intro](../SO-ES5-Shmem/1_IPC_intro/README.md)). Sostanzialmente, impostando ``IPC_CREAT`` si crea il semaforo se non esiste già, mentre usando ``IPC_CREAT | IPC_EXCL`` la ``semget()`` fallisce se il semaforo è già presente.
In caso di successo, la ``semget()`` restituisce il descrittore del *semaphore set*, altrimenti, viene restituito il valore ``-1``.

Il numero massimo di semafori in un *semaphore set* è definito in ``linux/sem.h`` come:

```c
#define SEMMSL  32      /* <=512 max num of semaphores per id */
```

Per creare un array semaforico di 2 semafori con chiave nulla, utilizzare il seguente snippet di codice:

```c
key_t sem_key = IPC_PRIVATE;
int sem_ds = semget(sem_key, 2, IPC_CREAT | 0664);
```

#### Inizializzazione e rimozione: ``semctl()``

Per poter inizializzare e rimuovere un semaforo si utilizza la system call ``semctl()``.

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semctl(int semid, int semnum, int cmd, ...);
```

La system call ``semctl()`` esegue l'operazione specificata in ``cmd`` sul *semaphore set* identificato da ``semid`` e sull'``semnum``-esimo semaforo dell'array.

N.B.: I semafori all'interno del *semaphore set* sono numerati partendo da ``0``.

Alcuni possibili valori da usare per ``cmd`` sono:

- ``SETVAL``: Imposta il valore, specificato come quarto parametro, di uno specifico semaforo identificato da ``semnum`` all'interno del *semaphore set* ``semid``.
- ``IPC_RMID``: Rimuove il *semaphore set* ``semid`` dal kernel.

Per altri utilizzi di ``semctl()`` riferirsi al manuale (``man semctl``).

In definitiva, per poter inizializzare un array semaforico, a due valori ``val1`` e ``val2``:

```c
semctl(sem_ds, 0, SETVAL, val1);
semctl(sem_ds, 1, SETVAL, val2);
```

Per poter rimuovere un array semaforico (in questo caso la variable ``num_sem`` viene ignorata):

```c
semctl(id_sem, num_sem ,IPC_RMID);
```

#### Semaphore operations: ``semop()``

Per eseguire operazioni sulla struttura identificativa di un semaforo (vedi ``sem``) è necessario utilizzare la system call ``semop()``:

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semop(int semid, struct sembuf *sops, size_t nsops);
```

In particolare, ``semop()`` esegue operazioni sui semafori nell'array identificato da ``semid``. Ognuno degli ``nsops`` elementi, riferiti dal puntatore ``sops``, specifica un'operazione da compiere sul semaforo. L’operazione è descritta da una struttura, struct ``sembuf``, la quale include i seguenti campi:

```c
struct sembuf{
	unsigned short sem_num;  /* semaphore number */
   	short          sem_op;   /* semaphore operation */
   	short          sem_flg;  /* operation flags */
}
```

Due sono i valori che può assumere ``sem_flg``: ``IPC_NOWAIT`` e ``SEM_UNDO``. Se si specifica ``SEM_UNDO``, l'operazione sarà annullata nel momento in cui il processo che l'ha eseguita termina.

L'insieme delle operazioni specificate da ``sops`` sono eseguite in maniera **atomica**, ossia tutte le operazioni indicate devono poter essere effettuate simultaneamente, altrimenti la ``semop`` si blocca o ritorna immediatamente.

Ogni operazione è eseguita sul semaforo individuato da ``sem_num``. In altre parole ``sem_num`` indica su quale semaforo, tra quelli presenti nel *semaphore set*, dovrà essere eseguita l’operazione. 


### Implementazione delle primitive ``wait`` e ``signal`` tramite la struttura semaforica

Ricordando la system call ``semop()``, i valori che può assumere il campo ``sem_op`` specificano tre possibili tipologie di operazioni che si possono compiere sul semaforo. Grazie a queste 3 modalità, è possibile implementare le primitive di *wait* (``sem_op < 0``), *wait for zero* (``sem_op == 0``), e *signal* (``sem_op > 0``).

#### Implementazione della *signal*: ``sem_op > 0``

Se ``sem_op`` è un intero positivo, l'operazione consisterà nell'addizionare il valore di ``sem_op`` al valore ``semval`` del semaforo. 

```c
	semval += sem_op
```

Al fine di implementare l'operazione di *signal*, il processo chiamante dovrà necessariamente avere i permessi per modificare i valori del semaforo. 

Questa operazione non causa in alcun caso il blocco del processo. Nel caso in cui sia specificato il flag ``SEM_UNDO``, il kernel sottrae il valore ``sem_op`` dal valore del *semaphore adjustment* (``semadj``), il quale identifica un contatore delle operazioni *undo*.

Secondo quanto descritto precedentemente, l'implementazione di una primitiva ``signal`` su semaforo è la seguente:

```c
void Signal_Sem (int id_sem,int numsem){
	struct sembuf sem_buf;
	sem_buf.sem_num = numsem;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = 1;
	semop(id_sem, &sem_buf, 1);   //semaforo verde
}
```
Notare l'operazione fatta con ``semop()`` e i valori per ogni campo della struttura ``sembuf``, in particolare ``sem_buf.sem_op = 1``..

#### Implementazione della *wait*: ``sem_op < 0``

Se ``sem_op`` ha valore negativo, l'operazione si articolerà come di seguito:

- se ``semval ≥ |sem_op|`` l'operazione procede immediatamente e il valore assoluto di   ``sem_op`` è sottratto da ``semval``. Se specificato il flag ``SEM_UNDO`` il kernel addiziona il valore ``sem_op`` dal valore del *semaphore adjustment* (``semadj``), il quale identifica un contatore delle operazioni *undo*.

- se ``semval < |sem_op|``, se specificato il flag ``IPC_NOWAIT`` la system call fallisce (``errno =  EAGAIN``); altrimenti il valore del campo ``semncnt`` (il contatore dei processi sospesi nell'attesa che il valore del semfaro venga incrementato) viene incrementato di ``1`` e il processo si sospende finchè una delle seguenti condizioni si avvera:
	
	- ``semval ≥ |sem_op|``,  quando questa condizione sarà verificata il valore di  ``semncnt`` sarà decrementato e il valore del semaforo sarà 
	
		```c
		semval -= |sem_op|
		```

		Se specificato ``SEM_UNDO`` il sistema aggiornerà il contatore “undo count” (``semadj``)  del processo per il semaforo in questione. 

	- Il semaforo viene rimosso. In questo caso la system call fallisce (``errno = EIDRM``). 

Secondo quanto descritto precedentemente, l'implementazione di una primitiva ``wait`` su semaforo è la seguente:

```c
void Wait_Sem (int id_sem, int numsem){
	struct sembuf sem_buf;
	sem_buf.sem_num = numsem;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = -1;
	semop(id_sem, &sem_buf, 1);   //semaforo rosso
}
```
Notare l'operazione fatta con ``semop()`` e i valori per ogni campo della struttura ``sembuf``, in particolare ``sem_buf.sem_op = -1``.


#### Implementazione della *wait-for-zero*: ``sem_op == 0``

Se ``sem_op`` ha valore nullo, l’operazione specificata (*wait-for-zero*) è articolata nei seguenti passi:

- se il valore ``semval`` è zero, l’operazione procede immediatamente (il processo non si sospende)
- Altrimenti (``semval ≠ 0``) si procederà come di seguito:
	- se è specificato il flag ``IPC_NOWAIT`` in ``sem_flg``, la system call fallisce 	restituendo il codice di errore ``EAGAIN`` a mezzo della variabile ``errno``
	- altrimenti la variabile ``semzcnt`` (che indica il numero di processi sospesi nell’attesa che il valore del semaforo diventi nullo) è incrementata di ``1``, forzando il processo a sospendersi finché una delle seguenti condizioni si verificherà: 
 		1. ``semval`` diventa ``0``, (allora il valore di ``semzcnt`` è decrementato). 
		2. Il semaforo è rimosso: la system call fallisce (``errno = EIDRM``). 

```c
void Wait_for_Zero_Sem (int id_sem, int numsem){
	struct sembuf sem_buf;
	sem_buf.sem_num = numsem;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = 0;
	semop(id_sem, &sem_buf, 1);   //semaforo rosso
}
```
