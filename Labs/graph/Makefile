CFLAGS+=--std=c99 
CFLAGS+=-g
CFLAGS+=-O2 -Wall -Werror -pedantic
CC=clang

all: main

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c -o graph.o

main: main.c graph.o
	$(CC) $(CFLAGS) $< graph.o -o $@
	
clean:
	rm -f *.o
	rm -f main