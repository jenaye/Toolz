CC=gcc
OPTIONS=-I.
DEPS = Show.h ReadStream.h
OBJ = Hexit.o Show.o ReadStream.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(OPTIONS)

Hexit: $(OBJ)
	$(CC) -o Hexit Hexit.c ReadStream.o Show.o -I.
	make clean
.PHONY: clean

clean:
	rm -f *.o
