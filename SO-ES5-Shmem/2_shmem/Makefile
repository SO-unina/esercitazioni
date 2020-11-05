all: start

start: main_es_1.o
	gcc -o main_es_1_ex main_es_1.o

main_es_1.o: main_es_1.c
	gcc -c main_es_1.c

clean:
	rm -rf *.o
	rm -rf main_es_1_ex
