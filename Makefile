.POSIX:
.SUFFIXES:

CC = cc
CFLAGS = -Wall -g -pedantic

prelude: prelude.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f prelude
