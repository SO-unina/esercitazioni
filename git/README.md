## Utilzzo base di ``git``

``git`` è un sistema di controllo delle versioni (versioning system), e mantiene l'intera storia (in termini di modifiche) di una directory.
La directory in ``git`` è chiamata **repository**.
Per creare un primo repository basta registrarsi a [https://github.com/](https://github.com/) e creare un nuovo account. Il repository che verrà creata è remota, ovvero risiede sul server github. 

Per poter utilizzare tale repository localmente (sul proprio PC) bisogna utilizzare il comando ``git clone``. 
Successivamente, il workflow è quello di aggiungere dei cambiamenti (dei contenuti) a tale repository, aggiungere i cambiamenti al *commit* corrente, effettuare il commit, ed effettuare il *push* di questi cambiamenti verso il repository remoto. 

Per utilizzare il repository delle esercitazioni del corso di Sistemi Operativi, è possibile clonare tale repository nel proprio repository personale. Assumendo nome utente ``username`` e ``my_repo`` il nome del proprio repository personale, possiamo:

```console
$ git clone https://github.com/username/my_repo
$ cd my_repo
$ git clone https://github.com/SO-unina/esercitazioni
$ # Aggiungere (eventualmente) dei file
$ git add <file>
$ git commit -m "Commit dei file"
$ git push origin master
```

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
