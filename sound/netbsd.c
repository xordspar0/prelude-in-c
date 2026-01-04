#include <assert.h>
#include <fcntl.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <sys/audioio.h>

#include "../sound.h"

static int stream = 0;

int sound_open(void)
{
	stream = open("/dev/sound", O_WRONLY);
	if (stream < 0) {
		perror("Failed to open stream");
		return 1;
	}

	audio_info_t info;
	AUDIO_INITINFO(&info);
	info.play.sample_rate = SOUND_SAMPLE_RATE;
	info.play.channels = 1;
	info.play.precision = 32;
	info.play.encoding = AUDIO_ENCODING_SLINEAR;

	int err = ioctl(stream, AUDIO_SETINFO, &info);
	if (err < 0) {
		perror("Failed to set stream format");
		return 1;
	}

	return 0;
}

int sound_play(float *buf, size_t buflen)
{
	int32_t ibuf[buflen];

	for (int i = 0; i < buflen; i++) {
		ibuf[i] = buf[i] * INT32_MAX;
	}

	int count = write(stream, ibuf, sizeof ibuf);
	if (count < 0) {
		perror("Failed to write to stream");
		return 1;
	}

	return 0;
}

void sound_close(void)
{
	int err = close(stream);
	if (err < 0) {
		perror("Failed to close stream");
	}
}
