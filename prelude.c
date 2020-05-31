#include <stdio.h>

#include "sound.h"

int main(int argc, char *argv[])
{
	int err = sound_open();
	if (err != 0) {
		printf("%s: Failed to initialize sound\n", argv[0]);
		return 1;
	}

	err = sound_play();
	if (err != 0) {
		printf("%s: Failed to play sound\n", argv[0]);
		return 1;
	}

	sound_close();

	return 0;
}
