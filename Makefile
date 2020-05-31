# Requires GNU Make. I would like to use POSIX make, or at least a common set
# of features that work with GNU Make and the BSD makes, but I can't figure out
# how to make it work with the conditional compiling and linking.

CC = cc
CFLAGS = -Wall -g -pedantic
LDFLAGS =

platform != uname -s
ifeq ($(platform), Linux)
	platform_sound = sound/linux.c 
	LDFLAGS += -lpulse -lpulse-simple
else
	platform_sound = $(error Platform not supported)
endif
platform_object = $(platform_sound:.c=.o)

prelude: prelude.o sound.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

prelude.o: prelude.c sound.h
sound.o: $(platform_object)
	cp $< $@

$(platform_object): $(platform_sound) sound.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f prelude *.o sound/*.o
