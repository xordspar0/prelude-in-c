#define SOUND_SAMPLE_RATE 44100
typedef float songbuf_t;
#if defined(__linux__)
#define SOUND_SAMPLE_PRECISION PA_SAMPLE_FLOAT32LE
#elif defined(__NetBSD__)
#define SOUND_SAMPLE_PRECISION 32
#endif

int sound_open();
int sound_play(songbuf_t *buf, size_t bufsize);
void sound_close();
