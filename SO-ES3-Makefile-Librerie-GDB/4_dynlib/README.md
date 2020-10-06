# Libreria dinamica

In questo esempio si vuole generare una libreria dinamica che racchiuda le funzionalità di somma e prodotto definite nel file ``mat.c`` e ``mat.h``. Tale libreria viene utilizzata nel codice ``main.c``

Supponendo di chiamare la libreria statica mat, per poter compilare tale libreria come dinamica è necessario eseguire il comando:

```
gcc -shared -Wl,-soname,libmat.so -o libmat.so mat.o
```

Notare come nel Makefile viene utilizzata la variabile d'ambiente ``${PWD}`` per poter accedere al percorso corrente (dove si sta eseguendo il comando ``make``).

Effettuare i seguenti passi:

- Eseguire ``make -f MakefileShLib`` per compilare la libreria

- Eseguire ``make -f MakefileShLib clean`` per rimuovere gli artefatti di compilazione (nel caso rilanciare la compilazione)

- Prima di lanciare il file eseguibile calc generato, aggiornare la variabile d'ambiente LD_LIBRARY_PATH con la directory corrente. A tal scopo, posizionarsi all'interno della directory dove è generata la libreria dinamica ed eseguire il comando:

  ``export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD``

  Osservare l'output del comando ldd calc che mostrerà le dipendenze (altre librerie dinamiche) della libreria dinamica in oggetto. E.g.:
```
# ldd calc
	linux-vdso.so.1 (0x00007ffdaf757000)
	libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007ff98d40a000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007ff98d019000)
	/lib64/ld-linux-x86-64.so.2 (0x00007ff98d811000)
```
- Lanciare l'eseguibile calc
