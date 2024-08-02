// Rendering Engine
#ifndef TEXTINVADER_PHYSICS
#define TEXTINVADER_PHYSICS

void initPlayer(player *Player, int rows, int cols);

void initInvaders(invader *Invaders, int maxCols, int wave);
void moveInvaders(invader *Invaders, int *direction, int maxCol, int *wave);
void fireInvaders(invader *Invaders, player *Player, int wave);

void initExplosions(explosion *Explosions);
void spawnExplosion(explosion *Explosions, int x, int y, int xEnd, int yEnd, int frames);
void moveBullets(player *Player, invader *Invaders);

bool checkCollisions(player *Player, invader *Invaders, explosion *Explosions, SDL_AudioDeviceID audioId, Uint8 *explode, Uint32 len);

#endif