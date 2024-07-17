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

void drawExplosion(int x, int y, int xEnd, int yEnd, int maxCols) {
    char expBigLine[maxCols];
    char expSmallLine[maxCols];
    char expBlankLine[maxCols];
    int i = 0;
    for(i = 0; i<maxCols; i++) {
        expBigLine[i] = 0;
        expSmallLine[i] = 0;
        expBlankLine[i] = 0;
    }
    for(i = 0; i <= (xEnd - x); i++) {
        expBigLine[i] = 'X';
        expSmallLine[i] = 'x';
        expBlankLine[i] = ' ';
    }
    for(i = y; i <= yEnd; i++) {
        mvprintw(i, x, expBigLine);
    }
    refresh();
    for(i = y; i <= yEnd; i++) {
        mvprintw(i, x, expSmallLine);
    }
    refresh();
    for(i = y; i <= yEnd; i++) {
        mvprintw(i, x, expBlankLine);
    }
    refresh();
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