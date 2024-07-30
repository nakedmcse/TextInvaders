// Text based Space Invaders
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ncurses.h>
#include<SDL2/SDL.h>
#include<sqlite3.h>
#include "types.h"
#include "render.h"
#include "physics.h"
#include "input.h"

int main(void) {
    bool isRunning;
    int rows, cols, wave, hiscoreIndex;
    int frame_timer = 0, frame_divisor = 1000;
    int invaderDirection = INVADER_LEFT;
    player Player;
    invader Invaders[MAX_INVADERS];
    explosion Explosions[MAX_EXPLOSIONS];
    hiscore Hiscores[MAX_HISCORES];
    SDL_Joystick *joystick = NULL;
    sqlite3 *dbContext = NULL;

    // Init Screen and hi score table
    joystick = initScreen(&rows, &cols);
    initHiscores(&Hiscores[0], dbContext);

    do {
        // Init Game Objects
        wave = 1;
        initInvaders(&Invaders[0], cols, wave);
        initPlayer(&Player, rows, cols);
        initExplosions(&Explosions[0]);
        if(joystick) frame_divisor = 500;
        gameStart(rows, cols);
        initBases(rows, cols);
        isRunning = true;

        // Main Loop
        while(isRunning) {
            drawPlayer(Player);
            if(frame_timer == 0) moveInvaders(&Invaders[0], &invaderDirection, cols, &wave);
            drawInvaders(&Invaders[0]);
            isRunning = checkCollisions(&Player, &Invaders[0], &Explosions[0]);
            if(frame_timer == 0) drawExplosions(&Explosions[0], cols);
            if(frame_timer == 0) fireInvaders(&Invaders[0], &Player, wave);
            drawBullets(&Player, &Invaders[0]);
            if(frame_timer == 0) moveBullets(&Player, &Invaders[0]);
            drawScores(&Player, wave, cols);
            isRunning = pollInput(&Player, joystick, frame_timer) && isRunning;
            refresh();
            frame_timer++;
            frame_timer = frame_timer % frame_divisor;
        }

        if(Player.lives == 0) {
            hiscoreIndex = checkHiscore(&Player, &Hiscores[0], wave);
            gameOver(rows, cols, wave, hiscoreIndex, &Player, &Hiscores[0]);
        }
    } while(Player.lives == 0);

    endwin();
    SDL_JoystickClose(joystick);
    SDL_Quit();
    if (dbContext) sqlite3_close(dbContext);
    return 0;
}