#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "sound.h"

#define AMPLITUDE 0.20
#define SIXTEENTH_NOTES_PER_MINUTE 320
#define SECONDS_PER_MINUTE 60

/*
 * The pitch table is taken from the source code of Eric S. Raymond's speaker
 * device driver, version 1.4. You can find the most up to date version on his
 * website at http://www.catb.org/~esr/software.html.
 */

/*
 * The speaker.c code is copyright 1994 by Eric S. Raymond
 * <esr@snark.thyrsus.com>.  Use it as you like, as long as you include this
 * notice in any derived works and explain how you derived them from speaker.c
 * somewhere.
 *
 *	$Id: speaker.c,v 1.10 1994/10/24 22:35:06 esr Exp $
 */

/*
 * This is the American Standard A440 Equal-Tempered scale with frequencies
 * rounded to nearest integer. Thank Goddess for the good ol' CRC Handbook...
 * our octave 0 is standard octave 2.
 */
#define OCTAVE_NOTES	12	/* semitones per octave */
static int pitchtab[] =
{
/*        C     C#    D     D#    E     F     F#    G     G#    A     A#    B*/
/* 0 */   65,   69,   73,   78,   82,   87,   93,   98,  103,  110,  117,  123,
/* 1 */  131,  139,  147,  156,  165,  175,  185,  196,  208,  220,  233,  247,
/* 2 */  262,  277,  294,  311,  330,  349,  370,  392,  415,  440,  466,  494,
/* 3 */  523,  554,  587,  622,  659,  698,  740,  784,  831,  880,  932,  988,
/* 4 */ 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1975,
/* 5 */ 2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951,
/* 6 */ 4186, 4435, 4698, 4978, 5274, 5588, 5920, 6272, 6644, 7040, 7459, 7902,
};

/*
 * buf: An array of floats
 * buflen: The length of the array
 * note: An MML note number. It corresponds to the index of pitchtab plus 1.
 *   MML notes can be in the range 1-84.
 * t: The index of the first sample in the buffer relative to the beginning
 *   of the song. Used to align consecutive notes.
 *
 * Returns the number of samples written to the buffer.
 */
size_t gen_note(float *buf, size_t buflen, size_t note, size_t t)
{
	double freq = pitchtab[note - 1];

	int i;
	for (i = 0; i < buflen; i++) {
		buf[i] = fmod(AMPLITUDE * (t + i) * freq / SOUND_SAMPLE_RATE, AMPLITUDE) - AMPLITUDE / 2;
	}

	return i;
}

#define buflen (SECONDS_PER_MINUTE * SOUND_SAMPLE_RATE / SIXTEENTH_NOTES_PER_MINUTE)

void song_play(int song[], size_t songlen)
{
	size_t t = 0;
	float buf[buflen] = {0};

	for (size_t i = 0; i < songlen; i++) {
		t += gen_note(
			buf,
			buflen,
			song[i],
			t
		);

		int err = sound_play(buf, buflen);
		if (err != 0) {
			fputs("Failed to play sound\n", stderr);
			return;
		}
	}
}

int main(int argc, char *argv[])
{
	int err = sound_open();
	if (err != 0) {
		fprintf(stderr, "%s: Failed to initialize sound\n",
			argv[0]);
		return 1;
	}

	int song[] = {
		25, 29, 32, 37, 41, 32, 37, 41, 25, 29, 32, 37, 41, 32, 37, 41,
		25, 27, 34, 39, 42, 34, 39, 42, 25, 27, 34, 39, 42, 34, 39, 42,
		24, 27, 32, 39, 42, 32, 39, 42, 24, 27, 32, 39, 42, 32, 39, 42,
		25, 29, 32, 37, 41, 32, 37, 41, 25, 29, 32, 37, 41, 32, 37, 41,
		25, 29, 34, 41, 46, 34, 41, 46, 25, 29, 34, 41, 46, 34, 41, 46,
		25, 27, 31, 34, 39, 31, 34, 39, 25, 27, 31, 34, 39, 31, 34, 39,
		24, 27, 32, 39, 44, 32, 39, 44, 24, 27, 32, 39, 44, 32, 39, 44,
		24, 25, 29, 32, 37, 29, 32, 37, 24, 25, 29, 32, 37, 29, 32, 37,
		22, 25, 29, 32, 37, 29, 32, 37, 22, 25, 29, 32, 37, 29, 32, 37,
		17, 22, 27, 31, 37, 27, 31, 37, 17, 22, 27, 31, 37, 27, 31, 37,
		20, 24, 27, 32, 36, 27, 32, 36, 20, 24, 27, 32, 36, 27, 32, 36,
		20, 23, 29, 32, 38, 29, 32, 38, 20, 23, 29, 32, 38, 29, 32, 38,
		18, 22, 27, 34, 39, 27, 34, 39, 18, 22, 27, 34, 39, 27, 34, 39,
		18, 21, 27, 34, 39, 27, 34, 39, 18, 21, 27, 34, 39, 27, 34, 39,
		17, 20, 25, 32, 37, 25, 32, 37, 17, 20, 25, 32, 37, 25, 32, 37,
		17, 18, 22, 25, 30, 22, 25, 30, 17, 18, 22, 25, 30, 22, 25, 30,
		15, 18, 22, 25, 30, 22, 25, 30, 15, 18, 22, 25, 30, 22, 25, 30,
		 8, 15, 20, 24, 30, 20, 24, 30,  8, 15, 20, 24, 30, 20, 24, 30,
		13, 17, 20, 25, 29, 20, 25, 29, 13, 17, 20, 25, 29, 20, 25, 29,
		13, 20, 23, 25, 29, 23, 25, 29, 13, 20, 23, 25, 29, 23, 25, 29,
		 6, 18, 22, 25, 27, 22, 25, 27,  6, 18, 22, 25, 27, 22, 25, 27,
		 7, 13, 22, 25, 28, 22, 25, 28,  7, 13, 22, 25, 28, 22, 25, 28,
		 9, 18, 24, 25, 27, 24, 25, 27,  9, 18, 24, 25, 27, 24, 25, 27,
		 8, 18, 20, 24, 27, 20, 24, 27,  8, 18, 20, 24, 27, 20, 24, 27,
		 8, 17, 20, 25, 29, 20, 25, 29,  8, 17, 20, 25, 29, 20, 25, 29,
		 8, 15, 20, 25, 30, 20, 25, 30,  8, 15, 20, 25, 30, 20, 25, 30,
		 8, 15, 20, 24, 30, 20, 24, 30,  8, 15, 20, 24, 30, 20, 24, 30,
		 8, 16, 22, 25, 31, 22, 25, 31,  8, 16, 22, 25, 31, 22, 25, 31,
		 8, 17, 20, 25, 32, 20, 25, 32,  8, 17, 20, 25, 32, 20, 25, 32,
		 8, 15, 20, 25, 30, 20, 25, 30,  8, 15, 20, 25, 30, 20, 25, 30,
		 8, 15, 20, 24, 30, 20, 24, 30,  8, 15, 20, 24, 30, 20, 24, 30,
		 1, 13, 20, 23, 29, 20, 23, 29,  1, 13, 20, 23, 29, 20, 23, 29,
		 1, 13, 18, 22, 25, 30, 25, 22, 25, 22, 18, 22, 18, 15, 18, 15,
		 1, 12, 32, 36, 39, 42, 39, 36, 39, 36, 32, 36, 27, 30, 29, 27,
		25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
	};
	size_t song_length = sizeof song / sizeof song[0];
	song_play(song, song_length);

	sound_close();

	return 0;
}
