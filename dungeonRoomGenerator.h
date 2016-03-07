#ifndef DUNGEON_ROOM_GENERATOR_H
#define DUNGEON_ROOM_GENERATOR_H

#include "dungeonObjects.h"
#include <time.h>

//public Dungeon_Space_Room *Room_Collection;

Dungeon_Space_Room generateRoom();//lol seed
Dungeon_Space_Room *generateMultipleRooms(int *seed);
stair_t Place_Stairs(Dungeon_Space_Struct **dungeon, int *seed, stair_direction_t direction);


#endif