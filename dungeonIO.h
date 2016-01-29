#ifndef DUNGEON_IO_H
#define DUNGEON_IO_H

#include "dungeonObjects.h"

typedef enum 
{
	SEED,
	SAVE, 
	LOAD
} Flags;

extern Flags *flags;

bool Contains_Flag(Flags *flag, int size, Flags contains);



#endif