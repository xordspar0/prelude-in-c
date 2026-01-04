#define SOUND_SAMPLE_RATE 44100

int sound_open(void);
int sound_play(float *buf, size_t buflen);
void sound_close(void);
