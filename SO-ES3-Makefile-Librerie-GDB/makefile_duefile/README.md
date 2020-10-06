# Esercizio 1. Makefile 

In questo esempio si vuole mostrare come è possibile scrivere un Makefile ed utilizzare il comando ``make``.

Il comando ``make`` è un utility usata specialmente per semplificare la compilazione separata di programmi composti da più file sorgente e librerie.
Digitando ``make`` il comando cerca un file di nome ``Makefile`` nella directory corrente, lo interpreta ed esegue le regole ivi contenute.

Alternativamente con ``make –f MakefileNAME``, il comando interpreta il makefile di nome ``MakefileNAME``. 

Una **regola** di un makefile segue la seguente sintassi:

```
	target: dipendenze
	[tab]	comando di sistema
```

Dato un particolare target, make esegue i comandi presenti alla linea successiva, se le dipendenze sono tutte soddisfatte.
Le dipendenze sono file da cui il target dipende. ``N.B.: il carattere tab è necessario, altrimenti otterremo un errore di interpretazione.``
