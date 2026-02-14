CC=gcc
CFLAGS=-Iinclude -Wall
LIBS=-lssl -lcrypto -lz

SRC=$(wildcard src/*.c)

all:
	$(CC) $(SRC) $(CFLAGS) $(LIBS) -o mygit

clean:
	rm -f mygit
