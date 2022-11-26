#include <stdio.h>

#include <alsa/asoundlib.h>

#include "../sound.h"

static snd_pcm_t *stream = NULL;

int sound_open()
{
	int err = 0;

	err = snd_pcm_open(&stream, "default", SND_PCM_STREAM_PLAYBACK, 0);
	if (err) {
		fprintf(stderr, "Failed to open stream: %s\n",
			snd_strerror(err));
		return 1;
	}

	err = snd_pcm_set_params(stream,
			SND_PCM_FORMAT_FLOAT_LE,
			SND_PCM_ACCESS_RW_INTERLEAVED,
			1,
			SOUND_SAMPLE_RATE,
			1,
			500000);
	if (err) {
		fprintf(stderr, "Failed to configure stream: %s\n",
			snd_strerror(err));
		return 1;
	}

	return 0;
}

int sound_play(float *buf, size_t bufsize)
{
	snd_pcm_sframes_t count = snd_pcm_writei(
			stream, buf, bufsize / sizeof buf[0]);
	if (count < 0) {
		fprintf(stderr,
			"Failed to write to stream: %s\n",
			snd_strerror(count));
		return 1;
	}

	return 0;
}

void sound_close()
{
	int err = snd_pcm_drain(stream);
	if (err) {
		fprintf(stderr,
			"Failed to drain stream: %s\n",
			snd_strerror(err));
	}
	snd_pcm_close(stream);
}
