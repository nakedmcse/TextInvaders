// Audio
#ifndef TEXTINVADERS_AUDIO
#define TEXTINVADERS_AUDIO

void initMixer(Mix_Chunk **fireBuffer, Mix_Chunk **explodeBuffer);
void playMixer(Mix_Chunk *buffer);
void closeMixer(Mix_Chunk *fireBuffer, Mix_Chunk *explodeBuffer);

#endif
