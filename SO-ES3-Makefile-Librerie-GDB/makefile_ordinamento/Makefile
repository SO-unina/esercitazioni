all: provaOrd

provaOrd: alg_ord.o vettore.o provaOrd.o
	g++ -o provaOrd alg_ord.o vettore.o provaOrd.o

alg_ord.o: alg_ord.cpp alg_ord.h
	g++ -c alg_ord.cpp

vettore.o: vettore.cpp vettore.h
	g++ -c vettore.cpp


provaOrd.o: provaOrd.cpp vettore.h alg_ord.h
	g++ -c provaOrd.cpp

clean:
	rm -f *.o
	rm -f ./provaOrd 
	rm -f *~
