#include <fcntl.h>
#include <stdio.h>

static int stream = 0;

int sound_open() {
	stream = open("/dev/sound", O_WRONLY);
	if (stream == -1) {
		perror("Failed to open stream");
		return 1;
	}

	return 0;
}

int sound_play() {
	int err = 0;

	for (int t = 0; ; t++) {
		if (write(stream, &t, sizeof t) < 0) {
			perror("Failed to write to stream");
			return 1;
		}
	}

	return 0;
}

void sound_close() {
	int err = close(stream);
	if (err == -1) {
		perror("Failed to close stream");
	}
}
