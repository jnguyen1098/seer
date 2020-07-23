CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra -Wpedantic -ggdb3
VFLAGS = --show-leak-kinds=all --track-origins=yes --leak-check=full

run: bin/gryphsig
	./bin/gryphsig

bin/gryphsig: obj/gryphsig.o
	$(CC) $(CFLAGS) obj/gryphsig.o -o bin/gryphsig

obj/gryphsig.o: src/gryphsig.c
	$(CC) $(CFLAGS) src/gryphsig.c -c -o obj/gryphsig.o

clean:
	rm -rf bin/*
	rm -rf obj/*
