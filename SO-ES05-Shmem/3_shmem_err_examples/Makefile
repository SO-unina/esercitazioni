all: shm_flags

shm_flags: shm_flags.c shm_other
	gcc -o shm_flags shm_flags.c

shm_other: shm_other.c
	gcc -o shm_other shm_other.c

clean:
	rm -rf *.o
	rm -rf shm_flags
	rm -rf shm_other
