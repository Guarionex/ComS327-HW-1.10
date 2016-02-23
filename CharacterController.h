#ifndef CHARACTER_CONTROLLER_H
#define CHARACTER_CONTROLLER_H

#include "dungeonObjects.h"
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>

typedef enum character_type_enum
{
	PLAYER,
	MONSTER
} character_type_t;

typedef struct player
{
	char *name;
} player_t;

typedef struct monster
{
	uint8_t abilities;
	bool lost;
	pos_t memory;
} monster_t;

typedef union character_parent
{
	player_t player;
	monster_t monster;
} character_parent_t;

typedef struct character_tag
{
	int32_t speed;
	int32_t timer;
	int id;
	bool alive;
	pos_t pos;
	Dungeon_Space_Struct cell;
	character_type_t character_type;
	character_parent_t character_parent;
} character_t;

extern player_t pc;
extern int *character_map;
extern character_t *character_list;
extern int num_characters;
extern const character_t NULL_CHARACTER;

character_t Place_Player(Dungeon_Space_Struct **dungeon, int *seed);
character_t create_monster(Dungeon_Space_Struct **dungeon, int *seed);
character_parent_t character_parent_create(character_type_t character_type, va_list ap);
character_t character_tag_create(int32_t speed, int32_t timer, int id, bool alive, pos_t pos, Dungeon_Space_Struct cell, character_type_t character_type, ...);
void create_character_list();
void add_character(character_t new_character);
character_t delete_character(int id);
character_t get_character_by_id(int id);
int get_character_index_by_id(int id);
int check_character_map(int x, int y);
bool move_character(int character_id, int *seed, Dungeon_Space_Struct **dungeon);
bool move_player(character_t *player_to_move, int to, Dungeon_Space_Struct **dungeon);
int32_t compare_character(const void *key, const void *with);
void update_telepath(void);
void line_of_sight(Dungeon_Space_Struct **dungeon);
bool line_of_sight_helper(pos_t monster_pos, Dungeon_Space_Struct **dungeon);
bool move_monster(character_t *player_to_move, Dungeon_Space_Struct **dungeon);
void set_distance(char *distance);
void set_distance_tunneler(char *distance_tunneller);
int distance_converter(char symbol);




#endif