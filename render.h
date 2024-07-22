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
    int i, j, c = 0;
    char expChars[6] = ".oO*xX";
    char expLine[maxCols];
    for(i = 0; i < MAX_EXPLOSIONS; i++) {
        if(!Explosions[i].active) continue;
        if(Explosions[i].frames == 0) {
            Explosions[i].active = false;
            for(c = 0; c <= (Explosions[i].xEnd - Explosions[i].X); c++) {
                expLine[c] = ' ';
            }
            expLine[(Explosions[i].xEnd - Explosions[i].X)+1] = 0;
        }
        else {
            Explosions[i].frames--;
            for(c = 0; c <= (Explosions[i].xEnd - Explosions[i].X); c++) {
                expLine[c] = expChars[rand() % 6];
            }
            expLine[(Explosions[i].xEnd - Explosions[i].X)+1] = 0;
        }
        for(j = Explosions[i].Y; j <= Explosions[i].yEnd; j++) {
            mvprintw(j, Explosions[i].X, expLine);
        }
    }
}

// Bullets
void drawBullets(player *Player, invader *Invaders) {
    int b = 0;
    for(b = 0; b < MAX_PLAYER_BULLETS; b++) {
        if(Player->bullets[b].active) {
            mvprintw(Player->bullets[b].oldY, Player->bullets[b].oldX, " ");
            mvprintw(Player->bullets[b].Y, Player->bullets[b].X, "|");
            Player->bullets[b].oldX = Player->bullets[b].X;
            Player->bullets[b].oldY = Player->bullets[b].Y;
        }
    }
    for(b = 0; b < MAX_INVADERS; b++) {
        if(Invaders[b].bullet.active) {
            mvprintw(Invaders[b].bullet.oldY, Invaders[b].bullet.oldX, " ");
            mvprintw(Invaders[b].bullet.Y, Invaders[b].bullet.X, "*");
            Invaders[b].bullet.oldX = Invaders[b].bullet.X;
            Invaders[b].bullet.oldY = Invaders[b].bullet.Y;
        }
    }
}

// Screen
SDL_Joystick *initScreen(int *actRows, int* actCols) {
    initscr();
    getmaxyx(stdscr, *actRows, *actCols);
    clear();
    curs_set(0);
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    refresh();
    SDL_Init(SDL_INIT_GAMECONTROLLER);
    return SDL_JoystickOpen(0);
}

void drawScores(player *Player, int wave, int maxCols) {
    char hud[maxCols+1];
    int i = 0;
    for(i = 0; i<maxCols; i++) hud[i] = ' ';
    hud[maxCols] = 0;
    snprintf(hud, sizeof(hud), " Text Invaders!  SCORE:%05d  WAVE:%02d  LIVES: ", Player->score, wave);
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

void gameOver(int rows, int cols, int wave, player *Player) {
    clear();
    mvprintw(rows/2, (cols-16)/2, "G A M E  O V E R");
    mvprintw((rows/2)+2, (cols-21)/2, "SCORE: %05d  WAVE: %02d", Player->score, wave);
    refresh();
    while(getch() == ERR) {};
    clear();
}

void gameStart(int rows, int cols) {
    clear();
    int r = (rows/2) - 2;
    attron(A_REVERSE);
    mvprintw(r, (cols-27)/2, " T E X T  I N V A D E R S ! ");
    attroff(A_REVERSE);
    mvprintw(r+2, (cols-26)/2, "Z   | Joystick Left -- Left");
    mvprintw(r+3, (cols-26)/2, "X   | Joystick Right -- Right");
    mvprintw(r+4, (cols-26)/2, "SPC | Joystick Fire -- Shoot");
    mvprintw(r+5, (cols-26)/2, "Q                   -- Quit");
    mvprintw(r+7, (cols-22)/2, "Press any key to start");
    refresh();
    while(getch() == ERR) {};
    clear();
}

#endif