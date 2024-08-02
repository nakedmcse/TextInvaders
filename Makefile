all: linux

linux: textinvaders.c audio.c hiscores.c
	gcc -O3 -o textinvaders textinvaders.c audio.c hiscores.c input.c -lncurses -lSDL2 -lsqlite3

windows: textinvaders.c audio.c hiscores.c sqlite3.c
	gcc -O3 -o textinvaders.exe textinvaders.c sqlite3.c audio.c hiscores.c input.c -IC:/w64devkit/include -lncursesw -lSDL2

clean:
	rm -f textinvaders
	rm -f invaders.db
