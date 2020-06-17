#include <stdio.h>

#include <pulse/error.h>
#include <pulse/simple.h>

static pa_simple *stream = NULL;

int sound_open() {
	pa_sample_spec spec;
	int err = 0;

	spec.format = PA_SAMPLE_U8;
	spec.channels = 1;
	spec.rate = 8000;

	stream = pa_simple_new(
		NULL,
		"prelude",
		PA_STREAM_PLAYBACK,
		NULL,
		"Play Bach's Prelude in C",
		&spec,
		NULL,
		NULL,
		&err
	);

	if (stream == NULL) {
		fprintf(stderr, "Failed to open pulseaudio stream: %s", pa_strerror(err));
		return 1;
	}

	return 0;
}

int sound_play() {
	int err = 0;

	for (int t = 0; ; t++) {
		if (pa_simple_write(stream, &t, sizeof t, &err) < 0) {
			fprintf(stderr, "Failed to write to pulseaudio stream: %s", pa_strerror(err));
			return 1;
		}
	}

	return 0;
}

void sound_close() {
	pa_simple_free(stream);
}