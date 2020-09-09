CC = gcc

hamming: hamming.o
	$(CC) hamming.o -o hamming -lwiringPi

hamming.o: hamming.c
	$(CC) -c  hamming.c

clean:
	rm hamming.o
