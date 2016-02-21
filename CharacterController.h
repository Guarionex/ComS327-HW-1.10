#ifndef CHARACTER_CONTROLLER_H
#define CHARACTER_CONTROLLER_H

#include "dungeonObjects.h"
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>

typedef enum character_type_enum
{
	PLAYER,
	MONSTER
} character_type_t;

typedef struct player
{
	Dungeon_Space_Struct cell;
	pos_t pos;
} player_t;

typedef struct monster
{
	pos_t pos;
} monster_t;

typedef union character_parent
{
	player_t player;
	monster_t monster;
} character_parent_t;

typedef struct character_tag
{
	int speed;
	int timer;
	character_type_t character_type;
	character_parent_t character_parent_t;
} character_t;

extern player_t pc;

player_t Place_Player(Dungeon_Space_Struct **dungeon, int *seed);
character_parent_t character_parent_create(character_type_t character_type, va_list ap);
character_t character_tag_create(int speed, int timer, character_type_t character_type, ...);


#endif