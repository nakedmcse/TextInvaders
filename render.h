// Rendering Engine
#ifndef TEXTINVADER_RENDERING
#define TEXTINVADER_RENDERING

// Player
void drawPlayer(player Player) {
    mvprintw(Player.oldY, Player.oldX-2, "     ");
    mvprintw(Player.Y, Player.X-2, "--!--");
    Player.oldX = Player.X;
    Player.oldY = Player.Y;
}

// Invaders
void drawInvaders(invader *Invaders) {
    int i = 0;
    for(i = 0; i < MAX_INVADERS; i++) {
        if(!Invaders[i].active) continue;
        mvprintw(Invaders[i].oldY, Invaders[i].oldX-2, "     ");
        mvprintw(Invaders[i].Y, Invaders[i].X-2, "(-O-)");
        Invaders[i].oldX = Invaders[i].X;
        Invaders[i].oldY = Invaders[i].Y;
    }
}

// Explosions
void drawExplosions(explosion *Explosions, int maxCols) {
    int i, c = 0;
    char expChars[3] = ".xX";
    char expLine[maxCols];
    for(i = 0; i < MAX_EXPLOSIONS; i++) {
        if(!Explosions[i].active) continue;
        if(Explosions[i].frames == 0) {
            Explosions[i].active = false;
            for(c = 0; c <= (Explosions[i].xEnd - Explosions[i].X); c++) {
                expLine[c] = ' ';
            }
            expLine[c+1] = 0;
        }
        else {
            Explosions[i].frames--;
            for(c = 0; c <= (Explosions[i].xEnd - Explosions[i].X); c++) {
                expLine[c] = expChars[rand() % 3];
            }
            expLine[c+1] = 0;
        }
        mvprintw(0, 0, "Drawing Explosion %d at %d, %d as %s", i, Explosions[i].X, Explosions[i].Y, expLine);
        for(i = Explosions[i].Y; i <= Explosions[i].yEnd; i++) {
            mvprintw(i, Explosions[i].X, expLine);
        }
    }
}

// Bullets
void drawBullets(player *Player) {
    int b = 0;
    for(b = 0; b < MAX_PLAYER_BULLETS; b++) {
        if(Player->bullets[b].active) {
            mvprintw(Player->bullets[b].oldY, Player->bullets[b].oldX, " ");
            mvprintw(Player->bullets[b].Y, Player->bullets[b].X, "|");
            Player->bullets[b].oldX = Player->bullets[b].X;
            Player->bullets[b].oldY = Player->bullets[b].Y;
        }
    }
}

// Screen
void initScreen(int *actRows, int* actCols) {
    initscr();
    getmaxyx(stdscr, *actRows, *actCols);
    clear();
    curs_set(0);
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    refresh();
}

void drawScores(player *Player, int maxCols) {
    char hud[maxCols+1];
    int i = 0;
    for(i = 0; i<maxCols; i++) hud[i] = ' ';
    hud[maxCols] = 0;
    snprintf(hud, sizeof(hud), " Text Invaders!  SCORE:%05d  LIVES: ", Player->score);
    for(i = 0; i<Player->lives; i++) strcat(hud, "--!--   ");
    hud[strlen(hud)] = ' ';
    attron(A_REVERSE);
    mvprintw(Player->maxY+1,0,hud);
    attroff(A_REVERSE);
}

void initBases(int rows, int cols) {
    int i = 0;
    int perLine = (cols - 20)/10;
    for(i = 0; i<perLine; i++) {
        mvprintw(rows-4, (i*10)+10, "#####");
        mvprintw(rows-3, (i*10)+10, "#####");
    }
}

#endif