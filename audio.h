// Audio
#ifndef TEXTINVADERS_AUDIO
#define TEXTINVADERS_AUDIO

SDL_AudioDeviceID initAudio(Uint8 **fireBuffer, Uint32 *fireLen, Uint8 **explodeBuffer, Uint32 *explodeLen);
void playAudio(SDL_AudioDeviceID id, Uint8 *buffer, Uint32 len);
void closeAudio(SDL_AudioDeviceID id, Uint8 *fireBuffer, Uint8 *explodeBuffer);

#endif
