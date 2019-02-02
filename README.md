# Prelude in C

An implementation of Bach's [Prelude in C, BWV
846](https://en.wikipedia.org/wiki/Prelude_and_Fugue_in_C_major,_BWV_846).

## Goals

* Expore making music with programming
* Learn about audio APIs
* Learn how to write a multiplatform C program
* It would be nice if it actually sounds good

## Design

* The music should somehow be defined by code
	* Encode it in an array and render to a waveform? Kinda boring...also, it
	  would be very hard to compose music by writing bytes into an array.
	* Write it in a MIDI kind of representation and write a player that can
	  generate sound from that?
* No third-party libraries. I actually want to learn the platform-specific
  APIs.
* Build it with a plain Makefile. I'm interested in learning how to write
  portable Makefiles.
* It's in a file called prelude.c!
