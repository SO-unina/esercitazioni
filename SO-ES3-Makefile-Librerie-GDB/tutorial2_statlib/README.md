# Libreria statica

In questo esempio si vuole generare una libreria statica che racchiude le funzionalità di somma e prodotto definite nel file ``mat.c`` e ``mat.h.
Tale libreria viene utilizzata nel codice ``main.c``

Supponendo di chiamare la libreria statica ``calc``, per poter compilare tale libreria come statica è necessario eseguire il comando:

```ar rcs libmat.a mat.o```

Notare come nel Makefile viene utilizzata la variabile d'ambiente ``${PWD}`` per poter accedere al percorso corrente (dove si sta eseguendo il comando ``make``).
