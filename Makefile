CC=gcc
CFLAGS=-Iinclude -Wall
LIBS=-lssl -lcrypto -lz

SRC=$(wildcard src/*.c)

all:
	$(CC) $(SRC) $(CFLAGS) $(LIBS) -o ccgit

clean:
	rm -f ccgit
