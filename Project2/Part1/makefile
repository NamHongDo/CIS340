CC = gcc
CFLAGS = -std=gnu99 -Wall -g -I.
OBJ = padder.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

a: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run:
	./a
.PHONY: clean
clean:
	rm -f *.o *~ a
