all: main analizzatore elaboratore generatore

main: main.o
	gcc -o main_exe main.o

main.o: main.c header.h
	gcc -c main.c

analizzatore: analizzatore.o procedure.o semafori.o
	gcc -o analizzatore analizzatore.o procedure.o semafori.o

elaboratore: elaboratore.o procedure.o semafori.o
	gcc -o elaboratore elaboratore.o procedure.o semafori.o

generatore: generatore.o procedure.o semafori.o
	gcc -o generatore generatore.o procedure.o semafori.o

procedure.o: procedure.c header.h
	gcc -c procedure.c

semafori.o: semafori.c semafori.h
	gcc -c semafori.c

clean:
	rm -f *.o 
	rm -f main_exe
	rm -f analizzatore
	rm -f elaboratore
	rm -f generatore

