# TextInvaders
Text based space invaders in C.

Inspired by Dave Plumbers version on PDP.

## Building:
This uses the ncurses library and SDL2 library, which must both be installed in order to compile.

Mac:
```bash
brew install sdl2
gcc -O3 -o textinvaders -I/usr/local/include/SDL2 -D_THREAD_SAFE -L/usr/local/lib textinvaders.c -lncurses -lSDL2
```

Linux:
```bash
sudo apt-get install libsdl2-dev
gcc -O3 -o textinvaders textinvaders.c -lncurses -lSDL2
```