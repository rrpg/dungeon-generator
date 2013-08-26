#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "dungeon.h"

#define DUNGEON_WIDTH 10
#define DUNGEON_HEIGHT 10

int main(int argc, char* argv[])
{
	s_dungeon d;
	int c;
	int visual_display = 0;

	d.width = DUNGEON_WIDTH;
	d.height = DUNGEON_HEIGHT;

	while ((c = getopt (argc, argv, "w:h:v")) != -1) {
		switch (c) {
			case 'w':
				d.width = atoi(optarg);
				break;
			case 'h':
				d.height = atoi(optarg);
				break;
			case 'v':
				visual_display = VISUAL_DISPLAY_MODE;
				break;
			default:
				abort();
		}
	}


	d.grid = malloc(d.width * d.height);

	generate_dungeon(&d);
	display_dungeon(&d, visual_display);

	free(d.grid);

	return 0;
}
