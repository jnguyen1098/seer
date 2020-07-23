CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra -Wpedantic -ggdb3 -Iinclude -D_CATCH_CRASHES
VFLAGS = --show-leak-kinds=all --track-origins=yes --leak-check=full

run: bin/gryphsig
	./bin/gryphsig

test: bin/internaltest
	./bin/internaltest

valgrind: bin/gryphsig
	valgrind $(VFLAGS) ./bin/gryphsig

bin/gryphsig: obj/gryphsig.o
	$(CC) $(CFLAGS) obj/gryphsig.o -o bin/gryphsig

bin/internaltest: obj/internaltest.o obj/gryphsig.o
	$(CC) $(CFLAGS) obj/internaltest.o obj/gryphsig.o -o bin/internaltest

obj/gryphsig.o: src/gryphsig.c
	$(CC) $(CFLAGS) src/gryphsig.c -c -o obj/gryphsig.o

obj/internaltest.o: test/internal_test.c
	$(CC) $(CFLAGS) test/internal_test.c -c -o obj/internaltest.o

clean:
	rm -rf bin/*
	rm -rf obj/*
