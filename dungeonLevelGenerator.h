#ifndef DUNGEON_LEVEL_GENERATOR_H
#define DUNGEON_LEVEL_GENERATOR_H

#include "dungeonObjects.h"
#include "dungeonRoomGenerator.h"

extern Dungeon_Space_Struct **dungeon_map;

void Create_Blank_Map(int *seed);
bool Place_Rooms(Dungeon_Space_Room *rooms);
void Connect_Rooms();
Dungeon_Space_Struct **Generate_Map(int seed);
void Draw_Dungeon();


#endif