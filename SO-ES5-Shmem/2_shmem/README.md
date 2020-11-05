## Memoria condivisa: shared memory

I processi Unix (a differenza dei thread) non possono condividere la memoria, neanche i processi "parenti". Infatti, un processo figlio eredita una **copia** dei dati del processo padre: se i due processi modificano quei dati dopo la system call ``fork()``, ognuno modifica la propria copia.

Una memoria condivisa (SHM) è una porzione di memoria accessibile da più processi.

<p align="center">
<img src="../images/shared_memory_example.png" width="400">
</p>

L'utilizzo di una SHM in Linux prevede il seguente workflow:

- Creazione della SHM;
- Collegamento alla SHM;
- Uso della SHM;
- Scollegamento della SHM;
- Eliminazione della SHM.

Per utilizzare una SHM si può effettuare una
**richiesta esplicita** se il processo che vuole usare la SHM esistente ne conosce la chiave. Altrimenti, lo sviluppatore può utilizzare la ``fork()``, ovvero un processo può *collegarsi* alla SHM, dopodichè generare tramite fork i figli, i quali avranno automaticamente una copia del descrittore della SHM.

Letture e scritture su di una memoria condivisa non necessitano di particolari chiamate di sistema. Infatti, una shared memory può essere scritta e letta come una qualsiasi variabile facente parte dello spazio di indirizzamento del processo.

La massima quantità di dati che può essere letta/scritta con una singola istruzione da un processo dipende dall’architettura hardware. 
Per poter utilizzare una SHM gli header da includere sono i seguenti:

```c
#include <sys/shm.h>
#include <sys/ipc.h>
```

Il kernel mantiene una struttura dati interna speciale per ogni segmento di memoria condivisa. Il nome della struttura è ``shmid_ds``, ed è definita in ``linux/shm.h``:

```c
/* One shmid data structure for each shared memory segment in the system. */

struct shmid_ds {
	struct ipc_perm shm_perm;        /* operation perms */
	int     shm_segsz;               /* size of segment (bytes) */
	time_t  shm_atime;               /* last attach time */
	time_t  shm_dtime;               /* last detach time */
	time_t  shm_ctime;               /* last change time */
	unsigned short  shm_cpid;        /* pid of creator */
	unsigned short  shm_lpid;        /* pid of last operator */
	short   shm_nattch;              /* no. of current attaches */

	/* the following are private */
	unsigned short shm_npages;       /* size of segment (pages) */
	unsigned long  *shm_pages;       /* array of ptrs to frames -> SHMMAX */ 
	struct vm_area_struct *attaches; /* descriptors for attaches */
};
```

### Creazione di una shared memory: ``shmget()``

Per poter creare una shared memory ed utilizzarla è necessario usare la system call ``shmget()``:

```c
#include <sys/ipc.h>
#include <sys/shm.h>

int shmget(key_t key, size_t size, int shmflg);
```

dove,

- ``key``: chiave per identificare la SHM in maniera univoca nel sistema;
- ``size``: dimensione in byte della memoria condivisa;
- ``shmflg``: intero che specifica la modalità di creazione e dei permessi di accesso (IPC_CREAT, IPC_EXCL, permessi).
	
In caso di successo, la chiamata a ``shmget()`` restituisce un intero che è l'identificatore numerico (il descrittore) per l'utilizzo della memoria condivisa; in caso di fallimento, la chiamata restituisce ``-1``. 

#### Creazione shared memory con chiave IPC cablata e nessun flag impostato

```c
	...
	key_t chiave = 40;
	int ds_shm;
	ds_shm = shmget(chiave, 1024, 0);

	if(ds_shm < 0) {
   		// la risorsa non esiste! esci dal programma
    	perror(“errore shmget!”);
    	exit(1);
  	}
  	... Utilizza la shared memory già esistente...
```
La chiave utilizzata è il valore ``40`` e la dimensione impostata è di ``1Kb``. Non avendo usato nessun flag (flag pari a ``0``), se la shared memory non è stata già creata da un altro processo, la funzione ``shmget()`` produrrà un errore.

