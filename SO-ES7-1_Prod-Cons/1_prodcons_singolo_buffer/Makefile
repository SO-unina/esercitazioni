all: prodcons_singolo_buffer

prodcons_singolo_buffer: procedure.o semafori.o prodcons_singolo_buffer.o
	gcc -o prodcons_singolo_buffer procedure.o semafori.o prodcons_singolo_buffer.o

prodcons_singolo_buffer.o: prodcons_singolo_buffer.c
	gcc -c prodcons_singolo_buffer.c

procedure.o: procedure.h procedure.c
	gcc -c procedure.c

semafori.o: semafori.c semafori.h
	gcc -c semafori.c



clean:
	rm -rf *.o
	rm -rf prodcons_singolo_buffer
