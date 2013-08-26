#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dungeon.h"

int main(int argc, char* argv[])
{
	if (argc != 3) {
		fputs("A room value and an option are needed to be analysed\n", stderr);
		return 1;
	}

	char* endptr;
	int value = strtol(argv[1], &endptr, 10);

	if (*endptr != '\0') {
		fputs("The given value is not a valid integer\n", stderr);
		return 1;
	}

	if (strcmp(argv[2], "used") == 0) {
		printf("%d", value != 0);
	}
	else if (strcmp(argv[2], "entrance") == 0) {
		printf("%d", IS_ENTRANCE(value));
	}
	else if (strcmp(argv[2], "north") == 0) {
		printf("%d", HAS_NORTH_DOOR(value));
	}
	else if (strcmp(argv[2], "west") == 0) {
		printf("%d", HAS_WEST_DOOR(value));
	}
	else if (strcmp(argv[2], "south") == 0) {
		printf("%d", HAS_SOUTH_DOOR(value));
	}
	else if (strcmp(argv[2], "east") == 0) {
		printf("%d", HAS_EAST_DOOR(value));
	}
	else {
		fputs("The given option is not valid\n", stderr);
		return 1;
	}

	return 0;
}
