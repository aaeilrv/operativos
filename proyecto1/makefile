CC = gcc
CFLAGS = -ansi -Wall -pedantic

all: arbol

arbol: main.o auxstruct.o tuplearray.o linkedlist.o auxfunctions.o
	$(CC) $(CFLAGS) -o arbol main.o auxstruct.o tuplearray.o linkedlist.o auxfunctions.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

auxstruct.o: auxstruct.c
	$(CC) $(CFLAGS) -c auxstruct.c

tuplearray.o: tuplearray.c
	$(CC) $(CFLAGS) -c tuplearray.c

linkedlist.o: linkedlist.c
	$(CC) $(CFLAGS) -c linkedlist.c

auxfunctions.o: auxfunctions.c
	$(CC) $(CFLAGS) -c auxfunctions.c

clean:
	rm *.o arbol
