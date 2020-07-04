#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "sound.h"

#define AMPLITUDE 1
#define BPM 80
#define SECONDS_PER_MINUTE 60

/*
 * Note is the pitch in Hz.
 * Duration is how many seconds to write into the buffer.
 *
 * Returns the size of the new buffer in bytes.
 */
size_t gen_note(float **bufptr, int note, double duration)
{
	size_t length = duration * SOUND_SAMPLE_RATE;
	float *buf = calloc(length, sizeof (float));
	if (buf == NULL) {
		if (errno != 0) {
			perror("gen_note failed to allocate a buffer");
		}
		return 0;
	}

	for (int i = 0; i < length; i++) {
		buf[i] = (2 * AMPLITUDE / M_PI) * asinf(sinf(i * 2 * M_PI / (SOUND_SAMPLE_RATE/note)));
	}

	*bufptr = buf;
	return length * sizeof (float);
}

void song_play(int song[], size_t length)
{
	double t = 0;
	float *buf = NULL;
	for (int i = 0; i < length; i++) {
		size_t size = gen_note(&buf, song[i], (double)SECONDS_PER_MINUTE/BPM);

		int err = sound_play(buf, size);
		if (err != 0) {
			fputs("Failed to play sound\n", stderr);
			return;
		}

		free(buf);
		t += size;
	}
}

int main(int argc, char *argv[])
{
	int err = sound_open();
	if (err != 0) {
		fprintf(stderr, "%s: Failed to initialize sound\n", argv[0]);
		return 1;
	}

	int song[] = {440, 480, 1000, 200};
	size_t song_length = sizeof song / sizeof song[0];
	song_play(song, song_length);

	sound_close();

	return 0;
}
