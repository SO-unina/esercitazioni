## Esercizio 1.

In questo esercizio, si implementa una comunicazione inter-processo utilizzando una shared memory, disciplinando l'accesso con un semaforo. In particolare, si vuole creare 2 processi figli che incrementano per 100 volte una variable intera memorizzata nella shared memory.

Nei file [semafori.h](semafori.h) e [semafori.c](semafori.c) sono definite e implementate le operazioni di *wait* e *signal* su semaforo.

Nel file [main.c](main.c) è implementato il *main* del programma richiesto.

Alcune domande:

- Cosa succederebbe se eliminassi la chiamata a ``Wait_Sem()`` o a ``Signal_Sem()`` o a entrambi?
- Cosa indica il secondo parametro della ``semget()``?
- Cosa cambia utliizzando i flag ``IPC_CREAT | IPC_EXCL`` per la ``shmget()`` e la ``semget()``?


Provare a reimplementare questo esercizio su più eseguibili (basta utilizzare come chiave IPC la macro ``IPC_PRIVATE``?).

