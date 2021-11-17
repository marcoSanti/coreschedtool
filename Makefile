CC=gcc
CFLAGS=-O3
DEBUG=-g $(CFLAGS)

./compiled/coreschedtools: ./compiled/main.o ./compiled/utils.o
	$(CC) -o ./compiled/coreschedtool ./compiled/main.o ./compiled/utils.o

./compiled/main.o: main.c main.h
	$(CC) $(CFLAGS) -o ./compiled/main.o -c main.c

./compiled/utils.o: utils.c main.h
	$(CC) $(CFLAGS) -o ./compiled/utils.o -c utils.c

clear:
	rm ./compiled/*


install: ./compiled/coreschedtools
	cp ./compiled/coreschedtool /usr/bin/coreschedtool