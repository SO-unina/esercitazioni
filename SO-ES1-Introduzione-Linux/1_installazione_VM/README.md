# Istruzioni per uso della macchina virtuale a supporto della parte esercitativa del corso di Sistemi Operativi

###### Docenti: Domenico Cotroneo, Marcello Cinque, Roberto Natella

**Ultimo aggiornamento: 07/10/2020**

La macchina virtuale ospita il sistema operativo **Ubuntu 20.04 LTS** (una distribuzione leggera di **Linux** ), e contiene al suo interno i principali pacchetti software utili per il corso (shell, compilatore, debugger, etc.).

La macchina è contenuta in un file con estensione **.ova** da scaricare tramite il link OneDrive:

[https://communitystudentiunina-my.sharepoint.com/:u:/g/personal/roberto\_natella\_unina\_it/EbruKk\_SvlxBipH0\_cLe-eABcuFc2skO0t6EUAErq4cFOw?e=FkDLUZ](https://communitystudentiunina-my.sharepoint.com/:u:/g/personal/roberto_natella_unina_it/EbruKk_SvlxBipH0_cLe-eABcuFc2skO0t6EUAErq4cFOw?e=FkDLUZ)

Tale file è stato creato per mezzo del programma **Oracle VirtualBox**, che deve essere installato sulla macchina su cui si intende far girare la macchina virtuale. L'applicativo VirtualBox è un gestore di macchine virtuali gratuito e facilmente installabile scaricando il programma di installazione dal sito internet della Oracle ([https://www.virtualbox.org/)](https://www.virtualbox.org/)).

La versione raccomandata di VirtualBox (su cui è stata creata la macchina virtuale) è la versione **6.2**.

Una volta installato VirtualBox è possibile **importare** la macchina virtuale, scegliendo ' **File -> Importa applicazione virtuale**' come in figura:

<p align="center">
<img src="../images/image002.png" width="300">
</p> 



Appare la seguente form dove inserire **il percorso del file .ova** con la macchina virtuale da caricare:


<div style="text-align:center">
<img src="../images/image005.png" width="300" > 
</div>


Cliccare qui per selezionare il file .ova

<div style="text-align:center">
<img src="../images/image006.png" width="300" > 
</div>


Cliccare l'icona a destra del campo di testo (il bottone evidenziato in rosso nell'immagine precedente), scegliere il file di estensione '.ova'.

<div style="text-align:center">
<img src="../images/image007.png" width="300" > 
</div>


Cliccando su **Continua** , dopo pochi minuti la macchina virtuale sarà importata in VirtualBox. La macchina virtuale apparirà a sinistra nella schermata principale di VirtualBox.


Per avviare la macchina virtuale, **cliccare sul nome della macchina virtuale** nell'elenco a sinistra, e poi sul tasto **Avvia**; in alto nella schermata. Prima di avviare la VM è possibile scegliere di personalizzare l'hardware virtuale da utilizzare cliccando sul tasto  **Impostazioni**. La raccomandazione è quella di avere almeno **2 CPU virtuali** e almeno **2Gb di memoria RAM**.

Dopo l'avvio, apparirà una nuova finestra in cui eseguirà il sistema operativo Linux. Al termine dell'avvio del sistema operativo, la macchina virtuale apparirà come segue:

<div style="text-align:center">
<img src="../images/image008.png" width="300" > 
</div>


In alternativa a VirtualBox, è possibile eseguire la macchina virtuale utilizzando il programma **VMware Workstation Player** (per Windows e Linux). Il programma è gratuitamente scaricabile da internet.

<div style="text-align:center">
<img src="../images/image009.png" width="300" > 
</div>


Per importare la macchina virtuale in VMware Workstation Player, si selezioni la voce **Importa...**.

<div style="text-align:center">
<img src="../images/image010.png" width="300" > 
</div>


Si aprirà una nuova finestra, in cui accorrerà scegliere il file **.ova** della macchina virtuale.

<div style="text-align:center">
<img src="../images/image011.png" width="300" > 
</div>


Nel caso dovesse apparire il seguente popup sulla verifica di conformità, selezionare l'opzione **Riprova** per forzare l'importazione.

<div style="text-align:center">
<img src="../images/image012.png" width="300" > 
</div>


L'importazione della macchina virtuale potrebbe richiedere svariati minuti, dipendentemente dalla potenza della macchine fisica ospitante.

<div style="text-align:center">
<img src="../images/image013.png" width="300" > 
</div>


Come per VirtualBox, al termine dell'operazione, è possibile scegliere di personalizzare l'hardware virtuale da utilizzare per la VM importata oppure proseguire con i valori di default. La raccomandazione è quella di avere almeno 2 CPU virtuali e almeno 2Gb di memoria RAM.

<div style="text-align:center">
<img src="../images/image014.png" width="300" > 
</div>


La macchina virtuale dovrà apparire correttamente nella libreria di VMware Workstation Player.


**NOTE IMPORTANTI**

Per effettuare operazioni di amministrazione (ad esempio, installazione di pacchetti, il comando sudo, etc.), si utilizzi la password ' **so**' (nome utente: ' **so**').