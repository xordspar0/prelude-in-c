#include <stdio.h>

#include "sound.h"

void fill_buf(float *buf, size_t bufsize) {
	for (int i = 0; i < bufsize; i++) {
		buf[i] = i;
	}
}

int main(int argc, char *argv[])
{
	int err = sound_open();
	if (err != 0) {
		printf("%s: Failed to initialize sound\n", argv[0]);
		return 1;
	}

	float buf[1024];
	for (;;) {
		fill_buf(buf, sizeof buf / sizeof buf[0]);

		err = sound_play(buf, sizeof buf / sizeof buf[0]);
		if (err != 0) {
			printf("%s: Failed to play sound\n", argv[0]);
			return 1;
		}
	}

	sound_close();

	return 0;
}
