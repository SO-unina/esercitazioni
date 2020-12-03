### Lettori/scrittori con semafori, su una coppia di valori condivisa

Si realizzi in linguaggio C un'applicazione **multiprocesso** in cui
un processo scrittore e due processi lettori scambiano dati attraverso
un buffer condiviso, da allocare in una **shared memory UNIX**. Il
buffer dovrà contenere una coppia di variabili intere (`val_1` e
`val_2`), entrambe con valori tra 0 e 9. Lo scrittore dovrà scegliere
casualmente una coppia di valori e scriverla sulle due variabili
all'atto di una scrittura. I due lettori dovranno leggere,
rispettivamente, la prima e la seconda variabile. Si sincronizzi l'accesso utilizzando
**semafori UNIX** considerando i vincoli del problema lettori-scrittori. Si simuli la scrittura con una attesa di 1 secondo, e
la lettura con una attesa di 2 secondi, effettuando in entrambi i casi
una stampa a video. In totale, lo scrittore dovrà effettuare 5
scritture, e i lettori 5 letture.

Il programma deve essere sviluppato in tre eseguibili distinti (utilizzare la ``exec()``), di cui:

1. il primo eseguibile è eseguito da un processo padre che crea tre processi figli, ciascuno dei quali eseguirà uno degli altri eseguibili;
2. un eseguibile per il codice dei lettori;
3. un eseguibile per il codice dello scrittore.

![image](../../images/lettori-scrittori_con_semafori_su_una_coppia_di_valori_condivisa.png)

Provare ad implementare lo stesso esercizio considerando più scrittori e adottando le diverse strategie per la starvation.
