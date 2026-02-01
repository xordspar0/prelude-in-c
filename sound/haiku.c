#include <stdio.h>

#include <os/MediaKit.h>
#include <os/media/MediaDefs.h>

#include "../sound.h"

#define RING_BUFFER_SIZE 8192

typedef struct RingBuffer {
	float *buf;
	size_t size;
	size_t first;
	size_t last;
} RingBuffer;

static RingBuffer ring_buffer;
static BSoundPlayer *player;

static void fill_sound(void *context, void *buffer, size_t output_size, const media_raw_audio_format &format) {
	RingBuffer *input = (RingBuffer *) context;
	float *output = (float *) buffer;
	
	size_t samples_written = 0;
	while (input->first != input->last && samples_written < output_size / sizeof *output) {
		output[samples_written++] = input->buf[input->first];
		input->first = (input->first + 1) % input->size;
	}
}

int sound_open(void)
{
	float *buf = (float *) calloc(RING_BUFFER_SIZE, sizeof(float));
	if (buf == NULL) {
		fputs("failed to allocate ring buffer", stderr);
		return 1;
	}
	
	ring_buffer = {
		.buf = buf,
		.size = RING_BUFFER_SIZE,
		.first = 0,
		.last = 0,
	};

	media_raw_audio_format format = {
		.frame_rate = SOUND_SAMPLE_RATE,
		.channel_count = 1,
		.format = media_raw_audio_format::B_AUDIO_FLOAT,
		.byte_order = B_MEDIA_HOST_ENDIAN,
		.buffer_size = 0,
	};

	player = new BSoundPlayer(&format, "prelude.c", fill_sound, NULL, &ring_buffer);
	player->Start();
	player->SetHasData(true);
	
	return 0;
}

size_t sound_play(float *buf, size_t buflen)
{
	size_t samples_written = 0;
	size_t next = (ring_buffer.last + 1) % ring_buffer.size;
	
	while (samples_written < buflen) {
		while (next == ring_buffer.first) {}
		
		ring_buffer.buf[next] = buf[samples_written];
		samples_written++;
		ring_buffer.last = next;
		next = (ring_buffer.last + 1) % ring_buffer.size;
	}

	return 0;
}

void sound_close(void)
{
	float silence_buffer[2 * RING_BUFFER_SIZE];
	memset(silence_buffer, 0, sizeof silence_buffer);
	sound_play(silence_buffer, sizeof silence_buffer / sizeof silence_buffer[0]);

	player->Stop(true, false);
	delete player;
}
