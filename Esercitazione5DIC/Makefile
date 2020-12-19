all: main_ex

main_ex: main.o generatore.o filtro.o checksum.o visualizzatore.o
	gcc -o main_ex main.o generatore.o filtro.o checksum.o visualizzatore.o

main.o: main.c header.h
	gcc -c main.c

generatore.o: generatore.c header.h
	gcc -c generatore.c

filtro.o: filtro.c header.h
	gcc -c filtro.c

checksum.o: checksum.c header.h
	gcc -c checksum.c

visualizzatore.o: visualizzatore.c header.h
	gcc -c visualizzatore.c

clean:
	rm -rf main_ex
	rm -rf *.o
