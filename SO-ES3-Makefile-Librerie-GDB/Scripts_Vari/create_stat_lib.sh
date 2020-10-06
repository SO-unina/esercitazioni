#!/bin/bash
#Compilare modulo sorgente
gcc -c mat.c

#Compilazione libreria statica
ar rcs libmat.a mat.o

