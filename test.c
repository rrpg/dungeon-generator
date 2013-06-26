#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_DUNGEON 1

#include "dungeon.h"

int test_generate_dungeon();
int test_neighbours();
int test_get_opposite_direction_bit();

s_dungeon _generate();
s_dungeon _pseudo_generate();
int _check_integrity(s_dungeon dungeon);

int main()
{
	int ret = 0;
	// generate_dungeon
	ret |= test_generate_dungeon();
	// room_has_door
	// get_neighbour_room_index
	ret |= test_neighbours();
	// get_opposite_direction_bit
	ret |= test_get_opposite_direction_bit();

	return ret;
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

int _check_integrity(s_dungeon dungeon)
{
	int size = dungeon.width * dungeon.height;
	int r, d, ret;
	int neighbour;

	int rooms = BIT_DOOR_NORTH | BIT_DOOR_EAST | BIT_DOOR_SOUTH | BIT_DOOR_WEST;
	ret = 0;
	for (r = 0; r < size ; r++) {
		for (d = 1; d <= rooms; d <<= 1) {
			if ((d & rooms) == 0) {
				continue;
			}

			if ((dungeon.grid[r] & d) == d) {
				neighbour = get_neighbour_room_index(&dungeon, r, d);
				if (neighbour == -1) {
					ret = 1;
					printf("KO: Room %d leads to nothing (no door in direction %d)\n", r, d);
				}
				else if (!room_has_door(&dungeon, neighbour, get_opposite_direction_bit(d))) {
					ret = 1;
					printf("KO: There is no door in the neighbour room (%d) leading to room %d\n", neighbour, r);
				}
				else {
					printf("OK: Room doors\n");
				}
			}
		}
	}

	return ret;
}

int test_generate_dungeon()
{
	printf("\ntest_generate_dungeon\n");
	printf("---------------------\n");

	s_dungeon dungeon;
	int width, height, ret;

	width = height = 3;
	dungeon = _generate(width, height);

	printf("%s: Entrance index is a valid cell (%d)\n", 0 <= dungeon.entrance && dungeon.entrance < width * height ? "Ok" : "Ko", dungeon.entrance);

	ret = _check_integrity(dungeon);
	free(dungeon.grid);

	return ret;
}

int test_neighbours()
{
	printf("\nTest integrity with predefined dungeon\n");
	printf("-----------------------\n");

	s_dungeon dungeon;
	int ret;

	dungeon = _pseudo_generate();

	int i, j, n;
	int result[9][4] = {
		{-1, 1, 3, -1},
		{-1, 2, 4, 0},
		{-1, -1, 5, 1},
		{0, 4, 6, -1},
		{1, 5, 7, 3},
		{2, -1, 8, 4},
		{3, 7, -1, -1},
		{4, 8, -1, 6},
		{5, -1, -1, 7},
	};
	int directions[4] = {
		BIT_DOOR_NORTH, BIT_DOOR_EAST, BIT_DOOR_SOUTH, BIT_DOOR_WEST
	};
	for (i = 0; i < dungeon.width * dungeon.height; i++) {
		for (j = 0; j < 4; j++) {
			n = get_neighbour_room_index(&dungeon, i, directions[j]);
			if (n != result[i][j]) {
				printf("KO Neighbour %d %d\n", i, j);
			}
			else {
				printf("OK Neighbour\n");
			}
		}
	}

	ret = _check_integrity(dungeon);
	free(dungeon.grid);

	return ret;
}

int test_get_opposite_direction_bit()
{
	int ret = 0;
	char* res;

	printf("\ntest_get_opposite_direction_bit\n");
	printf("-------------------------------\n");
	printf("%s: Test North\n", res = (get_opposite_direction_bit(BIT_DOOR_NORTH) == BIT_DOOR_SOUTH ? "Ok" : "Ko"));
	ret |= strcmp(res, "Ko") == 0;
	printf("%s: Test South\n", res = (get_opposite_direction_bit(BIT_DOOR_SOUTH) == BIT_DOOR_NORTH ? "Ok" : "Ko"));
	ret |= strcmp(res, "Ko") == 0;
	printf("%s: Test East\n", res = (get_opposite_direction_bit(BIT_DOOR_EAST) == BIT_DOOR_WEST ? "Ok" : "Ko"));
	ret |= strcmp(res, "Ko") == 0;
	printf("%s: Test West\n", res = (get_opposite_direction_bit(BIT_DOOR_WEST) == BIT_DOOR_EAST ? "Ok" : "Ko"));
	ret |= strcmp(res, "Ko") == 0;
	printf("%s: Test Unknown\n", res = (get_opposite_direction_bit(12) == -1 ? "Ok" : "Ko"));
	ret |= strcmp(res, "Ko") == 0;

	return ret;
}
