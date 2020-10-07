## Utilzzo base di ``git``

``git`` è un sistema di controllo delle versioni (versioning system), e mantiene l'intera storia (in termini di modifiche) di una directory.
La directory in ``git`` è chiamata **repository**.
Per creare (automaticamente) una prima repository basta registrarsi a [https://github.com/](https://github.com/) e creare un account. La repository che verrà create è remota (cioè risiede sul server github). 

Per portare tale repository localmente sul proprio PC bisogna utilizzare il comando ``git clone``. 
Successivamente, il workflow è quello di aggiungere dei cambiamenti (dei contenuti) a tale repository, aggiungere i cambiamenti al *commit* corrente, effettuare il commit, ed effettuare il *push* di questi cambiamenti verso la repository remota. 

Quindi, per utilizzare la repository delle esercitazioni del corso di Sistemi Operativi, i comandi base sono i seguenti:

```console
$ git clone https://github.com/SO-unina/esercitazioni$ # Aggiungere (eventualmente) dei file$ git add <file>
$ git commit -m "Commit dei file"
$ git push origin master
```

Il comando ``git status`` è importante per conoscere lo stato attuale del repository locale rispetto a quello remoto. Ad esempio, è possibile sapere se c'è qualche cambiamento da aggiornare sulla repository remota oppure no.

Nel caso in cui non ci fosse nulla da aggiornare, il messaggio in output sarà similmente a:

```console
$ git status
Sul branch masterYour branch is up-to-date with ’origin/master’.
nothing to commit, working directory clean```Viceversa, se ci fosse qualche file da aggiornare (push) sulla repository remota, il messaggio in output sarà similmente a:

```console$ git status
Sul branch master
Your branch is up to date with 'origin/main'.

Untracked files:
  (use "git add <file>..." to include in what will be committed)

	<file1>
	<file2>

nothing added to commit but untracked files present (use "git add" to track)
```