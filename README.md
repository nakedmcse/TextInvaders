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

Windows:
```bash
Download w64devkit and extract to c:\w64devkit
https://github.com/skeeto/w64devkit/releases/

Dowload SDL2 mingw release zip file
https://github.com/libsdl-org/SDL/releases
Extract bin, include, share and lib from x86_64-w64-mingw32 folder to c:\w64devkit (ie merge the folders)

Download NCurses mingw zip file
https://invisible-island.net/datafiles/release/mingw64.zip
extract bin, include and lib to c:\w64devkit (ie merge the folders)

Open CMD
cd c:\w64devkit\src
git clone https://github.com/nakedmcse/TextInvaders
Edit textinvaders.c line 6 change to #include<ncursesw/ncurses.h>
Edit textinvaders.c line 13 change to int WinMain(int argc, char*argv[])
Edit textinvaders.c line 16 int frame_timer = 0, frame_divisor = 50;

cd ..
w64devkit.exe
cd /w64devkit
gcc -O3 -o textinvaders.exe src/TextInvaders/textinvaders.c -IC:/w64devkit/include -lncurses -lSDL2
textinvaders.exe
```