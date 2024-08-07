all: linux

linux: textinvaders.c audio.c hiscores.c input.c physics.c render.c
	gcc -O3 -o textinvaders textinvaders.c audio.c hiscores.c input.c physics.c render.c -lncurses -lSDL2 -lSDL2_mixer -lsqlite3

windows: textinvaders.c audio.c hiscores.c input.c physics.c render.c sqlite3.c
	gcc -O3 -o textinvaders.exe textinvaders.c sqlite3.c audio.c hiscores.c input.c render.c -IC:/w64devkit/include -lncursesw -lSDL2 -lSDL2_mixer

clean:
	rm -f textinvaders
	rm -f invaders.db
