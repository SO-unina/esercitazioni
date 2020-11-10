## Esercizio 2.

Si realizzi in linguaggio C/C++ un'applicazione **multiprocesso** che svolga, in parallelo su più processi, la **ricerca del valore minimo** all'interno di un vettore di grandi dimensioni. Il processo padre dovrà allocare un vettore di 10.000 valori interi, da memorizzare in una **memoria condivisa UNIX**, e da inizializzare con valori non negativi scelti casualmente. Dopodiché, il processo padre dovrà creare un gruppo di 10 processi figli, e scambiare con loro il vettore di interi.

Ciascuno dei processi figli dovrà lavorare su una **porzione distinta del vettore** creato dal padre. Ad esempio, il primo figlio dovrà lavorare sui primi 1000 elementi; il secondo figlio sui secondi 1000 elementi; etc. Ogni figlio dovrà cercare il valore minimo all'interno dalla porzione di vettore assegnatagli.

Il processo padre e i figli dovranno inoltre condividere in **mutua esclusione** un buffer, atto a contenere un singolo valore intero, utilizzando una **area di memoria condivisa e semafori UNIX**. Al termine della ricerca, il processo figlio dovrà consultare il valore attualmente presente nel buffer condiviso. Se il valore che ha trovato è minore di quello del buffer, il processo figlio dovrà sovrascrivere il buffer con il valore che ha trovato. Al termine di tutti i processi figli, il padre potrà prelevare il valore minimo assoluto dal buffer condiviso.

<p align="center">
<img src="../images/calcolo_parallelo_su_un_vettore_condiviso.png" width="600">
</p>


I file da modificare e completare con il codice mancante sono i seguenti:

- [main.c](main.c)

- [processi-mutua-esclusione.c](processi-mutua-esclusione.c)