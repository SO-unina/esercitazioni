## Lettori-Scrittori singolo buffer con starvation di entrambi

Nel problema **lettori-scrittori** abbiamo due categorie di processi:

- **Lettori**, che leggono un messaggio su di una risorsa condivisa
- **Scrittori**, che scrivono il messaggio dalla risorsa condivisa

I vincoli del problema sono:

- i processi lettori possono accedere *contemporaneamente* alla risorsa;
- i processi scrittori hanno accesso *esclusivo* alla risorsa;
- i lettori e scrittori *si escludono mutuamente* dall'uso della risorsa.

In particolare, in questo esercizio affrontiamo lo scenario in cui abbiamo **starvation di lettori e di scrittori**.

### Esercizio

*Scrivere un’applicazione concorrente che implementi il problema dei Lettori/Scrittori con starvation di entrambi.
Il programma crei dei processi che agiscano da lettori e scrittori utilizzando un unico buffer di memoria in cui sono memorizzati valori di tipo long. Il buffer di memoria è creato attraverso una shared memory e la sincronizzazione tra produttori e consumatori deve avvenire tramite l'utilizzo di semafori.*

Per risolvere tale problema, si utilizza una variable condivisa ``NUM_LETTORI`` per contare il numero di lettori che contemporaneamente accedono alla risorsa. 
Solo quando nessun lettore è in attesa di leggere (``NUM_LETTORI == 0``), gli scrittori potranno accedere (sempre uno alla volta) alla risorsa condivisa per poter scrivere.
Rispetto alla soluzione con starvation dei soli scrittori, anche per gli scrittori si può ottenere un comportamento analogo ai lettori, introducendo una variabile ``NUM_SCRITTORI``

In questo scenario occorrono 4 semafori, tutti inizializzati a ``1``:

- ``MUTEXL`` usato per gestire l'accesso alla variabile ``NUM_LETTORI`` in mutua esclusione da parte dei lettori;

- ``MUTEXS`` per gestire l’accesso alla variabile ``NUM_SCRITTORI`` in mutua esclusione da parte degli scrittori

- ``MUTEX`` per gestire l’accesso in mutua esclusione alla risorsa condivisa da parte degli scrittori;

- ``SYNCH`` per garantire la mutua esclusione tra i processi lettori e scrittori.

Le operazioni di lettura sono sempre "protette" dalle procedure di ``Inizio_Lettura()`` e ``Fine_Lettura()``, mentre le operazioni di scrittura sono sempre "protette" da ``Inizio_Scrittura()`` e ``Fine_Scrittura()``.

Questa particolare strategia di sincronizzazione può tuttavia può provocare condizioni di attesa indefinita (starvation) per sia per i processi lettori che per i processi scrittori.

Analizzare il file [procedure.c](procedure.c) in cui vengono implementate le funzioni di produzione e consumazione, e il file [lett_scrit_starv_entrambi.c](lett_scrit_starv_entrambi.c) dove vengono inizializzati i semafori necessari.

Compilare ed eseguire il codice:

```console
$ make
$ ./lettore_scrittore_exe
sono il figlio scrittore. Il mio pid 9737
sono il figlio lettore. Il mio pid 9738
sono il figlio scrittore. Il mio pid 9739
sono il figlio lettore. Il mio pid 9740
sono il figlio scrittore. Il mio pid 9741
sono il figlio lettore. Il mio pid 9742
sono il figlio scrittore. Il mio pid 9743
sono il figlio lettore. Il mio pid 9744
sono il figlio scrittore. Il mio pid 9745
sono il figlio lettore. Il mio pid 9746
Valore scritto: <833786>
Figlio n.ro 9737 e' morto con status= 0
Valore scritto: <835493>
 Figlio n.ro 9739 e' morto con status= 0
Valore scritto: <838006>
 Figlio n.ro 9741 e' morto con status= 0
Valore scritto: <840340>
 Figlio n.ro 9743 e' morto con status= 0
Valore scritto: <842565>
 Figlio n.ro 9745 e' morto con status= 0
Valore letto=<842565>, numero lettori=5
Valore letto=<842565>, numero lettori=5
Valore letto=<842565>, numero lettori=4
Valore letto=<842565>, numero lettori=4
Valore letto=<842565>, numero lettori=5
 Figlio n.ro 9746 e' morto con status= 0
 Figlio n.ro 9744 e' morto con status= 0
 Figlio n.ro 9740 e' morto con status= 0
 Figlio n.ro 9742 e' morto con status= 0
 Figlio n.ro 9738 e' morto con status= 0
```





