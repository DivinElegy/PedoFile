CC = gcc -Wall

all: logger

logger: logger.c logger.h
	$(CC) logger.c -o logger

clean:
	rm -f *.o *.bak *.out ex
