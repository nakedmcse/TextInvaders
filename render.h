// Rendering Engine
#ifndef TEXTINVADER_RENDERING
#define TEXTINVADER_RENDERING

void drawPlayer(player Player);
void drawInvaders(invader *Invaders);
void drawExplosions(explosion *Explosions, int maxCols);
void drawBullets(player *Player, invader *Invaders);
void drawScores(player *Player, int wave, int maxCols);

void initScreen(int *actRows, int* actCols);
SDL_Joystick *initSDL();
void initBases(int rows, int cols);

void gameOver(int rows, int cols, int wave, int hiscoreIndex, player *Player, hiscore *Hiscores);
void gameStart(int rows, int cols);

#endif