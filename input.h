// Input Engine
#ifndef TEXTINVADER_INPUT
#define TEXTINVADER_INPUT

void movePlayerLeft(player *Player);
void movePlayerRight(player *Player);
bool spawnBullet(player *Player);
bool pollInput(player *Player, SDL_Joystick *joystick, int frame_timer, SDL_AudioDeviceID audioId, Uint8 *fire, Uint32 len);

#endif