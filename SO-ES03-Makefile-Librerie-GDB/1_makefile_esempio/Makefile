all: start

start: lib.o main.o
	g++ -o start lib.o main.o

lib.o: lib.cpp lib.h
	g++ -c lib.cpp

main.o: main_MIO.cpp lib.h
	g++ -c main.cpp

clean:
	rm -f *.o
	rm -f ./start 
	rm -f *~
