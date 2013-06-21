#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "dungeon.h"

/*
 * "Private" methods
 */
bool room_has_door(s_dungeon *dungeon, int room, int direction);
int get_neighbour_room_index(s_dungeon *dungeon, int current_room, int direction);
int get_opposite_direction_bit(int direction);

/*
 * Implementations
 */

/**
 * Generate a dungeon from an empty dungeon and its size.
 * The number of rooms is defined from the given size
 *
 * For that, an array of rooms is generated.
 * The first item of the array is the first room, the entrance.
 * Then for each room (entrance included), its doors are defined:
 * - there is a door if the neighbour room has a room leading to the current
 * 		room
 * - if the neighbour room has not yet been visited, a room presence is randomly
 * 		defined
 */
s_dungeon generate_dungeon(s_dungeon d)
{
	int i, entrance, neighbours, generated_cells_number;

	// Dungeon cells area number
	int dungeon_area = d.width*d.height;
	// Collection of generated cells, array of dungeon.grid indexes
	int* generated_cells = (int*) calloc(dungeon_area, sizeof(int));
	// Bits for the possible doors in the current cell
	neighbours = BIT_DOOR_NORTH | BIT_DOOR_EAST | BIT_DOOR_SOUTH | BIT_DOOR_WEST;

	srand(time(NULL));

	for (i = 0 ; generated_cells_number < dungeon_area && (i == 0 || generated_cells[i] != 0); i++) {
		// if the cell is the first, let's define the dungeon entrance.
		if (i == 0) {
			entrance = rand() % dungeon_area;
			generated_cells[0] = entrance;
			d.grid[entrance] = BIT_ENTRANCE | BIT_USED_ROOM;
			d.entrance = entrance;
			generated_cells_number = 1;
		}

		// For each cell, generate random doors
		int potential_doors = (rand() % (neighbours + 1)) & neighbours;

		// Check the room's neighbours
		int door;
		for (door = 1; door <= neighbours ; door <<= 1) {
			// The bit match a door bit, ignore the others
			if ((door & neighbours) != door) {
				continue;
			}

			int neighbour_room = get_neighbour_room_index(&d, generated_cells[i], door);
			if (!~neighbour_room) {
				continue;
			}

			// See if there is a visited room with a door here.
			if (room_has_door(&d, neighbour_room, get_opposite_direction_bit(door))) {
				// Add the bit to the current room
				d.grid[generated_cells[i]] |= door;
			}
			// else see if a door has been randomly here
			else if ((door & potential_doors) == door) {
				// Add the room in the list, to process it later
				generated_cells[generated_cells_number++] = neighbour_room;
				d.grid[generated_cells[neighbour_room]] |= BIT_USED_ROOM | door;
			}
		}
	}
	free(generated_cells);

	return d;
}

/**
 * Take a room index, a direction to know if:
 * - the room has already been visited (BIT_USED_ROOM bit set)
 * - the room has a door leading to the given direction
 *
 * Returns false if
 * - there is no possible room (current room on an edge)
 * - or there is no room
 * - or if there is a room but with no door to the current room.
 * Else returns true
 */
bool room_has_door(s_dungeon *dungeon, int room, int direction)
{
	// if the room is used and has a door to the current room
	int needed_bit = BIT_USED_ROOM | direction;
	return ((*dungeon).grid[room] & needed_bit) == needed_bit;
}

/**
 * Takes a cardinal direction in argument and returns its oposite.
 */
int get_opposite_direction_bit(int direction)
{
	int opposite_direction = -1;
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
	int neighbour_room, width, height;

	width = (*dungeon).width;
	height = (*dungeon).height;

	switch (direction) {
		case BIT_DOOR_NORTH:
			neighbour_room = current_room - width;
			break;
		case BIT_DOOR_EAST:
			neighbour_room = current_room + 1;
			break;
		case BIT_DOOR_SOUTH:
			neighbour_room = current_room + width;
			break;
		case BIT_DOOR_WEST:
			neighbour_room = current_room - 1;
			break;
	}

	if ((direction == BIT_DOOR_NORTH && neighbour_room >= 0)
		|| (direction == BIT_DOOR_SOUTH && neighbour_room < width * height)
		|| (direction == BIT_DOOR_EAST && neighbour_room % width > 0)
		|| (direction == BIT_DOOR_WEST && neighbour_room % width < width - 1)) {
		return neighbour_room;
	}

	return -1;
}

void display_dungeon(s_dungeon d)
{
	printf("sizeof dungeon: %ld\n", sizeof(&d.grid));
}
