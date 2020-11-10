all: prodcons_coda_circolare prodcons_pool_buffer prodcons_singolo_buffer

prodcons_coda_circolare: prodcons_coda_circolare.c 
	gcc -o prodcons_coda_circolare prodcons_coda_circolare.c

prodcons_pool_buffer: prodcons_pool_buffer.c
	gcc -o prodcons_pool_buffer prodcons_pool_buffer.c

prodcons_singolo_buffer: prodcons_singolo_buffer.c
	gcc -o prodcons_singolo_buffer prodcons_singolo_buffer.c

clean:
	rm -rf *.o
	rm -rf prodcons_coda_circolare prodcons_pool_buffer prodcons_singolo_buffer
