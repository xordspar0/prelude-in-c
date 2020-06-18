typedef float songbuf_t;

int sound_open();
int sound_play(songbuf_t *buf, size_t bufsize);
void sound_close();
