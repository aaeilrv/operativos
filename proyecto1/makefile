CC = gcc
CFLAGS = -ansi -Wall -pedantic

all: arbol

arbol: main.o auxstruct.o tuplearray.o linkedlist.o
	$(CC) $(CFLAGS) -o arbol main.o auxstruct.o tuplearray.o linkedlist.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

auxstruct.o: auxstruct.c
	$(CC) $(CFLAGS) -c auxstruct.c

tuplearray.o: tuplearray.c
	$(CC) $(CFLAGS) -c tuplearray.c

linkedlist.o: linkedlist.c
	$(CC) $(CFLAGS) -c linkedlist.c

clean:
	rm *.o arbol
