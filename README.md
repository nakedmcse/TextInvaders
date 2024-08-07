# TextInvaders
Text based space invaders in C.

Inspired by Dave Plumbers version on PDP.

## Building:
This uses the ncurses, SQLite3 and SDL2 libraries, which must all be installed in order to compile.

Mac:
```bash
brew install sdl2 sdl2_mixer sqlite
make
```

Linux:
```bash
sudo apt-get install libsdl2-dev libsdl2-mixer-dev sqlite3 libsqlite3-dev
make
```

Windows:
```bash
Download w64devkit and extract to c:\w64devkit
https://github.com/skeeto/w64devkit/releases/

Download SDL2 mingw release zip file
https://github.com/libsdl-org/SDL/releases
Extract bin, include, share and lib from x86_64-w64-mingw32 folder to c:\w64devkit

Download SDL2 mixer mingw release zip file
https://github.com/libsdl-org/SDL_mixer/releases 
Extract bin, include, share and lib from x86_64-w64-mingw32 folder to c:\w64devkit

Download NCurses mingw zip file
https://invisible-island.net/datafiles/release/mingw64.zip
Extract bin, include and lib to c:\w64devkit 

Open CMD
cd c:\w64devkit\src
git clone https://github.com/nakedmcse/TextInvaders

Download SQLite3 Amalgamation zip file
https://sqlite.org/download.html
Extract sqlite3.c and sqlite3.h to src/TextInvaders

cd ..
w64devkit.exe
cd /w64devkit/src/TextInvaders
make windows
textinvaders.exe
```