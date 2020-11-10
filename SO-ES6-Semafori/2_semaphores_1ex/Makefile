all: semafori

semafori: semafori.o procedure.o
	gcc semafori.o procedure.o -o semafori

semafori.o: semafori.c procedure.h
	gcc -c semafori.c -o semafori.o

procedure.o: procedure.c procedure.h
	gcc -c procedure.c -o procedure.o

clean:
	rm -f *.o
	rm -f semafori
