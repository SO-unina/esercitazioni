# System call per la gestione dei processi

## Identificativo di un processo: ``getpid()`` e ``getppid()``

Ogni processo ha un unico identificatore di processo chiamato PID (Process Identifier). Il PID è un intero compreso tra 0 e ``pid_max``. Di default il ``pid_max`` è pari a ``32768``; è possibile leggere tale valore dal file di sistema ``/proc/sys/kernel/pid_max``. E.g.:

```
$ cat /proc/sys/kernel/pid_max
32768
```

Il PID di un processo viene assegnato dal kernel all’atto della sua creazione. E' possibile ottenere il PID di un processo attraverso la chiamata di sistema ``getpid()``. Inoltre, i processi in Unix sono organizzati gerarchicamente, ovvero, ogni processo ha un processo padre (eccetto il processo ``init``). Nel contesto di esecuzione del processo corrente, è possibile ottenre il PID del processo padre attraverso la chiamata di sistema ``getppid()``.

Il seguente codice stamperà a video il PID del processo corrente e il PID del suo processo padre:

```c
#include <stdio.h>
#include <unistd.h>

int main(void)
{
 	int pid, ppid;
 	pid = getpid();
 	printf("Sono il processo pid = %d\n", pid);
 
	ppid = getppid();
 	printf("Il mio processo genitore ha pid = %d\n", ppid);

 	return 0;
}
```

Provando a compilare ed eseguire tale codice (osservare i file [``Makefile``](Makefile) e [``main.c``](main.c)) otteniamo un output del genere:

```console
$ ./getpid_ex
Sono il processo pid = 19375
Il mio processo genitore ha pid = 14511
```

In Linux, sono stabiliti alcuni PID di default per specifici processi. Ad esempio:

- Processo ``scheduler``: PID = 0
- Processo ``init``: PID = 1
- Processo ``pagedaemon``: PID = 2

Per poter analizzare i PID associati ai processi attualmente sul sistema, possiamo utilizzare ancora il comando ``ps`` (vedi [lezione sui comandi shell](../SO-ES1-Introduzione-Linux/2_comandi_shell))