#### Creazione shared memory con chiave IPC cablata e flag ``IPC_CREAT``

```c
	...
	key_t chiave = 40;
  	int ds_shm;
  	ds_shm = shmget(chiave, 1024, IPC_CREAT | 0664);

  	if(ds_shm < 0) {
   		// qualcosa è andato storto (memoria esaurita, etc.)
    	perror(“errore shmget!”);
    	exit(1);
  	}
  	... Utilizza la shared memory (esistente o nuova)...
```

La chiave utilizzata è il valore ``40`` e la dimensione impostata è di ``1Kb``. La ``shmget()`` con ``IPC_CREAT`` impone **la creazione una nuova shared memory solo se non esiste già**. Se la shared memory con la chiave ``40`` esiste già, si ri-utilizza il segmento di memoria esistente. Inoltre, impostando i permessi a ``0664``, solo l’utente ed il gruppo proprietari hanno permessi di accesso read/write, mentre gli altri hanno solo accesso in lettura.

#### Creazione shared memory con chiave IPC cablata e flag ``IPC_CREAT`` e ``IPC_EXCL``

```c
	key_t chiave = 40;
 	int ds_shm = shmget(chiave,1024,IPC_CREAT|IPC_EXCL|0664);
 	if(ds_shm < 0) {
   		// La risorsa già esiste, viene segnalato con ds_shm<0.
		// Per ottenere un descrittore dalla SHM, occorre
   		// chiamare nuovamente shmget
   		// (senza né IPC_CREAT né IPC_EXCL)
   		
   		ds_shm = shmget(chiave, 1024, 0);
   		if(ds_shm<0) { 
   			/* errore */ 
   		}
	} else {
   		// La risorsa non esisteva, ed è stata appena creata.
   		// Il programma ha l’opportunità di inizializzarne
   		// il contenuto (ad esempio, «0» o una stringa vuota).
	}
	... Utilizza la shared memory ...
```

La chiave utilizzata è il valore ``40`` e la dimensione impostata è di ``1Kb``. La ``shmget()`` con ``IPC_CREAT`` e ``IPC_EXCL`` impone **la creazione una nuova shared memory solo se non esiste già, altrimenti ritorna un errore**. Infatti, se la shared memory con la chiave ``40`` esiste già, bisogna ottenere il descrittore della memoria condivisa già creata invocando la ``shmget()`` senza flag (``ds_shm = shmget(chiave, 1024, 0);``). Nel caso in cui la shared memory non esisteva già, viene creata ed è possibile per esempio inizializzarla. Per quanto riguarda i permessi associati abbiamo lo stesso effetto descritto nell'esempio precedente.


#### Creazione shared memory utilizzando ``ftok()``

```c
	key_t chiave = ftok("./eseguibile", 'k');
  	int ds_shm;
  	ds_shm = shmget(chiave, 1024, IPC_CREAT | 0664);

  	if(ds_shm < 0) {
    	// qualcosa è andato storto (memoria esaurita, etc.)
    	perror(“errore shmget!”);
    	exit(1);
  	}
  	... Utilizza la shared memory (esistente o nuova)...
```

In questo esempio non viene utilizzata una chiave cablata nel codice, ma più opportunamente si utilizza la system call ``ftok()`` per ottenere una IPC key univoca. Se due programmi differenti utilizzassero gli stessi parametri per la ``ftok()`` otterrebbero la stessa IPC key.


#### Creazione shared memory utilizzando ``IPC_PRIVATE``

```c
	int ds_shm = shmget(IPC_PRIVATE, 1024, IPC_CREAT|0664);

  	if(ds_shm < 0) {
    	// qualcosa è andato storto (memoria esaurita, etc.)
    	perror(“errore shmget!”);
    	exit(1);
  	}
  	... Utilizza la shared memory ...
```

