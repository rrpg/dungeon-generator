#include <stdint.h>

#define BIT_ENTRANCE    0x01
#define BIT_DOOR_NORTH  0x02
#define BIT_DOOR_EAST   0x04
#define BIT_DOOR_SOUTH  0x08
#define BIT_DOOR_WEST   0x10
#define BIT_STAIR_BELOW 0x20
#define BIT_STAIR_UP    0x40

// Grid cell: int:
// bit 0: 1 if there is a door leading to the outside, 0 else
// bits 1 to 4: 1 if there is a door leading to the next cell, 0 else
//      bit 1: north
//      bit 2: east
//      bit 3: south
//      bit 4: west
// bits 5: 1 if there is a stair leading to the floor below, 0 else
// bits 6: 1 if there is a stair leading to the floor below, 0 else
typedef struct {
    uint8_t* grid;
    int width;
    int height;
} s_dungeon;

s_dungeon generate_dungeon(s_dungeon d);
void display_dungeon(s_dungeon d);
