# Disassemblare un file ELF (file oggetto, librerie, etc.)

1. Compilare un file ``c`` e generare un file oggetto. E.g.:

```gcc -c -g mat.c```

Verrà generato automaticamente un file oggetto ``mat.o``

> **_N.B.:_** il flag ``-g`` e' richiesto per mostrare il codice C durante il "disassemblaggio"

2. Utilizzare il comando ``objdump`` per fare il reverse di un file ELF.

Per mostrare i contenuti di tutti gli header (provate a riconoscere le sezioni (text,bss,..) utilizzare il comando

```objdump -x [nome file]```

Nel caso particolare, proviamo a fare il dump del file oggetto ``mat.o`` generato precedentemente:

```console
$ objdump -x mat.o

mat.o:     formato del file elf64-x86-64
mat.o
architettura: i386:x86-64, flag 0x00000011:
HAS_RELOC, HAS_SYMS
indirizzo di partenza 0x0000000000000000

Sezioni:
Idx Name          Size      VMA               LMA               File off  Algn
  0 .text         00000098  0000000000000000  0000000000000000  00000040  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .data         00000000  0000000000000000  0000000000000000  000000d8  2**0
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          00000000  0000000000000000  0000000000000000  000000d8  2**0

...

SYMBOL TABLE:
0000000000000000 l    df *ABS*	0000000000000000 mat.c
0000000000000000 l    d  .text	0000000000000000 .text
0000000000000000 l    d  .data	0000000000000000 .data
0000000000000000 l    d  .bss	0000000000000000 .bss
0000000000000000 l    d  .debug_info	0000000000000000 .debug_info
0000000000000000 l    d  .debug_abbrev	0000000000000000 .debug_abbrev
0000000000000000 l    d  .debug_aranges	0000000000000000 .debug_aranges
0000000000000000 l    d  .debug_line	0000000000000000 .debug_line
0000000000000000 l    d  .debug_str	0000000000000000 .debug_str
0000000000000000 l    d  .note.GNU-stack	0000000000000000 .note.GNU-stack
0000000000000000 l    d  .note.gnu.property	0000000000000000 .note.gnu.property
0000000000000000 l    d  .eh_frame	0000000000000000 .eh_frame
0000000000000000 l    d  .comment	0000000000000000 .comment
0000000000000000 g     F .text	0000000000000049 somma
0000000000000049 g     F .text	000000000000004f prod
...

```

Dallo snippet precedente è possibile osservare le varie sezioni (text, area dati globale, etc.) e la tabella dei simboli (tra cui le funzioni di ``somma`` e ``prodotto`` implementate).

Tramite il comando ``objdump -d -S [nome file]``, è possibile ottenere il disassemblato dell'area testo di un file sorgente. Nel nostro esempio:

```console
$ objdump -d -S mat.o 

mat.o:     formato del file elf64-x86-64

Disassemblamento della sezione .text:

0000000000000000 <somma>:
#include <stdio.h>
#include <stdlib.h>
#include "mat.h"

int somma(int* s,int d){
   0:	f3 0f 1e fa          	endbr64 
   4:	55                   	push   %rbp
   5:	48 89 e5             	mov    %rsp,%rbp
   8:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
   c:	89 75 e4             	mov    %esi,-0x1c(%rbp)
	int temp = 0;
   f:	c7 45 f8 00 00 00 00 	movl   $0x0,-0x8(%rbp)
	int i;
	for(i=0; i < d; i++){
  16:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  1d:	eb 1d                	jmp    3c <somma+0x3c>
```