In questo esempio si crea una shared memory senza assegnare una chiave, dal momento che IPC_PRIVATE equivale ad una chiave IPC pari a ``0``. Infatti, utilizzando il comando ``ipcs``, la chiave apparirà con il valore pari a ``0``. In questo caso, **la shared memory è utilizzabile solo dal padre e i suoi figli**, ovvero non è una soluzione corretta nel caso in cui avessimo più programmi eseguibili.


### Collegamento di una shared memory: ``shmat()``

Per poter utilizzare una shared memory è necessario effettuare il cosiddetto *attach* tramite la system call ``shmat()``:

```c
#include <sys/types.h>
#include <sys/shm.h>

void *shmat(int shmid, const void *shmaddr, int shmflg);
```

dove,

- ``shmid`` è l'identificatore del segmento di memoria;
- ``shmaddr`` è l'indirizzo dell’area di memoria del processo chiamante al quale collegare il segmento di memoria condivisa. Se si utilizza il valore ``0``, il kernel proverà a trovare una regione di memoria non mappata già. Quest'ultimo approccio è quello raccomandato; 
-  ``flag`` indica le opzioni (e.g., ``IPC_RDONLY`` per collegare in sola lettura).

La funzione ``shmat()`` restituirà l'indirizzo di memoria, nello spazio di indirizzamento del processo chiamante, al quale il segmento di memoria condivisa è stato collegato (*attached*). In caso di fallimento, la funzione restituirà il valore ``-1``.

### Operazione di controllo su una shared memory: ``shmctl()``

La chiamata di sistema ``shmctl()`` permette di invocare un comando di controllo su una shared memory esistente.

```c
#include <sys/ipc.h>
#include <sys/shm.h>

int shmctl(int shmid, int cmd, struct shmid_ds *buf);
```
dove,

- ``shmid`` è il descrittore della memoria condivisa su cui si vuole operare;

- ``cmd``: specifica il comando da eseguire. Valori validi sono i seguenti:
	- ``IPC_STAT``: copia le informazioni di stato della memoria condivisa (identificata da ``shmid``) dalla struttura dati interna al kernel nella struttura ``shmid_ds`` puntata dalla variable ``buf``
	- ``IPC_SET``: Permette di scrivere i valori di qualche membro della struttura ``shmid_ds`` puntata dalla variable ``buf`` alla struttura interna al kernel;
	- ``IPC_RMID``: marca da eliminare la shared memory, rimuovendola solo quando non vi sono più processi collegati;
	- ``SHM_LOCK``: impedisce che il segmento di memoria condivso venga swappato o paginato.

- ``buf``: puntatore ad una struttura di tipo ``shmid_ds`` (parametro di ingresso nel caso del comando ``IPC_SET``, parametro di uscita nel caso del comando ``IPC_STAT``)

La funzione ``shmctl()`` restituisce ``-1`` in caso di fallimento.


### Esempio completo

Si vuole creare una shared memory con chiave nulla (``IPC_PRIVATE``) e dimensione pari ad un intero.

```c
	...
 	key_t chiave = IPC_PRIVATE;
 	int ds_shm = shmget(chiave, sizeof(int),IPC_CREAT|0664);
 	
 	if(ds_shm < 0) { 
 		perror(“errore shmget!”);
 		exit(1); 
 	}

 	int * p = (int*) shmat(ds_shm, NULL, 0);
 	if(p==(void*)-1) { 
 		perror(“errore shmget!”);
 		exit(1); 
 	}

 	key_t pid = fork();
 	if(pid==0) {
    	// processo figlio
    	*p = 123;
    	exit(0);
 	} else if(pid>0) {
    	// processo padre
    	wait(NULL);
    	printf(“Contenuto SHM: %d\n”, *p);
 	}
 	...
```

Analizzare il codice in [main_es_1_ex.c](main_es_1_ex.c). Provare a compilare ed eseguire il codice:

```console
$ make
$ ./main_es_1_ex
Dettagli shared memory creata:
...chiave IPC shm: 0
...descrittore shm: 196608
...indirizzo dopo attach: 0x10c645000
Contenuto SHM: 123
```



	





