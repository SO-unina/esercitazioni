## Esercizio. Problema Produttori/Consumatori con coda di messaggi asincrona

*Scrivere un’applicazione concorrente che implementi il problema dei Produttori/Consumatori singolo buffer utilizzando un protocollo di scambio di messaggi con invio asincrono.
Il programma crei dei processi che agiscano da produttori e consumatori, utilizzando una coda di messaggi per produrre e consumare valori di tipo char[]. La sincronizzazione tra produttori e consumatori deve avvenire tramite l'utilizzo delle primitive di msgsnd() e msgrcv()*

Analizzare il file [procedure.c](procedure.c) in cui vengono implementate le funzioni di produzione e consumazione, e il file [p_c_msg.c](p_c_msg.c) dove vengono inizializzate le chiamate di sistema necessarie.

Compilare ed eseguire il codice:

```console
$ make
$ ./start
sono il figlio consumatore. Il mio pid 52841
sono il produttore. Il mio pid 52840
MESSAGGIO INVIATO: <stringa 0>
MESSAGGIO INVIATO: <stringa 1>
MESSAGGIO INVIATO: <stringa 2>
MESSAGGIO INVIATO: <stringa 3>
MESSAGGIO INVIATO: <stringa 4>
MESSAGGIO INVIATO: <stringa 5>
MESSAGGIO INVIATO: <stringa 6>
MESSAGGIO INVIATO: <stringa 7>
MESSAGGIO INVIATO: <stringa 8>
MESSAGGIO INVIATO: <stringa 9>
Figlio n.ro 52840 e' morto con status= 0
MESSAGGIO RICEVUTO: <stringa 0>
Time Sender: Tue Nov 17 18:36:03 2020
Time Receiver: Tue Nov 17 18:36:03 2020
Time Ctime: Tue Nov 17 18:36:03 2020
Messages Number: 9
MESSAGGIO RICEVUTO: <stringa 1>
Time Sender: Tue Nov 17 18:36:03 2020
Time Receiver: Tue Nov 17 18:36:03 2020
Time Ctime: Tue Nov 17 18:36:03 2020
Messages Number: 8
...
MESSAGGIO RICEVUTO: <stringa 9>
Time Sender: Tue Nov 17 18:36:03 2020
Time Receiver: Tue Nov 17 18:36:03 2020
Time Ctime: Tue Nov 17 18:36:03 2020
Messages Number: 0
Figlio n.ro 52841 e' morto con status= 0
```





