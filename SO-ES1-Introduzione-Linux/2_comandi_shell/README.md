# Comandi di base

## Il comando ``sudo``

``sudo`` è un'applicazione che permette di eseguire i comandi con gli stessi privilegi dell'utente di root (l'utente più privilegiato). E.g.:

```shell
$ sudo COMANDO
```

## Installazione pacchetti

In Ubuntu, il package manager a linea di comando è l'applicazione ``apt``

Per poter installare i manuali per le librerie basate su POSIX (e.g., IPC, etc.), e installare tutti gli applicativi di sistema (e.g., make, gcc, etc.), eseguire i seguenti comandi con ``sudo``:

```shell
sudo apt-get install manpages-posix
sudo apt-get install manpages-posix-dev
sudo apt-get install build-essential
```

## Documentazione comandi: il comando ``man``

Per poter visualizzare la documentazione di uno specifico comando, possiamo utilizzare il comando ``man`` che prende in ingresso come primo parametro il comando di cui vogliamo la documentazione. E.g.:

```shell
$ man ls

LS(1)                                                                                                           User Commands                                                                                                           LS(1)

NAME
       ls - list directory contents

SYNOPSIS
       ls [OPTION]... [FILE]...

DESCRIPTION
       List information about the FILEs (the current directory by default).  Sort entries alphabetically if none of -cftuvSUX nor --sort is specified.

       Mandatory arguments to long options are mandatory for short options too.

       -a, --all
              do not ignore entries starting with .

       -A, --almost-all
              do not list implied . and ..
              
...
```


## Percorso relativo e percorso assoluto

Il **percorso assoluto** indica come giungere ad un file partendo dalla directory radice ``/``. E.g., un path assoluto è del tipo ``/home/user/main.c``.

Un **percorso relativo** fa riferimento alla directory corrente. Il comando per ottenere la directory corrente è ``pwd``:

```shell
$ pwd
/home/so
```

## Lista di file e directory

Per ottenere la lista di file e directory, è possibile utilizzare il comando ``ls``:

```shell
$ ls
Documenti  echo_test  echo_test_sort  Immagini  Modelli  Musica  prova  prova.c  Pubblici  Scaricati  Scrivania  snap  Video
```

Per ottenere una lista più dettagliata, visualizzando i permessi, e anche la grandezza di ogni file e directory, è possibile utilizzare il comando ``ls -lah``:

```shell
$ ls -lah
totale 128K
drwxr-xr-x 19 so   so   4,0K ott  7 13:37 .
drwxr-xr-x  3 root root 4,0K set 27 18:57 ..
drwxr-xr-x  2 so   so   4,0K set 27 19:09 Documenti
-rw-rw-r--  1 so   so     24 ott  7 13:34 echo_test
-rw-rw-r--  1 so   so     24 ott  7 13:38 echo_test_sort
drwxr-xr-x  2 so   so   4,0K set 27 19:09 Immagini
drwxr-xr-x  2 so   so   4,0K set 27 19:09 Modelli
drwxr-xr-x  2 so   so   4,0K set 27 19:09 Musica
-rwxrwxr-x  1 so   so    17K ott  7 13:07 prova
-rw-rw-r--  1 so   so     74 ott  7 13:06 prova.c
drwxr-xr-x  2 so   so   4,0K set 27 19:09 Pubblici
drwxr-xr-x  2 so   so   4,0K set 27 19:09 Scaricati
drwxr-xr-x  2 so   so   4,0K set 27 19:09 Scrivania
drwxr-xr-x  2 so   so   4,0K set 27 19:09 Video
```

> **_N.B.:_** La dimensione delle directory **non** è la somma delle dimensioni dei file contenuti. In realtà, è la dimensione del **descrittore** di quella directory (il descrittore della directory è un file!), che di default è 4Kb.


## Utilizzo delle directory

- Entrare in una directory

```shell
$ ls
Documenti  echo_test  echo_test_sort  Immagini  Modelli  Musica  prova  prova.c  Pubblici  Scaricati  Scrivania  snap  Video
$ cd Documenti/
~/Documenti$ pwd
/home/so/Documenti
```

- Creare una directory

```shell
$ mkdir new_directory

```

## Permessi

Ogni file e directory in Linux hanno un insieme di permessi definiti attraverso una maschera di 9 bit.

<p align="center">
<img src="images/permessi_image_001.png" width="300" > 
</p>

<p align="center">
<img src="images/permessi_image_002.png" width="300" > 
</p>

E' possibile visualizzare i permessi di una data directory o file attraverso il comando ``ls -l``:

```shell
$ ls -l
totale 68
drwxr-xr-x 2 so so  4096 set 27 19:09 Documenti
-rw-rw-r-- 1 so so    24 ott  7 13:34 echo_test
-rw-rw-r-- 1 so so    24 ott  7 13:38 echo_test_sort
drwxr-xr-x 2 so so  4096 set 27 19:09 Immagini
drwxr-xr-x 2 so so  4096 set 27 19:09 Modelli
drwxr-xr-x 2 so so  4096 set 27 19:09 Musica
-rwxrwxr-x 1 so so 16688 ott  7 13:07 prova
-rw-rw-r-- 1 so so    74 ott  7 13:06 prova.c
drwxr-xr-x 2 so so  4096 set 27 19:09 Pubblici
drwxr-xr-x 2 so so  4096 set 27 19:09 Scaricati
drwxr-xr-x 2 so so  4096 set 27 19:09 Scrivania
drwxr-xr-x 5 so so  4096 set 27 19:41 snap
drwxr-xr-x 2 so so  4096 set 27 19:09 Video
```

Oltre ai 9 bit che rappresentano i permessi, viene utilizzato un ulteriore carattere (il primo) che identifica:

- ``-``: Regular file
- ``b``: Block special file
- ``c``: Character special file
- ``d``: Directory
- ``l``: Symbolic link
- ``n``: Network file
- ``p``: FIFO
- ``s``: Socket

E' possibile modificare i permessi di un file/directory attraverso il comando ``chmod``. E.g.:

Rimuovere il permesso di esecuzione ad un file di nome ``prova``:

```shell
$ chmod -x prova
```

Aggiungere il permesso di esecuzione ad un file di nome ``prova``:

```shell
$ chmod +x prova
```

## Copia, rinomina, e rimozione file

- Copia il file specificato come primo parametro nel file specificato come secondo parametro

```shell
$ cp file_sorgente file_destinazione
```

- Rinomina il file specificato come primo parametro nel file specificato come secondo parametro

```shell
$ mv file_sorgente file_destinazione
```

- Sposta il file specificato come primo parametro nella directory specificata come secondo parametro

```shell
$ mv file_sorgente directory_dest/
```

- Rimuovi il file specificato come primo parametro

```shell
$ rm file_target
```

- Rimuovi la directory specificata come primo parametro

```shell
$ rm -r directory_target
```


## Compilazione ed esecuzione di programmi

Supponiamo di aver creato un file ``prova.c`` con il seguente snippet di codice:


```c
#include <stdio.h>

int main(){


	printf("HELLO WORLD!\n");
	return 0;
}
```

Per compilare il file sorgente e ottenere un file eseguibile (che chiamiamo ``prova``):

```shell
$ gcc -o prova prova.c 
```

Per poter lanciare l'eseguibile possiamo utilizzare un percorso relativo o assoluto.

Utilizzando il percorso assoluto:

```shell
$ /home/so/prova 
HELLO WORLD!
```

Utilizzando il percorso relativo:

```shell
$ pwd
/home/so
$ ./prova 
HELLO WORLD!
```

# Comandi avanzati

## Il comando ``echo`` e ``cat``

Il comando ``echo`` mostra la stringa in input come primo parametro sull stdout (di default è il video). E.g.:

```shell
$ echo "HELLO WORLD!"
HELLO WORLD!
```

Il comando ``cat`` mostra il file in input come primo parametro sull stdout (di default è il video). E.g.:

```shell
$ cat prova.c
#include <stdio.h>

int main(){


	printf("HELLO WORLD!\n");
	return 0;
}
```


## Redirezione su file: gli operatori ``>`` e ``>>``

echo "messaggio"
echo "messaggio" > nomefile
echo "altromessaggio" >> nomefile

## L'operatore *pipe* ``|``

cat nomefile
cat nomefile | sort
cat nomefile | sort | wc -l

## Comandi di utilità per i processi

ps aux
top
