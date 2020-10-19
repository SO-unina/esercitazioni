## Esecuzione di un programma: la famiglia``exec()``

L'unico modo in cui un programma può essere eseguito da Unix è che il processo corrente invochi la chiamata di sistema appartenente alla famiglia ``exec()`` (eccetto per il processo init). Il nuovo programma viene eseguito nel contesto del processo chiamante, cioè il PID non cambia. Se non ci sono errori, la chiamata a ``exec()`` non fa ritorno e il controllo passa al nuovo programma, mentre ritorna al chiamante solo se si verifica un'errore.

Il processo dopo la chiamata ad ``exec()``:

- Mantiene la stessa *process structure*;
- Ha codice, dati globali, stack e heap nuovi;
- Riferisce una nuova *text structure*;
- Mantiene *user area* (a parte PC e informazioni legate al codice) e stack del kernel.

Esistono varie versioni della ``exec()``:

```c
//Percorso completo dell’eseguibile; parametri tramite lista
int execl(char *path, char *arg0, .., char *argn, (char *) 0);

//Nome dell’eseguibile (da cercare nelle cartelle di sistema); parametri tramite lista
int execlp(char *nomefile, char *arg0, .., char *argn, (char *) 0);

//Percorso completo dell’eseguibile; parametri tramite array
int execv(const char *path, char *const argv[]);

//Nome dell’eseguibile (da cercare nelle cartelle di sistema); parametri tramite array
int execvp(const char *nomefile, char *const argv[]);
```

Ad esempio, per poter invocare un comando chiamato ``program``, basta generare un processo figlio e richiamare una delle system call appartenenti alla famiglia ``exec()``:

```c
pid = fork()
if (pid == 0) {
	// codice figlio
	...
	if (execlp("program",...) < 0){
   		perror(“exec fallita”);
	   exit(1);
	}

} else if (pid < 0){
	perror(“fork fallita”);
}
// Il padre continua da questo punto in poi.
// Generalmente, effettua una wait() sul figlio.
```

Analizzare il programma [main.c](main.c) che fa uso della funzione ``execl()`` per poter eseguire il comando ``ls -l``.
Provando ad eseguire il programma main.c, otterremmo una cosa del genere:

```console
$ ./main
ESECUZIONE del comando 'ls -l'...
total 40
-rw-r--r--@ 1 so  so  1930 Oct 19 13:05 README.md
-rwxr-xr-x  1 so  so  8708 Oct 19 13:07 main
-rw-r--r--  1 so  so   592 Oct 19 13:07 main.c
Il figlio 77657 ha terminato l'esecuzione con stato: 0
```


L'``exec()`` è anche nota come "sostituzione di codice". Questo significa che dopo la chiamata, è lo stesso processo che esegue, ma esegue un programma differente.

Le possibili implementazioni della ``exec()`` sono due:

- Sovra-scrittura del segmento di memoria corrente con nuovi valori;
- Allocazione di nuovi segmenti di memoria, inizializzazione di questi con i valori del nuovo processo e deallocazione dei segmenti *vecchi*.
