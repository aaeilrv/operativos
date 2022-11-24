CC = gcc
CFLAGS = -ansi -Wall -pedantic

all: buscar

buscar: main.o arrayfunc.o searchalg.o order.o records.o results.o
	$(CC) $(CFLAGS) -o buscar main.o arrayfunc.o searchalg.o order.o records.o results.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

arrayfunc.o: arrayfunc.c
	$(CC) $(CFLAGS) -c arrayfunc.c

records.o: records.c
	$(CC) $(CFLAGS) -c records.c

order.o: order.c
	$(CC) $(CFLAGS) -c order.c

searchalg.o: searchalg.c
	$(CC) $(CFLAGS) -c searchalg.c	

results.o: results.c
	$(CC) $(CFLAGS) -c results.c	

clean:
	rm *.o buscar
