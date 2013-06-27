#include <stdio.h>
#include <stdlib.h>
#include "dungeon.h"

#define DUNGEON_WIDTH 10
#define DUNGEON_HEIGHT 10

int main(int argc, char* argv[])
{
	s_dungeon d;

	d.width = DUNGEON_WIDTH;
	d.height = DUNGEON_HEIGHT;
	if (argc == 2) {
		d.width = atoi(argv[1]);
	}
	else if (argc == 3) {
		d.height = atoi(argv[2]);
	}

	d.grid = malloc(d.width * d.height);

	generate_dungeon(&d);
	display_dungeon(&d);

	free(d.grid);

	return 0;
}
