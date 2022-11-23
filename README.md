# Prelude in C

An implementation of Bach's [Prelude in C, BWV 846][1].

## Goals

* Expore making music with programming
* Learn about audio APIs
* Learn how to write a multiplatform C program
* It would be nice if it actually sounds good
  * My favorite recording of Prelude in C is [this performance by Martha
    Goldstein on the harpsichord][2]. This little program doesn't sound as
    good as that, but it's enough to make me smile.

## Design

* The music is defined as an array of integers that are [MML][3] note numbers.
  For more details, see the source code of prelude.c or consult a BSD man page
  for the [speaker device][4].
* I want to port it to every free operating system I can get my hands on.
* No third-party libraries. I actually want to learn the platform-specific
  APIs.
* It's in a file called prelude.c!

## How to run it

    ./configure
    make
    ./prelude

[1]: https://en.wikipedia.org/wiki/Prelude_and_Fugue_in_C_major,_BWV_846
[2]: https://en.wikipedia.org/wiki/File:Johann_Sebastian_Bach_-_The_Well-tempered_Clavier_-_Book_1_-_02Epre_cmaj.ogg
[3]: https://en.wikipedia.org/wiki/Music_Macro_Language
[4]: https://www.freebsd.org/cgi/man.cgi?query=speaker&manpath=FreeBSD+12.1-RELEASE+and+Ports
