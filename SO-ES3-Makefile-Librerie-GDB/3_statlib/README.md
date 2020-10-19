# Libreria statica

In questo esempio si vuole generare una libreria statica che racchiuda le funzionalità di somma e prodotto definite nei file ``mat.c`` e ``mat.h``.
Una libreria statica è una collezione di moduli oggetto (file ``.o``) in un unico file, con estensione ``.a``
Per creare una libreria statica si può usare il comando ``ar`` (archiver) di Unix.

La libreria analizzata in quest'esempio viene utilizzata nel codice ``main.c``.

Supponendo di chiamare la libreria statica ``mat``, per poter compilare tale libreria come statica è necessario eseguire il comando:

```
ar rcs libmat.a mat.o
```

In particolare, i flag specificano che:

- ``r``: inserisce il file con rimpiazzo
- ``c``: crea la libreria, se non esiste
- ``s``: crea un indice oggetto-file

Infine, per collegare i vari file oggetto con la libreria statica generata, bisogna utilizzare il compilatore ``gcc`` e i flag ``-L``, per indicare il path dove ricercare la libreria, e il flag ``-l`` per specificare il nome (epurato dal prefisso ``lib`` e dall'estensione ``.a``) della libreria da collegare. Ad esempio:

```
gcc -o calc main.c -L$(CURR) -lmat
```

Notare come nel Makefile viene utilizzata la variabile d'ambiente ``${PWD}`` per poter accedere al percorso corrente (dove si sta eseguendo il comando ``make``).
