## Utilzzo base di ``git``

> :warning: Il supporto all'autenticazione tramite password è stato rimosso il 13 Agosto 2021. E' necessario dunque creare un **Personal Access Token**. Per la creazione, consultare la guida al seguente [link](https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/creating-a-personal-access-token).


``git`` è un sistema di controllo delle versioni (versioning system), e mantiene l'intera storia (in termini di modifiche) di una directory.
La directory in ``git`` è chiamata **repository**.
Per creare un primo repository basta registrarsi a [https://github.com/](https://github.com/) e creare un nuovo account. Il repository che verrà creata è remota, ovvero risiede sul server github. 

Per utilizzare il repository delle esercitazioni del corso di Sistemi Operativi, è possibile clonare tale repository nel proprio repository personale. Assumendo nome utente ``username`` e ``my_repo`` il nome del proprio repository personale, possiamo:

```console
$ git clone https://username@github.com/SO-unina/esercitazioni
```
In questo modo avrete creato una copia del repository che è possibile utilizzare. Per poter ricevere tutti gli aggiornamenti dal repository remoto basta eseguire il comando ``git pull``.

Se si vuole creare un duplicato del repository remoto e utilizzare un proprio repository privato, è necessario effettuare il cosiddetto _mirroring_. Eseguire le istruzioni come di seguito:

```
# git clone --bare https://username@github.com/SO-unina/esercitazioni
# cd esercitazioni.git
# git push --mirror https://username@github.com/my_repo
# cd ..
# rm -rf esercitazioni.git
```
Successivamente, il workflow è quello di aggiungere dei cambiamenti (dei contenuti) al proprio repository, aggiungere i cambiamenti al *commit* corrente, effettuare il commit, ed effettuare il *push* di questi cambiamenti verso il proprio repository remoto. 

```
# git add CHANGED_FILE
# git commit -m "change file"
# git push
```

Ovviamente, quando si effettuerà il pull dal repository delle esercitazioni potrebbero esserci dei conflitti da gestire.

Il comando ``git status`` è importante per conoscere lo stato attuale del repository locale rispetto a quello remoto. Ad esempio, è possibile sapere se c'è qualche cambiamento da aggiornare sul repository remoto oppure no.

Nel caso in cui non ci fosse nulla da aggiornare, il messaggio in output sarà similmente a:

```console
$ git status
Sul branch master
Your branch is up-to-date with ’origin/master’.
nothing to commit, working directory clean
```

Viceversa, se ci fosse qualche file da aggiornare (push) sul repository remoto, il messaggio in output sarà similmente a:

```console
$ git status
Sul branch master
Your branch is up to date with 'origin/main'.

Untracked files:
  (use "git add <file>..." to include in what will be committed)

	<file1>
	<file2>

nothing added to commit but untracked files present (use "git add" to track)
```
