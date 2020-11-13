all: prodcons_coda_circolare

prodcons_coda_circolare: procedure.o semafori.o prodcons_coda_circolare.o
	gcc -o prodcons_coda_circolare procedure.o semafori.o prodcons_coda_circolare.o

prodcons_coda_circolare.o: prodcons_coda_circolare.c
	gcc -c prodcons_coda_circolare.c

procedure.o: procedure.h procedure.c
	gcc -c procedure.c

semafori.o: semafori.c semafori.h
	gcc -c semafori.c



clean:
	rm -rf *.o
	rm -rf prodcons_coda_circolare
