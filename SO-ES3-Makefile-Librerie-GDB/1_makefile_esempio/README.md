# Esercizio 1. Makefile

In questo esempio si vuole mostrare come è possibile scrivere un Makefile ed utilizzare il comando ``make``.

Il comando ``make`` è un utility usata specialmente per semplificare la compilazione separata di programmi composti da più file sorgente e librerie.
Digitando ``make`` il comando cerca un file di nome ``Makefile`` nella directory corrente, lo interpreta ed esegue le regole ivi contenute.

Alternativamente con ``make –f MakefileNAME``, il comando interpreta il makefile di nome ``MakefileNAME``.

Una **regola** di un makefile segue la seguente sintassi:

```
        target: dipendenze
        [tab]   comando di sistema
```

Dato un particolare target, make esegue i comandi presenti alla linea successiva, se le dipendenze sono tutte soddisfatte.
Le dipendenze sono file da cui il target dipende. ``N.B.: l'etichetta [tab] indica il carattere che si ottiene con il tasto TAB della tastiera. Tale carattere è necessario, altrimenti otterremo un errore di interpretazione.``

Per questioni di utilità, spesso viene sempre aggiunta la regola di clean all'interno di un Makefile. Questa regola (senza dipendenze) permette di
effettuare una pulizia dei file oggetto e i file eseguibili generate durante la compilazione. E.g.:

```
        clean:
                rm -rf *.o
                rm -rf executable
```
N.B.: Osservare come viene utilizzata la wildcard ``*.o`` per indicare tutti i file che terminano con l'estensione ``.o``
