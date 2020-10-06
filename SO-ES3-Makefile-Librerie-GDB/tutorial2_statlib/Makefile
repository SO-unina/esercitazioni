CURR=${PWD}

all: calcola

calcola: mat.a
	gcc -o calc main.c -L$(CURR) -lmat

mat.a: mat.o
	ar rcs libmat.a mat.o

mat.o: mat.h
	gcc -c mat.c

clean:
	rm -f ./calc
	rm -f libmat.a
	rm -f *.o
