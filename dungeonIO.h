#ifndef DUNGEON_IO_H
#define DUNGEON_IO_H

#include "dungeonObjects.h"

typedef enum 
{
	SEED,
	SAVE, 
	LOAD
} Flags;

bool Contains_Flag(Flags *flag, int size, Flags contains);

Dungeon_Space_Struct **Load_Dungeon(char *file);



#endif