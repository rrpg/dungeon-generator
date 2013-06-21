#include <stdio.h>
#include <stdlib.h>
#include "dungeon.h"

#define DUNGEON_WIDTH 10
#define DUNGEON_HEIGHT 10

int main()
{
	s_dungeon d;

	d.width = d.height = DUNGEON_WIDTH;
	d.grid = malloc(d.width * d.height);

	generate_dungeon(&d);
	display_dungeon(&d);

	free(d.grid);

	return 0;
}
