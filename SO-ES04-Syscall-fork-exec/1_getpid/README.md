## Identificativo di un processo: ``getpid()`` e ``getppid()``

Ogni processo ha un unico identificatore di processo chiamato PID (Process Identifier). Il PID è un intero compreso tra 0 e ``pid_max``. Di default il ``pid_max`` è pari a ``32768``; è possibile leggere tale valore dal file di sistema ``/proc/sys/kernel/pid_max``. E.g.:

```
$ cat /proc/sys/kernel/pid_max
32768
```

Il PID di un processo viene assegnato dal kernel all’atto della sua creazione. E' possibile ottenere il PID di un processo attraverso la chiamata di sistema ``getpid()``. Inoltre, i processi in Unix sono organizzati gerarchicamente, ovvero, ogni processo ha un processo padre (eccetto il processo ``init``). Nel contesto di esecuzione del processo corrente, è possibile ottenre il PID del processo padre attraverso la chiamata di sistema ``getppid()``.

Il seguente codice stamperà a video il PID del processo corrente e il PID del suo processo padre:

```c
#include <stdio.h>
#include <unistd.h>

int main(void)
{
 	int pid, ppid;
 	pid = getpid();
 	printf("Sono il processo pid = %d\n", pid);
 
	ppid = getppid();
 	printf("Il mio processo genitore ha pid = %d\n", ppid);

 	return 0;
}
```

Provando a compilare ed eseguire tale codice (osservare i file [``Makefile``](Makefile) e [``main.c``](main.c)) otteniamo un output del genere:

```console
$ ./getpid_ex
Sono il processo pid = 19375
Il mio processo genitore ha pid = 14511
```

In Linux, sono stabiliti alcuni PID di default per specifici processi. Ad esempio:

- Processo ``scheduler``: PID = 0
- Processo ``init``: PID = 1
- Processo ``pagedaemon``: PID = 2

Per poter analizzare i PID associati ai processi attualmente sul sistema, possiamo utilizzare ancora il comando ``ps`` (vedi [lezione sui comandi shell](../../SO-ES01-Introduzione-Linux/2_comandi_shell#comandi-di-utilità-per-i-processi-ps-e-top))

Oltre al comando ``ps``, è possibile analizzare la directory ``/proc`` che, per ogni processo nel sistema, contiene una directory denominata proprio con il PID del processo, e.g.:

```console 
$ ls /proc/
1     119   1397  199   2257  259  388  751  92           kpagecgroup
10    12    14    2     2258  260  391  76   93           kpagecount
100   120   1414  20    226   261  398  766  94           kpageflags
101   1203  1433  200   2261  262  4    77   95           loadavg
102   1207  15    201   227   263  450  78   950          locks
103   121   150   202   228   264  5    788  952          mdstat
104   122   1539  203   229   265  560  789  96           meminfo
105   1225  16    204   23    266  572  79   961          misc
106   123   1647  205   230   267  575  793  968          modules
1062  124   17    206   231   268  6    8    97           mounts
107   1245  18    207   232   269  611  801  98           mtrr
108   125   189   208   233   270  612  808  99           net
1082  1251  1894  209   234   271  613  809  993          pagetypeinfo
1089  1275  19    21    235   272  615  81   acpi         partitions
109   1278  190   210   236   273  618  815  buddyinfo    pressure
1095  1279  1904  211   237   274  622  82   bus          sched_debug
11    1280  192   212   238   275  623  84   cgroups      schedstat
110   1281  1921  2127  239   276  635  848  cmdline      scsi
1101  1283  1922  213   24    277  638  85   consoles     self
111   1288  1923  2137  240   278  646  850  cpuinfo      slabinfo
1116  1289  1924  214   241   279  650  852  crypto       softirqs
112   1290  1925  215   242   299  657  857  devices      stat
113   1291  1926  2156  243   3    661  86   diskstats    swaps
1136  1294  1927  216   244   300  662  863  dma          sys
114   1297  1928  217   245   339  671  866  driver       sysrq-trigger
1140  13    1929  218   246   362  675  869  execdomains  sysvipc
1141  1300  193   219   247   363  7    87   fb           thread-self
1143  1301  1930  2191  248   368  70   870  filesystems  timer_list
1145  1307  1931  2192  249   370  703  877  fs           tty
115   1308  1932  22    250   371  709  88   interrupts   uptime
1159  1309  1933  220   251   374  71   881  iomem        version
116   134   1934  2206  252   375  72   89   ioports      version_signature
1164  1354  1935  221   253   377  720  9    irq          vmallocinfo
1168  137   194   222   254   379  724  90   kallsyms     vmstat
117   1380  195   223   255   381  73   91   kcore        zoneinfo
1175  1383  196   224   256   383  734  910  keys
118   1385  197   225   257   386  74   915  key-users
1185  1387  198   2253  258   387  75   919  kmsg
```

Sotto la directory ``/proc`` è _montato_ il cosiddetto ``procfs``, un file system virtuale creato _on-the-fly_ all'avvio del sistema. La directory ``/proc`` contiene tutta una serie di informazioni utili che riguardano i processi che sono attualmente in esecuzione nel sistema. Ad esempio, il file ``cmdline`` contiene il path dell'eseguibile associato al PID di quel processo:

```
$ cat /proc/1/cmdline
/sbin/init
```
