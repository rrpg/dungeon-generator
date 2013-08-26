#ifndef DUNGEON_INCLUDED
#include "dungeon.h"
#endif

#define isUsedRoom(room) ((room & BIT_USED_ROOM) == BIT_USED_ROOM)
#define isEntrance(room) ((room & BIT_ENTRANCE) == BIT_ENTRANCE)
#define hasNorthDoor(room) ((room & BIT_DOOR_NORTH) == BIT_DOOR_NORTH)
#define hasSouthDoor(room) ((room & BIT_DOOR_SOUTH) == BIT_DOOR_SOUTH)
#define hasEastDoor(room) ((room & BIT_DOOR_EAST) == BIT_DOOR_EAST)
#define hasWestDoor(room) ((room & BIT_DOOR_WEST) == BIT_DOOR_WEST)
