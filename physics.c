// Physics
#include<stdbool.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include "types.h"
#include "audio.h"
#ifdef _WIN32
#include<ncursesw/ncurses.h>
#else
#include<ncurses.h>
#endif

// Player
void initPlayer(player *Player, int rows, int cols) {
    int i = 0;
    Player->maxX = cols;
    Player->maxY = rows-2;
    Player->oldX = cols/2;
    Player->oldY = rows-2;
    Player->X = cols/2;
    Player->Y = rows-2;
    Player->lives = MAX_PLAYER_LIVES;
    Player->score = 0;
    for(i=0; i<MAX_PLAYER_BULLETS; i++) {
        Player->bullets[i].active = false;
    }
}

// Invaders
void initInvaders(invader *Invaders, int maxCols, int wave) {
    int i = 0;
    int perLine = (maxCols - 20)/10;
    int spawnInvaders = perLine * wave > MAX_INVADERS ? MAX_INVADERS : perLine * wave;
    for(i = 0; i < MAX_INVADERS; i++) {
        Invaders[i].active = false;
        Invaders[i].bullet.active = false;
    }
    for(i = 0; i < spawnInvaders; i++) {
        Invaders[i].active = true;
        Invaders[i].X = ((i % perLine) * 10) + 10;
        Invaders[i].Y = (i / perLine) * 2;
        Invaders[i].oldX = Invaders[i].X;
        Invaders[i].oldY = Invaders[i].Y;
        Invaders[i].bullet.active = false;
    }
}

void moveInvaders(invader *Invaders, int *direction, int maxCol, int *wave) {
    int i, active = 0;
    bool moveDown = false;
    for(i = 0; i < MAX_INVADERS; i++) {
        if(!Invaders[i].active) continue;
        active++;
        Invaders[i].oldX = Invaders[i].X;
        Invaders[i].oldY = Invaders[i].Y;
        Invaders[i].X += *direction;
        moveDown = (Invaders[i].X == 2 || Invaders[i].X == maxCol-2 || moveDown);
    }
    if (active == 0) {
        *wave = *wave + 1;
        for(i = 0; i < MAX_INVADERS; i++) {
            if(Invaders[i].bullet.active) {
                Invaders[i].bullet.active = false;
                mvprintw(Invaders[i].bullet.Y, Invaders[i].bullet.X, " ");
            }
        }
        initInvaders(Invaders, maxCol, *wave);
    }
    if (moveDown) {
        *direction = 0-*direction;
        for(i = 0; i < MAX_INVADERS; i++) {
            if(!Invaders[i].active) continue;
            Invaders[i].Y++;
        }
    }
}

void fireInvaders(invader *Invaders, player *Player, int wave) {
    int i = 0;
    if(wave > 3) wave = 3;
    for(i = 0; i < MAX_INVADERS; i++) {
        if(!Invaders[i].active || Invaders[i].bullet.active) continue;
        if(Invaders[i].X == Player->X || (rand() % 10) > (10 - wave)) {
            Invaders[i].bullet.direction = BULLET_DOWN;
            Invaders[i].bullet.X = Invaders[i].X;
            Invaders[i].bullet.Y = Invaders[i].Y;
            Invaders[i].bullet.oldX = Invaders[i].X;
            Invaders[i].bullet.oldY = Invaders[i].Y;
            Invaders[i].bullet.active = true;
        }
    }
}

// Explosions
void initExplosions(explosion *Explosions) {
    int i = 0;
    for(i = 0; i < MAX_EXPLOSIONS; i++) {
        Explosions[i].X = 0;
        Explosions[i].Y = 0;
        Explosions[i].xEnd = 0;
        Explosions[i].yEnd = 0;
        Explosions[i].frames = 0;
        Explosions[i].active = false;
    }
}

void spawnExplosion(explosion *Explosions, int x, int y, int xEnd, int yEnd, int frames) {
    int i = 0;
    for(i = 0; i < MAX_EXPLOSIONS; i++) {
        if(Explosions[i].active) continue;
        Explosions[i].X = x;
        Explosions[i].Y = y;
        Explosions[i].xEnd = xEnd;
        Explosions[i].yEnd = yEnd;
        Explosions[i].frames = frames;
        Explosions[i].active = true;
        break;
    }
}

