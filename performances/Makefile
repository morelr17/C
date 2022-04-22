CFLAGS = -Wall -Wextra
CC = gcc

all: cat mcat-lib

cat: cat.o
	$(CC) -o $@ $^ 

cat.o: cat.c
	$(CC) -o $@ -c $^ $(CFLAGS)

mcat-lib: mcat-lib.o
	$(CC) -o $@ $^ 

mcat-lib.o: mcat-lib.c
	$(CC) -o $@ -c $^ $(CFLAGS)

clean:
	rm -f *.o cat mcat-lib

.PHONY: all clean