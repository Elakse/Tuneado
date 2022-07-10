
CFLAGS=-Wall -std=c99 -pedantic
LFLAGS=-Wall
DEBUG=-g


all: Gravitar


Gravitar: main.o bala.o caracteres.o color.o combustible.o escritura.o figuras.o fisica.o lista.o nave.o nivel.o planeta.o polilinea.o reactor.o torreta.o
	gcc $(LFLAGS) -o Gravitar main.o bala.o caracteres.o color.o combustible.o escritura.o figuras.o fisica.o lista.o nave.o nivel.o planeta.o polilinea.o reactor.o torreta.o -lm -lSDL2

main.o: main.c config.h nave.h bala.h figuras.h fisica.h lista.h nivel.h escritura.h
	gcc $(CFLAGS) $(DEBUG) -c main.c

bala.o: bala.c bala.h fisica.h
	gcc $(CFLAGS) $(DEBUG) -c bala.c

caracteres.o: caracteres.c caracteres.h
	gcc $(CFLAGS) $(DEBUG) -c caracteres.c

color.o: color.c color.h
	gcc $(CFLAGS) $(DEBUG) -c color.c

combustible.o: combustible.c combustible.h
	gcc $(CFLAGS) $(DEBUG) -c combustible.c

escritura.o: escritura.c escritura.h polilinea.h
	gcc $(CFLAGS) $(DEBUG) -c escritura.c

figuras.o: figuras.c figuras.h config.h polilinea.h
	gcc $(CFLAGS) $(DEBUG) -c figuras.c

fisica.o: fisica.c fisica.h
	gcc $(CFLAGS) $(DEBUG) -c fisica.c

lista.o: lista.c lista.h
	gcc $(CFLAGS) $(DEBUG) -c lista.c

nave.o: nave.c nave.h config.h fisica.h
	gcc $(CFLAGS) $(DEBUG) -c nave.c

nivel.o: nivel.c nave.h nivel.h lista.h torreta.h combustible.h reactor.h bala.h config.h fisica.h planeta.h
	gcc $(CFLAGS) $(DEBUG) -c nivel.c

planeta.o: planeta.c fisica.h planeta.h
	gcc $(CFLAGS) $(DEBUG) -c planeta.c

polilinea.o: polilinea.c polilinea.h color.h config.h
	gcc $(CFLAGS) $(DEBUG) -c polilinea.c

reactor.o: reactor.c reactor.h
	gcc $(CFLAGS) $(DEBUG) -c reactor.c

torreta.o: torreta.c torreta.h config.h fisica.h
	gcc $(CFLAGS) $(DEBUG) -c torreta.c

clean:
	rm *.o
