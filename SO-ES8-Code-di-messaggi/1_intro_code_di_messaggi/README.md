## Semafori

UNIX (System V), come anche Linux, mette a disposizione primitive che supportano la comunicazione fra processi (anche indipendenti) basata sullo **scambio di messaggi
**. Un **messaggio** è identificato come un blocco di informazioni senza alcun formato predefinito.

In particolare, UNIX supporta il modello nel quale lo scambio di messaggi non avviene direttamente tra il mittente e il destinatario, ma avviene tra un utente e una **mailbox** (comunicazione indiretta).

<p align="center">
<img src="../images/mailbox.png" width="400">
</p>

UNIX System V mette a disposizione unicamente le primitive di **send asincrona** e di **receive bloccante** e **receive non bloccante**.

Una mailbox può essere vista come una coda di messaggi. Essa é caratterizzata da:

- Una chiave, come per tutte le risorse IPC (e.g., segmenti di memoria condivisa, semafori);
- Un proprietario, ovvero l’utente che la istanzia;
- Un gruppo di appartenenza;
- Un insieme di permessi di accesso, indicate dalla solita stringa con 3 numeri a 3 bit.

### Operazioni su code di messaggi

#### Creazione di una coda di messaggi: ``msgget()``

Per creare una nuova coda di messaggi, o accedere ad una esistente, bisogna invocare la system call ``msgget()``.

```c
#include <sys/types.h>       
#include <sys/ipc.h>
#include <sys/msg.h>

int msgget(key_t key, int msgflg);
```




#### Invio di un messaggio: ``msgsnd()``

#### Ricezione di un messaggio: ``msgrcv()``

#### Operazioni di controllo su una coda di messaggi: ``msgctl()``


