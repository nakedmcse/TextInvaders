// Rendering Engine
#ifndef TEXTINVADER_PHYSICS
#define TEXTINVADER_PHYSICS

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
void initInvaders(invader *Invaders, int maxCols) {
    int i = 0;
    int perLine = (maxCols - 20)/10;
    for(i = 0; i < MAX_INVADERS; i++) {
        Invaders[i].active = true;
        Invaders[i].X = ((i % perLine) * 10) + 10;
        Invaders[i].Y = (i / perLine) * 2;
        Invaders[i].oldX = Invaders[i].X;
        Invaders[i].oldY = Invaders[i].Y;
    }
}

void moveInvaders(invader *Invaders, int *direction, int maxCol) {
    int i = 0;
    bool moveDown = false;
    for(i = 0; i < MAX_INVADERS; i++) {
        if(!Invaders[i].active) continue;
        Invaders[i].oldX = Invaders[i].X;
        Invaders[i].oldY = Invaders[i].Y;
        Invaders[i].X += *direction;
        moveDown = (Invaders[i].X == 0 || Invaders[i].X == maxCol-5 || moveDown);
    }
    if (moveDown) {
        *direction = 0-*direction;
        for(i = 0; i < MAX_INVADERS; i++) {
            if(!Invaders[i].active) continue;
            Invaders[i].Y++;
        }
    }
}

// Bullets
void moveBullets(player *Player) {
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
}

// Collisions
bool checkCollisions(player *Player, invader *Invaders) {
    int ch = 0, b = 0, i = 0;
    char balls[2];
    for(b = 0; b < MAX_PLAYER_BULLETS; b++) {
        if(Player->bullets[b].active)
        {
            ch = mvinch(Player->bullets[b].Y, Player->bullets[b].X);
            balls[0] = ch;
            balls[1] = 0;
            mvprintw(0,0,balls);
            switch((char)ch) {
                case '#':
                    Player->bullets[b].active = false;
                    drawExplosion(Player->bullets[b].X, Player->bullets[b].Y, Player->bullets[b].X, Player->bullets[b].Y, Player->maxX);
                case '(':
                case '-':
                case 'O':
                case ')':
                    Player->bullets[b].active = false;
                    Player->score += 100;
                    for(i = 0; i<MAX_INVADERS; i++) {
                        if (!Invaders[i].active) continue;
                        if (Invaders[i].Y == Player->bullets[b].Y && Player->bullets[b].X >= Invaders[i].X && Player->bullets[b].X <= Invaders[i].X+4) {
                            Invaders[i].active = false;
                            drawExplosion(Invaders[i].X, Invaders[i].Y, Invaders[i].X+4, Invaders[i].Y, Player->maxX);
                        }
                    }
            }
        }
    }
    return true;
}

#endif