// Audio
#include<SDL2/SDL.h>

SDL_AudioDeviceID initAudio(Uint8 **fireBuffer, Uint32 *fireLen, Uint8 **explodeBuffer, Uint32 *explodeLen) {
    SDL_AudioSpec wavSpec;
    SDL_LoadWAV("assets/fire.wav", &wavSpec, fireBuffer, fireLen);
    SDL_LoadWAV("assets/explode.wav", &wavSpec, explodeBuffer, explodeLen);
    return SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
}

void playAudio(SDL_AudioDeviceID id, Uint8 *buffer, Uint32 len) {
    SDL_ClearQueuedAudio(id);
    SDL_QueueAudio(id, buffer, len);
    SDL_PauseAudioDevice(id, 0);
}

void closeAudio(SDL_AudioDeviceID id, Uint8 *fireBuffer, Uint8 *explodeBuffer) {
    SDL_CloseAudioDevice(id);
    SDL_FreeWAV(fireBuffer);
    SDL_FreeWAV(explodeBuffer);
}
