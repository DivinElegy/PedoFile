CC = gcc -Wall

all: logger

logger: socket_server.o logger.o
	$(CC) socket_server.o logger.o -o logger

logger.o: logger.c logger.h
	$(CC) -O -c logger.c

socket_server.o: socket_server.c socket_server.h
	$(CC) -O -c socket_server.c

clean:
	rm -f *.o *.bak *.out ex