// Bullets
void moveBullets(player *Player, invader *Invaders) {
    int b = 0;
    for(b = 0; b < MAX_PLAYER_BULLETS; b++) {
        if(Player->bullets[b].active) {
            switch(Player->bullets[b].direction) {
            case BULLET_UP:
                if(Player->bullets[b].Y > 0) {
                    Player->bullets[b].oldY = Player->bullets[b].Y;
                    Player->bullets[b].Y--;
                    break;
                }
                Player->bullets[b].active = false;
                mvprintw(Player->bullets[b].Y, Player->bullets[b].X, " ");
                break;
            case BULLET_DOWN:
                if(Player->bullets[b].Y < Player->maxY) {
                    Player->bullets[b].oldY = Player->bullets[b].Y;
                    Player->bullets[b].Y++;
                    break;
                }
                Player->bullets[b].active = false;
                mvprintw(Player->bullets[b].Y, Player->bullets[b].X, " ");
                break;
            }
        }
    }
    for(b = 0; b < MAX_INVADERS; b++) {
        if(Invaders[b].bullet.active) {
            switch(Invaders[b].bullet.direction) {
            case BULLET_UP:
                if(Invaders[b].bullet.Y > 0) {
                    Invaders[b].bullet.oldY = Invaders[b].bullet.Y;
                    Invaders[b].bullet.Y--;
                    break;
                }
                Invaders[b].bullet.active = false;
                mvprintw(Invaders[b].bullet.Y, Invaders[b].bullet.X, " ");
                break;
            case BULLET_DOWN:
                if(Invaders[b].bullet.Y < Player->maxY) {
                    Invaders[b].bullet.oldY = Invaders[b].bullet.Y;
                    Invaders[b].bullet.Y++;
                    break;
                }
                Invaders[b].bullet.active = false;
                mvprintw(Invaders[b].bullet.Y, Invaders[b].bullet.X, " ");
                break;
            }
        }
    }
}

// Collisions
bool checkCollisions(player *Player, invader *Invaders, explosion *Explosions, SDL_AudioDeviceID audioId, Uint8 *explode, Uint32 len) {
    int ch = 0, b = 0, i = 0;
    for(b = 0; b < MAX_PLAYER_BULLETS; b++) {
        if(Player->bullets[b].active)
        {
            ch = mvinch(Player->bullets[b].Y, Player->bullets[b].X);
            switch((char)ch) {
                case '#':
                    Player->bullets[b].active = false;
                    spawnExplosion(Explosions, Player->bullets[b].X, Player->bullets[b].Y, Player->bullets[b].X, Player->bullets[b].Y, 6);
                    mvprintw(Player->bullets[b].oldY, Player->bullets[b].oldX, " ");
                    break;
                case '(':
                case '-':
                case 'O':
                case ')':
                    Player->bullets[b].active = false;
                    mvprintw(Player->bullets[b].oldY, Player->bullets[b].oldX, " ");
                    Player->score += 100;
                    for(i = 0; i<MAX_INVADERS; i++) {
                        if (!Invaders[i].active) continue;
                        if (Invaders[i].Y == Player->bullets[b].Y && Player->bullets[b].X >= Invaders[i].X-2 && Player->bullets[b].X <= Invaders[i].X+2) {
                            Invaders[i].active = false;
                            spawnExplosion(Explosions, Invaders[i].X-2, Invaders[i].Y, Invaders[i].X+2, Invaders[i].Y, 6);
                            if(audioId>0 && explode) {
                                playAudio(audioId, explode, len);
                            }
                            else {
                                beep();
                            }
                            break;
                        }
                    }
            }
        }
    }
    for(b = 0; b < MAX_INVADERS; b++) {
        if(Invaders[b].bullet.active)
        {
            ch = mvinch(Invaders[b].bullet.Y, Invaders[b].bullet.X);
            switch((char)ch) {
            case '#':
                Invaders[b].bullet.active = false;
                spawnExplosion(Explosions, Invaders[b].bullet.X, Invaders[b].bullet.Y, Invaders[b].bullet.X, Invaders[b].bullet.Y, 6);
                mvprintw(Invaders[b].bullet.oldY, Invaders[b].bullet.oldX, " ");
                break;
            case '-':
            case '!':
                if (Invaders[b].bullet.Y == Player->Y && Invaders[b].bullet.X >= Player->X-2 && Invaders[b].bullet.X <= Player->X+2) {
                    Invaders[b].bullet.active = false;
                    spawnExplosion(Explosions, Player->X-2, Player->Y, Player->X+2, Player->Y, 6);
                    mvprintw(Invaders[b].bullet.oldY, Invaders[b].bullet.oldX, " ");
                    Player->lives--;
                    Player->X = Player->maxX/2;
                    Player->oldX = Player->X;
                    flash();
                }
                break;
            }
        }
        if(Invaders[b].active && Invaders[b].Y == Player->Y) Player->lives = 0;
    }
    return Player->lives > 0;
}
