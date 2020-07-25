CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra -Wpedantic -ggdb3 -Iinclude -D_CATCH_CRASHES
VFLAGS = --show-leak-kinds=all --track-origins=yes --leak-check=full

run: bin/gryphsig
	./bin/gryphsig

valgrind: bin/gryphsig
	valgrind $(VFLAGS) ./bin/gryphsig


internal_test: bin/internal_test
	./bin/internal_test


bin/gryphsig: obj/gryphsig.o obj/linkedlist.o obj/main.o
	$(CC) $(CFLAGS) obj/gryphsig.o obj/linkedlist.o obj/main.o -o bin/gryphsig

bin/internal_test: obj/internal_test.o obj/gryphsig.o
	$(CC) $(CFLAGS) obj/internal_test.o obj/gryphsig.o -o bin/internal_test


obj/gryphsig.o: src/gryphsig.c
	$(CC) $(CFLAGS) src/gryphsig.c -c -o obj/gryphsig.o

obj/internal_test.o: test/internal_test.c
	$(CC) $(CFLAGS) test/internal_test.c -c -o obj/internal_test.o

obj/linkedlist.o: project/linkedlist.c
	$(CC) $(CFLAGS) -Iproject project/linkedlist.c -c -o obj/linkedlist.o

obj/main.o: src/main.c
	$(CC) $(CFLAGS) src/main.c -c -o obj/main.o


clean:
	rm -rf bin/*
	rm -rf obj/*
