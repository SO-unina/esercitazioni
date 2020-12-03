CC=gcc
LFLAGS=-pthread

# Nota: versioni precedenti di PThreads utilizzavano
# un flag differente ("-lpthread").
#LFLAGS=-lpthread

all: helloMT

helloMT: helloMT.c
	$(CC) $(LFLAGS) -o helloMT helloMT.c

clean:
	rm -f helloMT

