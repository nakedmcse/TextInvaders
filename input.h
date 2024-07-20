// Input Engine
#ifndef TEXTINVADER_INPUT
#define TEXTINVADER_INPUT

bool pollInput(player *Player, SDL_Joystick *joystick, int frame_timer) {
    int ch = getch();
    int b = 0;
    bool quit = false;

    if(joystick) {
        SDL_Event joyEvt;
        while (SDL_PollEvent(&joyEvt)) {
            if (joyEvt.type == SDL_JOYBUTTONDOWN) {
                ch = ' '; // pass fire to action
            }
        }

        int xaxis = SDL_JoystickGetAxis(joystick, 0);
        if (xaxis < -8000 & frame_timer == 0) {
            ch = 'z';
        } else if (xaxis > 8000 & frame_timer == 0) {
            ch = 'x';
        }
    }

    switch((char)ch) {
    case 'z':
        if(Player->X-1 > 2) {
            Player->oldX = Player->X;
            Player->X--;
        }
        break;
    case 'x':
        if(Player->X+1 < Player->maxX-2) {
            Player->oldX = Player->X;
            Player->X++;
        }
        break;
    case 'q':
        quit = true;
        break;
    case ' ':
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
        break;
    }

    return !quit;
}

#endif