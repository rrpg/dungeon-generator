BIT_USED_ROOM   = 0x01
BIT_ENTRANCE    = 0x02
BIT_DOOR_NORTH  = 0x04
BIT_DOOR_EAST   = 0x08
BIT_DOOR_SOUTH  = 0x10
BIT_DOOR_WEST   = 0x20
BIT_STAIR_BELOW = 0x40
BIT_STAIR_UP    = 0x80

def isUsedRoom(room):
	return (room & BIT_USED_ROOM) == BIT_USED_ROOM

def isEntrance(room):
	return (room & BIT_ENTRANCE) == BIT_ENTRANCE

def hasNorthDoor(room):
	return (room & BIT_DOOR_NORTH) == BIT_DOOR_NORTH

def hasSouthDoor(room):
	return (room & BIT_DOOR_SOUTH) == BIT_DOOR_SOUTH

def hasEastDoor(room):
	return (room & BIT_DOOR_EAST) == BIT_DOOR_EAST

def hasWestDoor(room):
	return (room & BIT_DOOR_WEST) == BIT_DOOR_WEST

def getDirections(room):
	return int(room) & (BIT_DOOR_NORTH | BIT_DOOR_EAST | BIT_DOOR_SOUTH | BIT_DOOR_WEST)
