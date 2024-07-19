// Types and Defines
#ifndef TEXTINVADER_TYPES
#define TEXTINVADER_TYPES

// Defs
#define BULLET_UP 0
#define BULLET_DOWN 1
#define INVADER_LEFT -1
#define INVADER_RIGHT 1
#define MAX_PLAYER_BULLETS 5
#define MAX_PLAYER_LIVES 3
#define MAX_INVADERS 48
#define MAX_EXPLOSIONS 100

// Types
typedef struct bullet {
    int oldX, oldY, X, Y;
    bool active;
    int direction;
} bullet;

typedef struct player {
    int oldX, oldY, X, Y, maxX, maxY, lives, score;
    bullet bullets[MAX_PLAYER_BULLETS];
} player;

typedef struct invader {
    int oldX, oldY, X, Y;
    bool active;
    bullet bullet;
} invader;

typedef struct explosion {
    int X, Y, xEnd, yEnd, frames;
    bool active;
} explosion;

#endif