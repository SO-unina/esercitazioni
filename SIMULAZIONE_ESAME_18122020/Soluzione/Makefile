all: calc

calc: main.o procedure.o
	gcc -pthread -o calc main.o procedure.o

main.o:	main.c header.h
	gcc -c main.c

procedure.o: procedure.c header.h
	gcc -c procedure.c

clean:
	rm -rf calc
	rm -rf *.o
