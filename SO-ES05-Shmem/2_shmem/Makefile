all: start

start: main_es_int.o main_es_str.o
	gcc -o main_es_int_ex main_es_int.o
	gcc -o main_es_str_ex main_es_str.o

main_es_int.o: main_es_int.c
	gcc -c main_es_int.c

main_es_str.o: main_es_str.c
	gcc -c main_es_str.c

clean:
	rm -rf *.o
	rm -rf main_es_int_ex
	rm -rf main_es_str_ex
