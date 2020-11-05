## Risorse IPC, IPC ID, e IPC key

Ogni risorsa IPC (detta anche *IPC object*) è identificata nel kernel da un valore univoco denominato **ID**. Per ottenere un ID per una risorsa IPC è necessario utilizzare una cosiddetta chiave IPC (**IPC key**). Una IPC key può essere:

- Cablata (*hardcoded*) nel codice, portando a potenziali problemi di consistenza, se tale chiave è già utilizzata nel sistema;
- Generata dal sistema mediante la chiamata di sistema  ``ftok()``
- Impostata con la macro ``IPC_PRIVATE`` che equivale a valore ``0``. In questo caso la risorsa IPC è priva di chiave, ed è accessibile solo al processo creatore ed ai suoi figli.

### La chiamata di sistema ``ftok()``

La chiamata di sistema ``ftok()`` ha la seguente firma:

```c
#include <sys/types.h>
#include <sys/ipc.h>

key_t ftok(const char *pathname, int proj_id)
```

In particolare, ``ftok()`` utilizza il *pathname* e *project identifier* per ottenere una IPC key. L'utilizzo classico è:

```c
key_t mykey;
mykey = ftok("./eseguibile", 'a');
```

La primitiva restituira una chiave IPC ottenuta da una funzione aritmetica che combina l'*inode number* e il *minor device number* del file `eseguibile` indicato come primo argomento e del carattere indicato come secondo argomento (`a`).

Due processi che usano gli stessi parametri ottengono le stesse chiavi. ``ftok()`` permette di evitare di cablare una chiave nel programma, e quindi di evitare eventuali incosistenze.

### I comandi ``ipcs`` e ``ipcrm``

Il comando ``ipcs`` visualizza tutte le strutture IPC (code di messaggio, shared memory, e semafori) allocate, mostrandone la chiave IPC, l'identificatore del descrittore della risorsa, l'utente proprietario, i permessi per la risorsa, e informazioni legate al tipo di risorsa IPC. Ad esempio:

```console
$ ipcs

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status

------ Semaphore Arrays --------
key        semid      owner      perms      nsems
0x00000000 1605632    www-data   600        1
```

E' possibile utilizzare i seguenti flag per mostrare solo alcune risorse IPC:

* ``-m, --shmems``. Write information about active shared memory segments.
* ``-q, --queues``. Write information about active message queues.
* ``-s, --semaphores``. Write information about active semaphore sets.
* ``-a, --all``. Write information about all three resources (default).

Ad esempio, per poter visualizzare solo le shared memory allocate correntemente nel sistema, basta eseguire:

```console
$ ipcs -m

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status
```

Il comando ``ipcrm`` permette di rimuovere una data struttura IPC dato il suo identificativo. Il comando è molto utilie quando lo sviluppatore non ha rimosso esplicitamente le strutture allocate (es. in caso di terminazione anomala). Ad esempio, se si vuole eliminare la shared memory avente id pari a ``1376256``:

```console
$ ipcrm -m 1376256
```

### Le primitive ``...get`` e ``...ctl``, e la struttura dati ``...id_ds``

La primitiva ``get`` utilizza la IPC key, ed opportuni parametri, per restituire al processo un descrittore della risorsa. Se la risorsa non esiste, deve essere creata.

Dato il descrittore della risorsa IPC, la primitiva ``ctl`` (control), permette di:

- Verificare lo stato di una risorsa;
- Cambiare lo stato di una risorsa
- Rimuovere una risorsa

Le strutture IPC create sono permanenti, ovvero la loro eliminazione richiede l'invocazione di un'apposita chiamata di sistema.

#### La primitiva ``get``

La primitiva ``get`` ha la seguente firma:

```
int ...get (key_t key, ..., int flag);
```

dove,

- ``key`` specifica la chiave dell’oggetto IPC. Tale chiave è un valore intero arbitrario che può essere cablato nel codice, generato da ``ftok()``, oppure impostato con la macro ``IPC_PRIVATE``;

- ``flag`` indica la modalità di acquisizione della risorsa e i permessi di accesso. E' possibile specificare in *or logico* (con il carattere pipe ``|``) le seguenti: 

	- Macro ``IPC_CREAT`` definita in ``sys/ipc.h``: impone di creare una nuova risorsa se non ne esiste già una con la chiave indicata. Se la risorsa già esiste, il flag è ininfluente.

	- Macro ``IPC_EXCL`` definita in  ``sys/ipc.h``: utilizzabile con ``IPC_CREAT`` per imporre di ritornare un errore se la risorsa già esiste. Questa modalità è utile per evitare di inizializzare la risorsa IPC più volte.
	- **Permessi di accesso**: sono specificati con la notazione ottale. Per esempio, il valore ``0664`` indica i permessi di lettura e scrittura per ``user`` e ``group``, e di sola lelttura per ``others`` (N.B.: lo 0 è per indicare la notazione ottale).

	 
#### La primitiva ``ctl``

La primitiva ``ctl`` ha la seguente firma:

```c
int ...ctl (int desc, ..., int cmd, ...);
```

dove,

- ``desc``: indica il descrittore della risorsa IPC;
- ``cmd``: specifica il comando da eseguire. E' possibile scegliere tra:
	- ``IPC_RMID``: rimozione della risorsa indicata
	- ``IPC_STAT``: richiede informazioni statistiche sulla risorsa indicata
	- ``IPC_SET``: richiede al sistema la modifica di un
	sottoinsieme degli attributi della risorsa (e.g. i permessi di accesso)


#### La struttura ``...id_ds``

La creazione di un oggetto IPC genera anche una struttura dati interna al kernel. La struttura è diversa per i vari tipi di oggetto ed ha la forma ``...id_ds``. Questa struttura contiene:

- una struttura di permessi ``ipc_perm``:

```
	ushort cuid, cgid; // creator user & group id 
	ushort uid, gid; 	// owner user & group id
	ushort mode; 		// r/w permissions 
```

- PID dell’ultimo processo che ha modificato la risorsa;
- tempi dell’ultimo accesso o modifica;
- ...





