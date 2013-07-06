all: main.c dungeon.c
	gcc -Wall -o "generator" main.c dungeon.c

test: test.c dungeon.c
	gcc -Wall -o "test" test.c dungeon.c
