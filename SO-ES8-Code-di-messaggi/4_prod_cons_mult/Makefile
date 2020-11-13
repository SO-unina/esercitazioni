
all: start p1 p2 p3

start: start.c
	gcc start.c -o start

p1: p1.c header.h procedure.o
	gcc p1.c -o p1 procedure.o

p2: p2.c header.h procedure.o
	gcc p2.c -o p2 procedure.o

p3: p3.c header.h procedure.o
	gcc p3.c -o p3 procedure.o

procedure.o: header.h
	gcc -c procedure.c

clean:
	rm -f *.o
	rm -f p1 p2 p3 start
