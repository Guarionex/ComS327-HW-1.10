#ifndef CHARACTER_CONTROLLER_H
#define CHARACTER_CONTROLLER_H

#include "dungeonObjects.h"
#include <time.h>
#include <stdlib.h>

typedef struct player
{
	Dungeon_Space_Struct cell;
	pos_t pos;
} player_t;

extern player_t pc;

player_t Place_Player(Dungeon_Space_Struct **dungeon, int *seed);

#endif