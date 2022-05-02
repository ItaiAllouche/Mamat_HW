CC=gcc
CLINK=$(CC)
CFLAGS= -g -Wall -std=c99

all: libgrades.so  

libgrades.so: grades.o
	$(CLINK) -shared grades.o -o libgrades.so -llinked-list -L.

grades.o: grades.c grades.h
	$(CC) -c -fpic grades.c

clean:
	rm -rf *.o 