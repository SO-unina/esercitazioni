## Lettori-Scrittori singolo buffer con starvation degli scrittori

Nel problema **lettori-scrittori** abbiamo due categorie di processi:

- **Lettori**, che leggono un messaggio su di una risorsa condivisa
- **Scrittori**, che scrivono il messaggio dalla risorsa condivisa

I vincoli del problema sono:

- i processi lettori possono accedere *contemporaneamente* alla risorsa;
- i processi scrittori hanno accesso *esclusivo* alla risorsa;
- i lettori e scrittori *si escludono mutuamente* dall'uso della risorsa.

In particolare, in questo esercizio affrontiamo lo scenario in cui abbiamo **starvation dei soli scrittori**.

### Esercizio

*Scrivere un’applicazione concorrente che implementi il problema dei Lettori/Scrittori con starvation degli scrittori.
Il programma crei dei processi che agiscano da lettori e scrittori utilizzando un unico buffer di memoria in cui sono memorizzati valori di tipo long. Il buffer di memoria è creato attraverso una shared memory e la sincronizzazione tra produttori e consumatori deve avvenire tramite l'utilizzo di semafori.*

Per risolvere tale problema, si utilizza una variable condivisa ``NUM_LETTORI`` per contare il numero di lettori che contemporaneamente accedono alla risorsa. Solo quando nessun lettore è in attesa di leggere (``NUM_LETTORI == 0``), gli scrittori potranno accedere (sempre uno alla volta) alla risorsa condivisa per poter scrivere.

Per disciplinare lettori e scrittori si utilizzano 2 semafori:

- ``MUTEXL`` per gestire l’accesso alla variabile ``NUM_LETTORI`` in mutua esclusione, da parte dei lettori. Tale semaforo è inizializzato a ``1``.

- ``SYNCH`` per garantire la mutua esclusione tra i processi lettori e scrittori e tra i soli processi scrittori. Tale semaforo è inizializzato a ``1``.

Le operazioni di lettura sono "protette" dalle procedure di ``Inizio_Lettura()`` e ``Fine_Lettura()``, mentre le operazioni di scrittura sono "protette" da ``Inizio_Scrittura()`` e ``Fine_Scrittura()``.

Un processo lettore attende solo se la risorsa è occupata da un processo scrittore. Un processo scrittore può accedere alla risorsa solo se questa è libera.

Questa particolare strategia di sincronizzazione può tuttavia può provocare condizioni di attesa indefinita (starvation) per i processi scrittori.

Analizzare il file [procedure.c](procedure.c) in cui vengono implementate le funzioni di produzione e consumazione, e il file [lett_scrit_starv_scrittori.c](lett_scrit_starv_scrittori.c) dove vengono inizializzati i semafori necessari.

Compilare ed eseguire il codice:

```console
$ make
$ ./lettore_scrittore_exe
id_shared=131084
sono il figlio scrittore. Il mio pid 5291
sono il figlio lettore. Il mio pid 5292
sono il figlio scrittore. Il mio pid 5293
sono il figlio lettore. Il mio pid 5294
sono il figlio scrittore. Il mio pid 5295
sono il figlio lettore. Il mio pid 5296
sono il figlio scrittore. Il mio pid 5297
sono il figlio lettore. Il mio pid 5298
sono il figlio scrittore. Il mio pid 5299
sono il figlio lettore. Il mio pid 5300
sono il figlio scrittore. Il mio pid 5301
sono il figlio lettore. Il mio pid 5302
Valore scritto=<826613>
Figlio n.ro 5291 e' morto con status= 0
Valore letto=<826613>, numero lettori=6
Valore letto=<826613>, numero lettori=5
Valore letto=<826613>, numero lettori=4
Valore letto=<826613>, numero lettori=4
Valore letto=<826613>, numero lettori=4
Valore letto=<826613>, numero lettori=3
 Figlio n.ro 5294 e' morto con status= 0
 Figlio n.ro 5292 e' morto con status= 0
 Figlio n.ro 5302 e' morto con status= 0
 Figlio n.ro 5300 e' morto con status= 0
 Figlio n.ro 5296 e' morto con status= 0
 Figlio n.ro 5298 e' morto con status= 0
Valore scritto=<829427>
 Figlio n.ro 5293 e' morto con status= 0
Valore scritto=<831269>
 Figlio n.ro 5301 e' morto con status= 0
Valore scritto=<832532>
 Figlio n.ro 5295 e' morto con status= 0
Valore scritto=<835373>
 Figlio n.ro 5297 e' morto con status= 0
Valore scritto=<838223>
 Figlio n.ro 5299 e' morto con status= 0
```





