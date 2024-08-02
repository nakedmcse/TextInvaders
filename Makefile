all: linux

linux: textinvaders.c
	gcc -O3 -o textinvaders textinvaders.c -lncurses -lSDL2 -lsqlite3

windows: textinvaders.c sqlite3.c
	gcc -O3 -o textinvaders.exe textinvaders.c sqlite3.c -IC:/w64devkit/include -lncursesw -lSDL2

clean:
	rm -f textinvaders
	rm -f invaders.db
