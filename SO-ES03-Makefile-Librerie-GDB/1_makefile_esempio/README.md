# Esercizio 1. Makefile

In questo esempio si vuole mostrare come è possibile scrivere un **Makefile** ed utilizzare il comando ``make``.

Il comando ``make`` è un utility utilizzata specialmente per semplificare la compilazione separata di programmi composti da più file sorgente e librerie.
Digitando ``make`` il comando cerca un file di nome ``Makefile`` (N.B.: la stringa è case-sensitive) nella directory corrente, lo interpreta ed esegue le regole ivi contenute.

Alternativamente con ``make –f MakefileNAME``, imponiamo al comando ``make`` di interpretare un makefile di nome ``MakefileNAME``.

Una **regola** di un makefile segue la seguente sintassi:

```make
target: dipendenze
	[tab] comando di sistema
```

Dato un particolare **target**, ``make`` esegue i comandi presenti alla linea successiva, se le dipendenze sono tutte soddisfatte.
Le dipendenze sono semplicemente file da cui il target dipende. 

> **_N.B.:_** l'etichetta [tab] indica il carattere che si ottiene con il tasto TAB della tastiera (codice ASCII 9 in decimale e esadecimale). Tale carattere è necessario, altrimenti otterremo un errore di interpretazione.

Il file **Makefile** utilizzato in quest'esercitazione è il seguente:

```make
all: start

start: lib.o main.o
	g++ -o start lib.o main.o

lib.o: lib.cpp lib.h
	g++ -c lib.cpp

main.o: main.cpp lib.h
	g++ -c main.cpp

clean:
	rm -f *.o
	rm -f ./start
	rm -f *~
```

Possiamo notare che la prima regola (``all``) dipende dal file ``start``, la quale dipende a sua volta dai file ``lib.o`` e ``main.o``, e così via fino ad arrivare ad una regola risolvibile.

Per questioni di utilità, spesso viene sempre aggiunta una regola di **clean** all'interno di un Makefile. Questa regola (senza dipendenze) permette di effettuare una pulizia dei file oggetto e dei file eseguibili generati durante la compilazione. E.g.:

```make
clean:
	rm -rf *.o
   	rm -rf executable
```
> **_N.B.:_** Osservare come viene utilizzata la wildcard ``*.o`` per indicare tutti i file che terminano con l'estensione ``.o``

Inoltre, in un Makefile è possibile utilizzare variabili. Una variabile è inizializzata usando la sintassi ``NOME_VARIABILE=VALORE``. Per accedere al valore della variabile basta utilizzare la sintassi ``${NOME_VARIABILE}``.
Analizzare il file [``Makefile2``](Makefile2) per osservare come sono utilizzate le variabili per definire le varie regole.

