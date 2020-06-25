#define SOUND_SAMPLE_RATE 44100

int sound_open();
int sound_play(float *buf, size_t bufsize);
void sound_close();
