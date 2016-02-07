#ifndef CHARACTER_CONTROLLER_H
#define CHARACTER_CONTROLLER_H

typedef struct player
{
	Dungeon_Space_Struct cell;
	int x;
	int y;
} player_t;

extern player_t pc;

int Place_Player(Dungeon_Space_Struct **dungeon, int seed);

#endif