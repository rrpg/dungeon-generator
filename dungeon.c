#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "dungeon.h"

int get_neighbour_room_index(s_dungeon *dungeon, int current_room, int direction);
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

/**
 * Takes a room index and a direction and returns the neighbour room.
 * If no neighbour room exists (eg. current_room is on an edge of the dungeon),
 * -1 is returned.
 */
int get_neighbour_room_index(s_dungeon *dungeon, int current_room, int direction)
{
	int neighbour_room;
	switch (direction) {
		case BIT_DOOR_NORTH:
			neighbour_room = current_room - (*dungeon).width;
			break;
		case BIT_DOOR_EAST:
			neighbour_room = current_room + 1;
			break;
		case BIT_DOOR_SOUTH:
			neighbour_room = current_room + (*dungeon).width;
			break;
		case BIT_DOOR_WEST:
			neighbour_room = current_room - 1;
			break;
	}

	if ((direction == BIT_DOOR_NORTH && neighbour_room >= 0)
		|| (direction == BIT_DOOR_SOUTH && neighbour_room < (*dungeon).width * (*dungeon).height)
		|| (direction == BIT_DOOR_EAST && neighbour_room % (*dungeon).width > 0)
		|| (direction == BIT_DOOR_WEST && neighbour_room < (*dungeon).width - 1)) {
		return neighbour_room;
	}

	return -1;
}

void display_dungeon(s_dungeon d)
{
	printf("sizeof dungeon: %ld\n", sizeof(&d.grid));
}
