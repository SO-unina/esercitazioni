## Esecuzione di un programma: la famiglia``exec()``

L'unico modo in cui un programma può essere eseguito da Unix è che il processo corrente invochi la chiamata di sistema appartenente alla famiglia ``exec()`` (eccetto per il processo init). Il nuovo programma viene eseguito nel contesto del processo chiamante, cioè il PID non cambia. Se non ci sono errori, la chiamata a ``exec()`` non fa ritorno e il controllo passa al nuovo programma, mentre ritorna al chiamante solo se si verifica un'errore.

Il processo dopo la chiamata ad ``exec()``:

- Mantiene la stessa *process structure*;
- Ha codice, dati globali, stack e heap nuovi;
- Riferisce una nuova *text structure*;
- Mantiene *user area* (a parte PC e informazioni legate al codice) e stack del kernel.

L'``exec()`` è anche nota come "sostituzione di codice". Questo significa che dopo la chiamata, è lo stesso processo che esegue, ma esegue un programma differente.

Le possibili implementazioni della ``exec()`` sono due:

- Sovra-scrittura del segmento di memoria corrente con nuovi valori;
- Allocazione di nuovi segmenti di memoria, inizializzazione di questi con i valori del nuovo processo e deallocazione dei segmenti *vecchi*.

Esistono varie versioni della ``exec()``:

```c
//Percorso completo dell’eseguibile; parametri tramite lista
int execl(char *path, char *arg0, .., char *argn, (char *) 0);

//Nome dell’eseguibile (da cercare nelle cartelle di sistema); parametri tramite lista
int execlp(char *nomefile, char *arg0, .., char *argn, (char *) 0);
```

Sia in ``execl()`` e ``execlp()`` notare come si usi il carattere nullo (``(char *) 0``, oppure è possibile usare ``NULL``) per indicare la fine dei parametri da passare al comando.

Altre versioni della ``exec()`` sono:

```c
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

### Esecuzione del comando ``ls -l`` tramite ``exec()``

Analizzare il programma [main_ls.c](main_ls.c) che fa uso della funzione ``execl()`` per poter eseguire il comando ``ls -l``. Notare come nella chiamata a ``execl()`` abbiamo: 

```c
execl("/bin/ls", "ls", "-l", NULL);
```
Ovvero:

- Il primo parametro è il path del comando ``ls`` (includendo il suo nome);
- Il secondo parametro è il nome del comando (``ls``);
- Il terzo parametro è il flag ``-l``;
- L'ultimo parametro sia ``NULL``.



Provando ad eseguire il programma main.c, otterremmo una cosa del genere:

```console
$ gcc -o main_ls main_ls.c
$ ./main_ls
ESECUZIONE del comando 'ls -l'...
total 40
-rw-r--r--@ 1 so  so  1930 Oct 19 13:05 README.md
-rwxr-xr-x  1 so  so  8708 Oct 19 13:07 main
-rw-r--r--  1 so  so   592 Oct 19 13:07 main.c
Il figlio 77657 ha terminato l'esecuzione con stato: 0
```

### Parametri del ``main()`` passati tramite command line 

Nell'utilizzo di ``exec()``, è possibile sfruttare i cosiddetti parametri della *command line* da passare al ``main()``. In particolare, è possibile utilizzare la seguente firma per la funzione ``main()``:

```c
int main(int argc, char *argv[]){

	...
	return 0;
}
```

dove ``argc`` indica il numero di stringhe puntate dal parametro ``*argv[]`` che invece sta ad indicare il puntatore all'array di stringhe in ingresso: ``argv[0]`` indica la prima stringa, ``argv[1]`` la seconda, e così via.

Analizziamo il codice in [main_cp.c](main_cp.c). Questo programma invoca il comando ``/bin/cp`` su due parametri che sono passati tramite linea di comando al ``main()``:

```c
execl("/bin/cp", "cp", argv[1], argv[2], 0);
```

Notare come l'indice dei parametri di ingresso parta da ``1`` e non da ``0``; questo perchè la stringa ``argv[0]`` identifica il nome dell'eseguibile che state avviando (provate a stampare la variabile ``argv[0]``).
Compilando il programma, e provandolo ad eseguire, otterremo come di seguito:

```console
$ gcc -o main_cp main_cp.c
$ ./main_cp main_cp.c main_cp.c.backup
Sono il processo padre, con PID 87487
Sono il processo figlio, con PID 87488
Command line passata al main():
argv[0]: ./main_cp
argv[1]: main_cp.c
argv[2]: main_cp.c.backup
Attendo 3 secondi
.
.
.
Copia effettuata con successo!
Il processo padre termina```







