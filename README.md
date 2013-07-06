# Dungeon Generator

A dungeon generator for rogue-like games written in C.

## Usage

```
# To compile the main executable
Make

# To generate a dungeon
./generator

# To generate a dungeon with a specific width/height (default are 10)
./generator -h 20 -w 15

# To generate a dungeon and display it (the default behaviour will list the
# rooms values)
./generator -v


# To compile and run the test executable
Make test
./test
```

## Explanations

A dungeon is defined by a grid (with a width and a height). Each cell of the
grid is a room.

A room can have up to 4 doors, one per cardinal direction.
A dungeon has one room considered as the entrance.

Each room of the dungeon is an integer (can be listed when generated without
-v option). The integer is a combination of bits of settings. Each bit is
described in section "Room bits details".

Example of generated dungeon with -v option (E is the entrance room):
```
            ###
            # #
    ##### ### #
    #   # #   #
### # # ##### #######
# # #E#     # #     #
# ### # ##### ### # #
#                   #
# ##### ####### ### #
# # # #   # #   #   #
### # # ### ### # ###
    #   #     # #   #
    #####     # #####
              # #
              ###
```

The rooms can be shown this way:
```
   |   |   |   |   |   |###|   |   |
   |   |   |   |   |   |# #|   |   |
   |   |   |   |   |   |# #|   |   |
---------------------------------------
   |   |###|###|   |###|# #|   |   |
   |   |#  |  #|   |#  |  #|   |   |
   |   |# #|# #|   |###|# #|   |   |
---------------------------------------
###|   |# #|# #|###|###|# #|###|###|###
# #|   |#E#|#  |   |  #|# #|#  |   |  #
# #|   |# #|# #|###|###|# #|###|# #|# #
---------------------------------------
# #|###|# #|# #|###|###|# #|###|# #|# #
#  |   |   |   |   |   |   |   |   |  #
# #|###|###|# #|###|###|###|# #|###|# #
---------------------------------------
# #|   |###|# #|###|   |###|# #|###|# #
# #|   |# #|#  |  #|   |#  |  #|#  |  #
###|   |# #|# #|###|   |###|# #|# #|###
---------------------------------------
   |   |# #|# #|   |   |   |# #|# #|###
   |   |#  |  #|   |   |   |# #|#  |  #
   |   |###|###|   |   |   |# #|###|###
---------------------------------------
   |   |   |   |   |   |   |# #|   |
   |   |   |   |   |   |   |# #|   |
   |   |   |   |   |   |   |###|   |
```

A room is a 3x3 square, a space represents a empty space and a # represents a
wall. The central point is always empty (the room itself), the points on the
edge are the walls. The corner points are always walls.
For example, the following room is a room with a door leading to the south and
another to the west:
```
###
  #
# #
```


## Generation

The dungeon to generate has a maximum width and a maximum height (once
generated, it will probably not use all the cells).

To generate the dungeon, 2 lists of width*height elements are needed. One will
be the dungeon grid itself and the other one will be temporary (used only for
the generation).

The generation process is the following:
- a loop is executed on the temporary list while the current index is lower than
the list size and the current element is different than 0 if the index is higher
than 0,
- 	if the current index is 0, the dungeon entrance is defined (index of the
entrance room randomly generated between 0 and the max number of rooms). The
entrance room is set in the rooms list and its index is added in the temporary
list.
- 	then, the current room's doors are defined (to define the neighbour rooms)
and those neighbour rooms are added to the temporary list to be processed later
in the loop.


## Room bits details

A room is a combination of bits stored in an integer. Here is the value of each
bits:
- 0x01: Set to 1 if the cell is an used room,
- 0x02: Set to 1 if the room is the dungeon entrance,
- 0x04: Set to 1 if the room has a door leading to the north
- 0x08: Set to 1 if the room has a door leading to the east
- 0x10: Set to 1 if the room has a door leading to the south
- 0x20: Set to 1 if the room has a door leading to the west
- 0x40: Not used yet, will probably be used to set a stair to the floor below
- 0x80: Not used yet, will probably be used to set a stair to the floor above
