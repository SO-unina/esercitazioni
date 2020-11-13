all: prodcons_vettore_stato

prodcons_vettore_stato: procedure.o semafori.o prodcons_vettore_stato.o
	gcc -o prodcons_vettore_stato procedure.o semafori.o prodcons_vettore_stato.o

prodcons_vettore_stato.o: prodcons_vettore_stato.c
	gcc -c prodcons_vettore_stato.c

procedure.o: procedure.h procedure.c
	gcc -c procedure.c

semafori.o: semafori.c semafori.h
	gcc -c semafori.c



clean:
	rm -rf *.o
	rm -rf prodcons_vettore_stato
