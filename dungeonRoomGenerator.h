#ifndef DUNGEON_ROOM_GENERATOR_H
#define DUNGEON_ROOM_GENERATOR_H

#include "dungeonObjects.h"
#include <time.h>

//public Dungeon_Space_Room *Room_Collection;

Dungeon_Space_Room generateRoom(int *seed);//lol seed
Dungeon_Space_Room *generateMultipleRooms(int *seed);


#endif