.POSIX:
.SUFFIXES:

CC = cc
CFLAGS = -Wall -g -pedantic

prelude: prelude.c
	$(CC) $(CFLAGS) prelude.c -o $@

.PHONY: clean
clean:
	rm -f prelude
