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
	* Encode waveforms in an array? Kinda boring...also, it would be very hard
	  to compose music by writing bytes into an array.
	* Write it in a MIDI kind of representation and write a player that can
	  generate sound from that?
	* Write C arrays that look like a music tracker table? Cool but
	  potientially complicated
	* Just use simple strings that are a subset of
	  [MML](https://en.wikipedia.org/wiki/Music_Macro_Language)
* No third-party libraries. I actually want to learn the platform-specific
  APIs.
* Build it with a plain Makefile. I'm interested in learning how to write
  portable Makefiles.
* It's in a file called prelude.c!
