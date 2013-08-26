all: main.c dungeon.c
	gcc -Wall -o "generator" main.c dungeon.c

analyser: analyser.c
	gcc -Wall -o "analyser" analyser.c

test: test.c dungeon.c
	gcc -Wall -o "test" test.c dungeon.c
