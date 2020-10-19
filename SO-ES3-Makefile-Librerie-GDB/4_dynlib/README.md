# Libreria dinamica (shared library)

In questo esempio si vuole generare una libreria dinamica che racchiuda le funzionalità di somma e prodotto definite nel file ``mat.c`` e ``mat.h``. Tale libreria viene utilizzata nel codice ``main.c``

Supponendo di chiamare la libreria statica mat, per poter compilare tale libreria come dinamica è necessario eseguire il comando:

```
gcc -shared -Wl,-soname,libmat.so -o libmat.so mat.o
```

Dove:
- ``-shared``: indica al compilatore che si vuole creare uno shared object
- ``-Wl``: passa opzioni al linker, in questo caso il nome della libreria
- ``-o``: nome da dare al file contenente la shared library

Per il nome della libreria vale una convenzione simile a quella vista per le librerie statiche: prefisso _lib_, e suffisso _.so_.
I file _obj1.o_, ..., _objN.o_ che compongono la libreria vanno compilati con l’opzione ``–fpic`` per generare codice rilocabile, ovvero indipendente dalla posizione (PIC – position independent code).

Notare come nel Makefile viene utilizzata la variabile d'ambiente ``${PWD}`` per poter accedere al percorso corrente (dove si sta eseguendo il comando ``make``).


Effettuare i seguenti passi:

- Eseguire ``make -f MakefileShLib`` per compilare la libreria

- Eseguire ``make -f MakefileShLib clean`` per rimuovere gli artefatti di compilazione (nel caso rilanciare la compilazione)

- Prima di lanciare il file eseguibile calc generato, aggiornare la variabile d'ambiente LD_LIBRARY_PATH con la directory corrente. A tal scopo, posizionarsi all'interno della directory dove è generata la libreria dinamica ed eseguire il comando:

```console
$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD
```

Osservare l'output del comando ldd calc che mostrerà le dipendenze (altre librerie dinamiche) della libreria dinamica in oggetto. E.g.:

```console
$ ldd calc
	linux-vdso.so.1 (0x00007ffdaf757000)
	libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007ff98d40a000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007ff98d019000)
	/lib64/ld-linux-x86-64.so.2 (0x00007ff98d811000)
```
> **_N.B.:_** Se non esportaste correttamente la variabile d'ambiente ``LD_LIBRARY_PATH``, otterreste il seguente output:

```console
$ ldd calc
	linux-vdso.so.1 (0x00007ffd17f8a000)
	libmat.so => not found
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f4b4c797000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f4b4cd8b000)
```

- Lanciare l'eseguibile generato ``calc``

Per evitare di dover modificare la variabile d'ambiente ``LD_LIBRARY_PATH``, è possibile utilizzare il flag ``-Wl,-rpath,$(DEFAULT_LIB_INSTALL_PATH)`` indicando al posto di ``DEFAULT_LIB_INSTALL_PATH`` il path della libreria dinamica. A questo punto, osservare come è fatto il file ``MakefileShLibDyn`` e:

- Provare a pulire gli artefatti di compilazione precedenti (``make -f MakefileShLib clean``)
- Compilare utilizzando il makefile ``MakefileShLibDyn`` (``make -f MakefileShLibDyn``)

L'esecuzione di ``calc`` dovrebbe andare a buon fine, senza modificare la variabile d'ambiente ``LD_LIBRARY_PATH``.



