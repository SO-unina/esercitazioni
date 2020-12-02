## Esercizio. Coda di messaggi con applicativi multipli

*Scrivere un’applicazione concorrente che sincronizzi tramite coda di messaggi UNIX tre tipologie di processi P1, P2, P3. I processi P1 e P2 inviano sulla coda un messaggio del tipo ``(PROCESS_ID, FLOAT_VALUE)``, dove il ``PROCESS_ID`` è la stringa ``"P1"`` o ``"P2"`` (a seconda del processo), mentre FLOAT_VALUE è un valore float generato casualmente nell'intervallo ``[i_dx,i_sx]``.
Il processo P3 dovrà ricevere 22 messaggi, 11 da parte del processo P1 e 11 dal processo P2, e calcolare la media cumulativa delle 2 serie. Al termine dei 22 messaggi ricevuti, il processo P3 stampa a video le medie calcolate. 

Compilare ed eseguire il codice:

```console
$ make
$ ./start
sono il produttore. Il mio pid 53623
sono il figlio consumatore. Il mio pid 53624
MESSAGGIO INVIATO: <www.unina.it>
MESSAGGIO RICEVUTO: <www.unina.it>
Figlio n.ro 53624 e' morto con status= 0
Figlio n.ro 53623 e' morto con status= 0
```





