all: main.c dungeon.c
	gcc -Wall -o "main" main.c dungeon.c
