# Copyright 2019 Jakob Sailer
# Author: Jakob Sailer <sailer.jakob@web.de>
# with snippets provided by https://proglang.informatik.uni-freiburg.de/teaching/advanced-programming/2019/


#
#
#  Sorry nur Aufgabe 3
#  Hatte diese Woche echt keine Zeit
#
#


CC = gcc
CFLAGS = --std=c11 -pedantic -Wall #-fsanitize=address,undefined -g -O0
BINARIES = cavetest wumpus wumpustest

.PHONY: all clean compile test checkstyle all

# all
all: checkstyle compile test


# delete
clean:
	rm -f $(BINARIES) *.o


# checkstyle
checkstyle:
	python3 ../cpplint3.py --filter=-runtime/int,-readability/casting,-runtime/threadsafe_fn --repository=. *.h *.c


# compile
compile: $(BINARIES)

# wumpus
cave.o: cave.c cave.h
	$(CC) $(CFLAGS) cave.c -c
	
cave: cave.o
	$(CC) $(CFLAGS) cave.o cave.c -o cave
	
cavetest: cave.o cavetest.c
	$(CC) $(CFLAGS) cave.o cavetest.c -o cavetest
	
wumpus.o: cave.o wumpus.c wumpus.h
	$(CC) $(CFLAGS) wumpus.c -c

wumpustest: cave.o wumpus.o wumpustest.c
	$(CC) $(CFLAGS) cave.o wumpus.o wumpustest.c -o wumpustest

# executable main
wumpus: cave.o wumpus.o wumpusMain.c
	$(CC) $(CFLAGS) cave.o wumpus.o wumpusMain.c -o wumpus


# tests
test:
	./cavetest
	./wumpustest


