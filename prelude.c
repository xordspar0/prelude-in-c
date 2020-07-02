#include <math.h>
#include <stdio.h>

#include "sound.h"

#define FREQ 440
#define AMPLITUDE 1

/*
 * Returns the number of bytes written to the buffer.
 */
int fill_buf(float *buf, size_t bufsize, int offset) {
	int initial_offset = offset;

	for (int i = 0; i < bufsize; i++) {
		buf[i] = (2 * AMPLITUDE / M_PI) * asinf(sinf(offset * 2 * M_PI / (SOUND_SAMPLE_RATE/FREQ)));
		offset++;
	}

	return offset - initial_offset;
}

int main(int argc, char *argv[])
{
	int err = sound_open();
	if (err != 0) {
		printf("%s: Failed to initialize sound\n", argv[0]);
		return 1;
	}

	int sample = 0;
	float buf[1024];
	for (;;) {
		sample += fill_buf(buf, sizeof buf / sizeof buf[0], sample);

		err = sound_play(buf, sizeof buf);
		if (err != 0) {
			printf("%s: Failed to play sound\n", argv[0]);
			return 1;
		}
	}

	sound_close();

	return 0;
}
