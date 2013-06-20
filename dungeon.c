#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "dungeon.h"

s_dungeon generate_dungeon(s_dungeon d)
{
	//~ uint8_t* dungeon = malloc(width*sizeof(uint8_t) * height*sizeof(uint8_t));
	int size = d.width * d.height;

	int i;
	for (i = 0 ; i < size ; i++) {
		d.grid[i] = 1;
		//~ printf("content: %" PRIu8 "\n", dungeon[i]);
	}

	return d;
}

void display_dungeon(s_dungeon d)
{
	printf("sizeof dungeon: %ld\n", sizeof(&d.grid));
}
