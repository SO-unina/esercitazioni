#!/bin/bash
#Compilare modulo sorgente
gcc -c -fpic mat.c
#Caso 1 compilazione libreria statica
gcc -shared -Wl,-soname,libmat.so -o libmat.so mat.o

