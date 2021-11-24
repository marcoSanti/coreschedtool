CC=gcc
CFLAGS=-O3
DEBUG=-g

coreschedtool: main.o utils.o
	$(CC) -o coreschedtool main.o utils.o

main.o: main.c main.h
	$(CC) $(CFLAGS) -o main.o -c main.c

utils.o: utils.c main.h
	$(CC) $(CFLAGS) -o utils.o -c utils.c

clear:
	rm *.o
	rm coreschedtool

install: coreschedtool
	sudo cp coreschedtool /usr/bin/coreschedtool
	
uninstall: /usr/bin/coreschedtool
	sudo rm /usr/bin/coreschedtool

debug: main.c utils.c main.h
	$(CC) $(DEBUG) -o main.o -c main.c
	$(CC) $(DEBUG) -o utils.o -c utils.c
	$(CC) -o debug  utils.o main.o
	





