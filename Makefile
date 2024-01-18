.POSIX:
.SUFFIXES:
include config.mk

prelude: prelude.o sound/$(PLATFORM).o
	$(CC) -o prelude prelude.o sound/$(PLATFORM).o $(LDLIBS)
prelude.o: prelude.c sound.h
$(PLATFORM).o: $(PLATFORM).c sound.h

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -f prelude *.o sound/*.o
