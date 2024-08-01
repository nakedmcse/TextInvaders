// Input Engine
#ifndef TEXTINVADER_INPUT
#define TEXTINVADER_INPUT

void movePlayerLeft(player *Player) {
    if(Player->X-1 > 2) {
        Player->oldX = Player->X;
        Player->X--;
    }
}

void movePlayerRight(player *Player) {
    if(Player->X+1 < Player->maxX-2) {
        Player->oldX = Player->X;
        Player->X++;
    }
}

void spawnBullet(player *Player) {
    int b = 0;
    for(b = 0; b < MAX_PLAYER_BULLETS; b++) {
        if(Player->bullets[b].active == false) {
            Player->bullets[b].oldX = Player->X;
            Player->bullets[b].oldY = Player->Y-1;
            Player->bullets[b].X = Player->X;
            Player->bullets[b].Y = Player->Y-1;
            Player->bullets[b].active = true;
            Player->bullets[b].direction = BULLET_UP;
            break;
        }
    }
}

bool pollInput(player *Player, SDL_Joystick *joystick, int frame_timer) {
    int ch = getch();
    bool quit = false;

    if(joystick) {
        SDL_Event joyEvt;
        if (SDL_PollEvent(&joyEvt)) {
            if (joyEvt.type == SDL_JOYBUTTONDOWN) {
                spawnBullet(Player);
            }
        }

        int xaxis = SDL_JoystickGetAxis(joystick, 0);
        if (xaxis < -8000 & frame_timer == 0) {
            movePlayerLeft(Player);
        } else if (xaxis > 8000 & frame_timer == 0) {
            movePlayerRight(Player);
        }
    }

    switch((char)ch) {
    case 'z':
        movePlayerLeft(Player);
        break;
    case 'x':
        movePlayerRight(Player);
        break;
    case 'q':
        quit = true;
        break;
    case ' ':
        spawnBullet(Player);
        break;
    }

    return !quit;
}

#endif