# GNU Debugger: ``gdb``

Il debugger è un programma usato per ispezionare un altro programma a tempo di esecuzione. In particolare, in Linux viene utilizzato ``gdb`` per programmi scritti in in C, C++, Fortran, e Modula-2.

Il debugger permette di:

- Eseguire step by step linee di codice
- Ispezionare parti specifiche del codice
- Analizzare variabili e registri
- Asnalizzare locazioni di memoria

Per avviare il debugger:

```console
$ gdb —args nome_file_eseguibile
```

Il file eseguibile per cui si vuole effettuare il debug con ``gdb`` deve essere compilato con l'opzione ``-g``, il quale istruisce il compilatore a generare le informazioni di debug.

### Comandi generali

- ``file``: selezione il file da debuggare
- ``run(r)``: esegue il file 
- ``attach <npid>``: permette a ``gdb`` di attaccarsi al processo con pid npid 
- ``kill``: uccide il processo per cui stiamo facendone il debug
- ``quit``: esce da ``gdb``

### Esecuzione step by step

- ``c(ontinue)``: continua l’esecuzione fino al prossimo stop
- ``s(tep)``: esegue una linea di codice, entrando nella chiamata a funzione se la linea è una call.
- ``n(ext)``: esegue una linea di codice, senza entrare nella chiamata a funzione se la linea è una call.
- ``finish``: termina l’esecuzione di una funzione
 
### Breakpoints

- ``b(reak)``: imposta un breakpoint alla linea di codice impostata come  
- ``watch <expr>``: trigger quando *expr* è letto o scritto
- ``info break``: lista di tutti i breakpoints
- ``clear <pos>``: elimina un breakpoint alla posizione pos
- ``delete <num>``: elimina un breakpoint usando il numero
 
### Comandi per ricercare e stampare

- ``list <pos>``: stampa la linea di codice nella posizione *pos*
- ``search <regexp>``: ricerca i punti del codice sorgente che soddisfano l’espressione regolare regexp
- ``backtrace``: stampa lo stacktrace fino a quel punto
- ``info <var,fun>``: stampa informazioni su variabili e funzioni
- ``print <expr>``: stampa la valutazione dell’espressione *expr*

### Comandi per modificare dati e control path

- ``set <name> <expr>``: cambia il valore di una variabile
- ``return <expr>``: forza il valore di ritorno ad *expr* dalla funzione corrente
- ``jump <pos>``: fa saltare l’esecuzione a *pos*
 
