CC = gcc -Wall

all: PedoFile

PedoFile: socket_server.o logger.o main.o
	$(CC) socket_server.o logger.o main.o -o PedoFile

main.o: main.c main.h
	$(CC) -O -c main.c

logger.o: logger.c logger.h
	$(CC) -O -c logger.c

socket_server.o: socket_server.c socket_server.h
	$(CC) -O -c socket_server.c

clean:
	rm -f *.o *.bak *.out ex
