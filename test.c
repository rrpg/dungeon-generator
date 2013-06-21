#include <stdio.h>
#include <stdlib.h>

#define TEST_DUNGEON 1

#include "dungeon.h"

void test_generate_dungeon();
void test_display_dungeon();
void test_neighbours();
void test_get_opposite_direction_bit();

s_dungeon _generate();
s_dungeon _pseudo_generate();
void _check_integrity(s_dungeon dungeon);

int main()
{
	// generate_dungeon
	test_generate_dungeon();
	// room_has_door
	// get_neighbour_room_index
	test_neighbours();
	// get_opposite_direction_bit
	test_get_opposite_direction_bit();

	return 1;
}

s_dungeon _generate(int width, int height)
{
	s_dungeon d;

	d.width = width;
	d.height = height;
	d.grid = malloc(d.width * d.height);
	generate_dungeon(&d);

	return d;
}

/**
 * Manually define a dungeon
 */
s_dungeon _pseudo_generate()
{
	s_dungeon d;

	d.width = 3;
	d.height = 3;
	d.grid = malloc(d.width * d.height);

	d.grid[0] = BIT_USED_ROOM | BIT_DOOR_EAST | BIT_DOOR_SOUTH;
	d.grid[1] = BIT_USED_ROOM | BIT_DOOR_WEST | BIT_DOOR_SOUTH;
	//d.grid[2]; Unused room
	d.grid[3] = BIT_USED_ROOM | BIT_DOOR_NORTH;
	d.grid[4] = BIT_USED_ROOM | BIT_ENTRANCE | BIT_DOOR_NORTH | BIT_DOOR_SOUTH;
	d.grid[5] = BIT_USED_ROOM | BIT_DOOR_SOUTH;
	d.grid[6] = BIT_USED_ROOM | BIT_DOOR_EAST;
	d.grid[7] = BIT_USED_ROOM | BIT_DOOR_EAST | BIT_DOOR_NORTH | BIT_DOOR_WEST;
	d.grid[8] = BIT_USED_ROOM | BIT_DOOR_NORTH | BIT_DOOR_WEST;
	d.grid[9] = BIT_USED_ROOM | BIT_DOOR_SOUTH;

	return d;
}

void _check_integrity(s_dungeon dungeon)
{
	int size = dungeon.width * dungeon.height;
	int r, d;
	int neighbour;
	int rooms = BIT_DOOR_NORTH | BIT_DOOR_EAST | BIT_DOOR_SOUTH | BIT_DOOR_WEST;
	for (r = 0; r < size ; r++) {
		for (d = 1; d <= rooms; d <<= 1) {
			if ((d & rooms) == 0) {
				continue;
			}

			if ((dungeon.grid[r] & d) == d) {
				neighbour = get_neighbour_room_index(&dungeon, r, d);
				if (neighbour == -1) {
					printf("KO: Room %d leads to nothing (no door in direction %d)\n", r, d);
				}
				else if (!room_has_door(&dungeon, neighbour, get_opposite_direction_bit(d))) {
					printf("KO: There is no door in the neighbour room (%d) leading to room %d\n", neighbour, r);
				}
				else {
					printf("OK: Room doors\n");
				}
			}
		}
	}
}

void test_generate_dungeon()
{
	printf("\ntest_generate_dungeon\n");
	printf("---------------------\n");

	s_dungeon dungeon;
	int width, height;

	width = height = 3;
	dungeon = _generate(width, height);

	printf("%s: Entrance index is a valid cell (%d)\n", 0 <= dungeon.entrance && dungeon.entrance < width * height ? "Ok" : "Ko", dungeon.entrance);

	_check_integrity(dungeon);
	free(dungeon.grid);
}

void test_neighbours()
{
	printf("\nTest integrity with predefined dungeon\n");
	printf("-----------------------\n");

	s_dungeon dungeon;

	dungeon = _pseudo_generate();

	_check_integrity(dungeon);
	free(dungeon.grid);
}

void test_get_opposite_direction_bit()
{
	printf("\ntest_get_opposite_direction_bit\n");
	printf("-------------------------------\n");
	printf("%s: Test North\n", get_opposite_direction_bit(BIT_DOOR_NORTH) == BIT_DOOR_SOUTH ? "Ok" : "Ko");
	printf("%s: Test South\n", get_opposite_direction_bit(BIT_DOOR_SOUTH) == BIT_DOOR_NORTH ? "Ok" : "Ko");
	printf("%s: Test East\n", get_opposite_direction_bit(BIT_DOOR_EAST) == BIT_DOOR_WEST ? "Ok" : "Ko");
	printf("%s: Test West\n", get_opposite_direction_bit(BIT_DOOR_WEST) == BIT_DOOR_EAST ? "Ok" : "Ko");
	printf("%s: Test Unknown\n", get_opposite_direction_bit(12) == -1 ? "Ok" : "Ko");
}
