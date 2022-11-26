#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/soundcard.h>

#include "../sound.h"

static int stream = 0;

int sound_open()
{
	int sample_rate = SOUND_SAMPLE_RATE;
	int channels = 1;
	int format = AFMT_S32_NE;
	int err = 0;

	stream = open("/dev/dsp", O_WRONLY);
	if (stream < 0) {
		perror("Failed to open stream");
		return 1;
	}

	err = ioctl(stream, SNDCTL_DSP_SPEED, &sample_rate);
	if (err < 0) {
		perror("Failed to set stream sample rate");
		return 1;
	}
	err = ioctl(stream, SNDCTL_DSP_CHANNELS, &channels);
	if (err < 0) {
		perror("Failed to set stream channel count");
		return 1;
	}
	err = ioctl(stream, SNDCTL_DSP_SETFMT, &format);
	if (err < 0) {
		perror("Failed to set stream format");
		return 1;
	}

	return 0;
}

int sound_play(float *buf, size_t bufsize)
{
	size_t n_items = bufsize / sizeof buf[0];
	int32_t ibuf[n_items];

	for (int i = 0; i < n_items; i++) {
		ibuf[i] = buf[i] * (float)INT32_MAX;
	}

	int count = write(stream, ibuf, bufsize);
	if (count < 0) {
		perror("Failed to write to stream");
		return 1;
	}

	return 0;
}

void sound_close()
{
	int err = close(stream);
	if (err < 0) {
		perror("Failed to close stream");
	}
}
