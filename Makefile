CC = gcc -Wall

all: PedoFile

PedoFile: pacdrive.o socket_server.o logger.o main.o
	$(CC) pacdrive.o socket_server.o logger.o main.o -o PedoFile -lhid

main.o: main.c main.h
	$(CC) -O -c main.c

logger.o: logger.c logger.h
	$(CC) -O -c logger.c

socket_server.o: socket_server.c socket_server.h
	$(CC) -O -c socket_server.c

pacdrive.o: pacdrive.c pacdrive.h
	$(CC) -O -c pacdrive.c

clean:
	rm -f *.o *.bak *.out ex
