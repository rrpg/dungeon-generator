#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "dungeon.h"

int get_opposite_direction_bit(int direction);

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

/**
 * Takes a cardinal direction in argument and returns its oposite.
 */
int get_opposite_direction_bit(int direction)
{
	int opposite_direction;
	switch (direction) {
		case BIT_DOOR_NORTH:
			opposite_direction = BIT_DOOR_SOUTH;
			break;
		case BIT_DOOR_EAST:
			opposite_direction = BIT_DOOR_WEST;
			break;
		case BIT_DOOR_SOUTH:
			opposite_direction = BIT_DOOR_NORTH;
			break;
		case BIT_DOOR_WEST:
			opposite_direction = BIT_DOOR_EAST;
			break;
	}
	return opposite_direction;
}

void display_dungeon(s_dungeon d)
{
	printf("sizeof dungeon: %ld\n", sizeof(&d.grid));
}
