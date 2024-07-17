// Text based Space Invaders
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<ncurses.h>
#include "types.h"
#include "render.h"
#include "physics.h"
#include "input.h"

int main(void) {
    bool isRunning = true;
    int rows, cols;
    int frame_timer = 0;
    int invaderDirection = INVADER_LEFT;
    player Player;
    invader Invaders[MAX_INVADERS];

    // Init Game
    initScreen(&rows, &cols);
    initInvaders(&Invaders[0], cols);
    initPlayer(&Player, rows, cols);
    initBases(rows, cols);

    // Main Loop
    while(isRunning) {
        drawPlayer(Player);
        if(frame_timer == 0) moveInvaders(&Invaders[0], &invaderDirection, cols);
        drawInvaders(&Invaders[0]);
        isRunning = checkCollisions(&Player, &Invaders[0]);
        drawBullets(&Player);
        if(frame_timer == 0) moveBullets(&Player);
        drawScores(&Player, cols);
        isRunning = pollInput(&Player) && isRunning;
        refresh();
        frame_timer++;
        frame_timer = frame_timer % 1000;
    }

    endwin();
    return 0;
}