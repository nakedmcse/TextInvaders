// Text based Space Invaders
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#ifdef _WIN32
#include<ncursesw/ncurses.h>
#include "sqlite3.h"
#else
#include<ncurses.h>
#include<sqlite3.h>
#endif

#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include "types.h"
#include "render.h"
#include "physics.h"
#include "input.h"
#include "hiscores.h"
#include "audio.h"

#ifdef _WIN32
int WinMain(int argc, char*argv[]) {
# else
int main(void) {
#endif
    bool isRunning;
    int rows, cols, wave, hiscoreIndex;
#ifdef _WIN32
    int frame_timer = 0, frame_divisor = 50;
#else
    int frame_timer = 0, frame_divisor = 1000;
#endif
    int invaderDirection = INVADER_LEFT;
    player Player;
    invader Invaders[MAX_INVADERS];
    explosion Explosions[MAX_EXPLOSIONS];
    hiscore Hiscores[MAX_HISCORES];
    Mix_Chunk *fireWAV = NULL, *explodeWAV = NULL;
    SDL_Joystick *joystick = NULL;
    sqlite3 *dbContext = NULL;

    // Init Screen, Audio and hi score table
    initScreen(&rows, &cols);
    joystick = initSDL();
    initMixer(&fireWAV, &explodeWAV);
    dbContext = initHiscores(&Hiscores[0]);

    do {
        // Init Game Objects
        wave = 1;
        initInvaders(&Invaders[0], cols, wave);
        initPlayer(&Player, rows, cols);
        initExplosions(&Explosions[0]);
#ifdef _WIN32
        if(joystick) frame_divisor = 50;
#else
        if(joystick) frame_divisor = 500;
#endif
        gameStart(rows, cols);
        initBases(rows, cols);
        isRunning = true;

        // Main Loop
        while(isRunning) {
            isRunning = checkCollisions(&Player, &Invaders[0], &Explosions[0], explodeWAV);
            isRunning = pollInput(&Player, joystick, frame_timer, fireWAV) && isRunning;

            drawPlayer(Player);
            drawInvaders(&Invaders[0]);
            drawBullets(&Player, &Invaders[0]);
            drawScores(&Player, wave, cols);

            if(frame_timer == 0) {
                moveInvaders(&Invaders[0], &invaderDirection, cols, &wave);
                fireInvaders(&Invaders[0], &Player, wave);
                moveBullets(&Player, &Invaders[0]);
                drawExplosions(&Explosions[0], cols);
            }

            refresh();
            frame_timer++;
            frame_timer = frame_timer % frame_divisor;
        }

        if(Player.lives == 0) {
            hiscoreIndex = checkHiscore(&Player, &Hiscores[0], wave);
            gameOver(rows, cols, wave, hiscoreIndex, &Player, &Hiscores[0]);
            updateDbScores(dbContext, &Hiscores[0]);
        }
    } while(Player.lives == 0);

    endwin();
    SDL_JoystickClose(joystick);
    closeMixer(fireWAV, explodeWAV);
    SDL_Quit();
    if (dbContext) sqlite3_close(dbContext);
    return 0;
}