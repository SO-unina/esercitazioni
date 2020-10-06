# Disassemblare un file ELF (file oggetto, librerie, etc.)

- Step 1: compilare un file c e generare un file oggetto

```gcc -c -g mat.c```

N.B.: il flag ``-g`` e' richiesto per mostrare il codice C durante il "disassemblaggio"

- Step 2: usare objdump per fare il reversing di un file ELF

Per mostrare i contenuti di tutti gli header (provate a riconoscere le sezioni (text,bss,..)

```objdump -x [nome file]``` 

Tramite il seguente comando, è possibile riconoscere all'interno della sezione ```text``` come viene tradotto il codice:

```objdump -d -S [nome file]``` 
