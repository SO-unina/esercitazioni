# Libreria dinamica

In questo esempio si vuole generare una libreria dinamica che racchiude le funzionalità di somma e prodotto definite nel file ``mat.c`` e ``mat.h``. Tale libreria viene utilizzata nel codice ``main.c``

Supponendo di chiamare la libreria statica ``mat``, per poter compilare tale libreria come dinamica è necessario eseguire il comando:

```gcc -shared -Wl,-soname,libmat.so -o libmat.so mat.o```

Notare come nel Makefile viene utilizzata la variabile d'ambiente ${PWD} per poter accedere al percorso corrente (dove si sta eseguendo il comando make).

Effettuare i seguenti passi:

- Eseguire ``make -f MakefileShLib`` per compilare
- Eseguire ``make -f MakefileShLib clean`` per pulire la compilazione
- Prima di lanciare il file eseguibile ``calc`` collegate la variabile d'ambiente ``LD_LIBRARY_PATH`` con la directory corrente, posizionarsi all'interno della directory dove è generata la libreria dinamica ed eseguire il comando:

  ``export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD``

- Osservare l'output del comando ``ldd calc`` che mostrerà le dipendenze (altre librerie dinamiche) della libreria dinamica in oggetto
- Lanciare l'eseguibile ``calc``
