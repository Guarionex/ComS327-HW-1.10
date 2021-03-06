#ifndef CHARACTER_CONTROLLER_H
#define CHARACTER_CONTROLLER_H


#include <time.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <vector>
#include "dungeonObjects.h"
#include "dice.h"
#include <string>
#include "item.h"

using namespace std;

typedef enum character_type_enum
{
	PLAYER,
	MONSTER
} character_type_t;

# ifdef __cplusplus

class characterClass
{
	public:
	int32_t speed;
	int32_t timer;
	int id;
	boolean alive;
	pos_t pos;
	Dungeon_Space_Struct cell;
	character_type_t character_type;
	
	string name;
	string description;
	char symbol;
	short color;
	Dice speedDice;
	Dice hp;
	Dice damage;
	
	int healthPoints;
	int magicPoints;
	
	characterClass();
	~characterClass();
};

class playerClass : public characterClass 
{
	const char *pname;
	
	public:
	itemClass equipment[12];
	itemClass inventory[10];
	itemClass spells[16];
	
	playerClass();
	~playerClass();
	playerClass(const char *player_name);
	inline const char *get_name() const
	{
		return pname;
	}
	
};

class monsterClass : public characterClass
{
	private:
	uint8_t abilities;
	bool lost;
	int memoryX;
	int memoryY;
	
	public:
	/*string name;
	string description;
	char symbol;
	short color;
	Dice speed;
	Dice hp;
	Dice damage;*/
	
	monsterClass();
	~monsterClass();
	monsterClass(uint8_t powers, bool is_mon_lost, int memX, int memY);
	inline uint8_t get_abilities() const
	{
		return abilities;
	}
	inline void set_abilities(uint8_t powers)
	{
		abilities = powers;
	}
	inline bool get_lost() const
	{
		return lost;
	}
	inline void set_lost(bool is_mon_lost)
	{
		lost = is_mon_lost;
	}
	inline int get_memoryX() const
	{
		return memoryX;
	}
	inline void set_memoryX(int new_x)
	{
		memoryX = new_x;
	}
	inline int get_memoryY() const
	{
		return memoryY;
	}
	inline void set_memoryY(int new_y)
	{
		memoryY = new_y;
	}
	
};

extern "C" {
# endif

//#include "dungeonObjects.h"



typedef struct player
{
	//const char *name;
} player_t;

typedef struct monster
{
	/*uint8_t abilities;
	boolean lost;
	pos_t memory;*/
} monster_t;

typedef union character_parent
{
	player_t *player;
	monster_t *monster;
} character_parent_t;

typedef struct character_tag
{
	/*int32_t speed;
	int32_t timer;
	int id;
	boolean alive;
	pos_t pos;
	Dungeon_Space_Struct cell;
	character_type_t character_type;
	character_parent_t character_parent;*/
} character_t;

extern player_t *pc;
extern int *character_map;
extern character_t **character_list;
extern int num_characters;
extern character_t NULL_CHARACTER;
extern int dead_monsters;

player_t *new_Player(void);
void destroy_Player(player_t *player_to_destroy);
player_t *new_Player_param(const char *player_name);
itemClass get_Player_equipment(player_t *playerC, int slot);
void set_Player_equipment(player_t *playerC, itemClass newEquipment, int slot);
itemClass get_Player_item(player_t *playerC, int slot);
void set_Player_item(player_t *playerC, itemClass newItem, int slot);
itemClass get_Player_spell(player_t *playerC, int slot);
void set_Player_spell(player_t *playerC, itemClass newSpell, int slot);


monster_t *new_Monster();
void destroy_Monster(monster_t *monster_to_destroy);
monster_t *new_Monster_param(uint8_t abilities, boolean lost, pos_t memory);
uint8_t get_Monster_abilities(monster_t *mon);
boolean get_Monster_lost(monster_t *mon);
void set_Monster_lost(monster_t *mon, boolean is_mon_lost);
pos_t get_Monster_memory(monster_t *mon);
void set_Monster_memory(monster_t *mon, pos_t new_memory);

character_t *new_Character();
void destroy_Character(character_t * toon);
int32_t get_Character_speed(character_t * toon);
void set_Character_speed(character_t * toon, int new_speed);
int32_t get_Character_timer(character_t * toon);
void set_Character_timer(character_t * toon, int32_t new_time);
int get_Character_id(character_t * toon);
boolean get_Character_alive(character_t * toon);
void set_Character_alive(character_t * toon, boolean status);
pos_t get_Character_pos(character_t * toon);
void set_Character_pos(character_t * toon, pos_t new_pos);
Dungeon_Space_Struct get_Character_cell(character_t * toon);
void set_Character_cell(character_t * toon, Dungeon_Space_Struct new_cell);
character_type_t get_Character_character_type(character_t * toon);
string get_Character_name(character_t *toon);
string get_Character_description(character_t *toon);
char get_Character_symbol(character_t *toon);
short get_Character_color(character_t *toon);
int get_Character_healthPoints(character_t *toon);
void set_Character_healthPoints(character_t *toon, int newHP);
int get_Character_magicPoints(character_t *toon);
void set_Character_magicPoints(character_t *toon, int newMP);
int get_Character_damage(character_t *toon);
void set_Character_parsed_data(character_t *toon, string pName, string pDesc, char pSymb, short pColor, Dice pDamage);
void set_Character_all(character_t * toon, int32_t set_speed, int32_t new_time, int mon_id, boolean status, pos_t new_pos, Dungeon_Space_Struct new_cell, character_type_t toon_type);
void set_Character_symbol(character_t *toon, char nSymbol);
void set_Character_color(character_t *toon, short newColor);

character_t *Place_Player(Dungeon_Space_Struct **dungeon, int *seed);
character_t *create_monster(Dungeon_Space_Struct **dungeon, int *seed, vector<monsterClass> monsterList);
character_parent_t character_parent_create(character_type_t character_type, va_list ap);
character_t character_tag_create(int32_t speed, int32_t timer, int id, boolean alive, pos_t pos, Dungeon_Space_Struct cell, character_type_t character_type, ...);
void create_character_list();
void add_character(character_t *new_character);
character_t delete_character(int id);
character_t *get_character_by_id(int id);
int get_character_index_by_id(int id);
int check_character_map(int x, int y);
string move_character(int character_id, int *seed, Dungeon_Space_Struct **dungeon, ...);
string move_player(character_t *player_to_move, pos_t to, Dungeon_Space_Struct **dungeon);
int32_t compare_character(const void *key, const void *with);
void update_telepath(void);
void line_of_sight(Dungeon_Space_Struct **dungeon);
boolean line_of_sight_helper(pos_t monster_pos, Dungeon_Space_Struct **dungeon);
string move_monster(character_t *player_to_move, Dungeon_Space_Struct **dungeon);
void set_distance(char *distance);
void set_distance_tunneler(char *distance_tunneller);
int distance_converter(char symbol);
void Destroy_Characters(void);

#ifdef __cplusplus
}

monster_t *new_Monster_existing(monsterClass *parsedMon);


#endif


#endif