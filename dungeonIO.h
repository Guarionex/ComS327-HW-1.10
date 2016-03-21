#ifndef DUNGEON_IO_H
#define DUNGEON_IO_H

#include "dungeonObjects.h"

typedef enum 
{
	SEED,
	SAVE, 
	LOAD,
	NUMMON
} Flags;

boolean Contains_Flag(Flags *flag, int size, Flags contains);
boolean Contains_Room(Dungeon_Space_Room *rooms, int size, Dungeon_Space_Room room);

Dungeon_Space_Struct **Load_Dungeon(char *file, int *num_rooms);
int Save_Dungeon(Dungeon_Space_Struct **dungeon_map_save, char *file, int num_rooms);



#endif