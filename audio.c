// Audio
#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>

void initMixer(Mix_Chunk **fireBuffer, Mix_Chunk **explodeBuffer) {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    *fireBuffer = Mix_LoadWAV("assets/fire.wav");
    *explodeBuffer = Mix_LoadWAV("assets/explode.wav");
}

void playMixer(Mix_Chunk *buffer) {
    Mix_PlayChannel(-1, buffer, 0);
}

void closeMixer(Mix_Chunk *fireBuffer, Mix_Chunk *explodeBuffer) {
    Mix_FreeChunk(fireBuffer);
    Mix_FreeChunk(explodeBuffer);
    Mix_Quit();
}