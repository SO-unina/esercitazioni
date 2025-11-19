all: start

start: lib.o main.o
	gcc -o start lib.o main.o

lib.o: lib.c lib.h
	gcc -c lib.c

main.o: main.c lib.h
	gcc -c main.c

clean:
	rm -f *.o
	rm -f ./start 
	rm -f *~
