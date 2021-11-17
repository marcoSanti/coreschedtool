CC=gcc
CFLAGS=-O3

coreschedtool: main.o utils.o
	$(CC) -o coreschedtool main.o utils.o

main.o: main.c main.h
	$(CC) $(CFLAGS) -o main.o -c main.c

utils.o: utils.c main.h
	$(CC) $(CFLAGS) -o utils.o -c utils.c

clear:
	rm *.o
	rm coreschedtool

install: coreschedtools
	cp coreschedtool /usr/bin/coreschedtool