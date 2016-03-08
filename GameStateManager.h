#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include "dungeonObjects.h"
#include "CharacterController.h"
#include "Graph.h"
#include "Dijkstra.h"
#include <stdio.h>
#include <stdint.h>
#include "binheap.h"
#include <unistd.h>
#include <ncurses.h>
#include <string.h>
#include "dungeonRoomGenerator.h"

typedef enum command
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT,
	REST,
	MONSTER_LIST,
	ESCAPE,
	SCROLL_UP,
	SCROLL_DOWN,
	DOWN_STAIRS,
	UP_STAIRS,
	SAVE_QUIT
} command_t;

extern Dungeon_Space_Struct **current_dungeon;
extern character_t player_character;
extern char *distance_map;
extern char *distance_dungeon;
extern char *distance_dungeon_tunneler;
extern int game_state;
extern int stair_player;

void Set_Dungeon(Dungeon_Space_Struct **dungeon);
void Set_Player(character_t player);
void Set_Stairs(stair_t stairs);
void Set_Debug_Info(int seed, int num_rooms);
void populate_monsters(int num_mon, int *seed);
char *Generate_Distance_Dungeon(bool tunneler);
void Draw_Dungeon(int use_curses);
void Draw_Monster_List(void);
void Draw_Distance_Dungeon(char *char_map);
void Destroy_All(void);
int turn(int *seed, int num_mon);
int input_handler(int key);
pos_t get_direction(command_t key);
void define_new_keys(void);
#endif