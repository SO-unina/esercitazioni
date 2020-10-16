# System call per la gestione dei processi

## Identificativo di un processo: ``getpid()``

Ogni processo ha un unico identificatore di processo chiamato PID (Process Identifier). Il PID è un intero compreso tra 0 e ``pid_max``. Di default il ``pid_max`` è pari a ``32768``; è possibile leggere tale valore dal file di sistema ``/proc/sys/kernel/pid_max``. E.g.:

```
$ cat /proc/sys/kernel/pid_max
32768
```

Il PID di un processo viene assegnato dal kernel all’atto della sua creazione. E' possibile ottenere il PID di un processo attraverso la chiamata di sistema ``getpid()``. E.g.:

```
#include <stdio.h>
#include <unistd.h>

int main(void)
{
 	int pid, ppid;
 	pid = getpid();
 	printf(”Sono il processo pid = %d\n”, pid);
 
	ppid = getppid();
 	printf(“Il mio processo genitore ha pid = %d\n”, ppid);

 	return 0;
}
```

Provando a compilare ed eseguire tale codice otteniamo:



