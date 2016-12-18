CC = gcc
CFLAGS = -std=gnu99 -Wall -g -I.
DEPS = shell.h
OBJ = main.c shell.c single.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run:
	./main

.PHONY: clean

clean:
	rm -f *.o *~ main
