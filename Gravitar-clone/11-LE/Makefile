all: main

main.o: main.c lista.h
	gcc -Wall -pedantic -std=c99 main.c -c

lista.o: lista.c lista.h
	gcc -Wall -pedantic -std=c99 lista.c -c

main: lista.o main.o
	gcc lista.o main.o -o main
