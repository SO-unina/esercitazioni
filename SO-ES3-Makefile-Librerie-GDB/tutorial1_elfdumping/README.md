# Disassemblare un file ELF

In questo esempio si vuole mostrare come effettuare il dump di un file oggetto. 

- Compilare un file c e generare un file oggetto

```gcc -c -g mat.c```

N.B.: il flag ``-g`` e' richiesto per attivare la compilazione dei simboli di debug e mostrare il codice C durante il "disassemblaggio"

- Utilizzare il comando ``objdump`` per fare il reverse di un file ELF

Per mostrare i contenuti di tutti gli header (provate a riconoscere le sezioni (text,bss,..) eseguire il comando:

```objdump -x [nome file]``` 

Tramite il seguente comando, è possibile riconoscere all'interno della sezione ```text``` come viene tradotto il codice:

```objdump -d -S [nome file]``` 
