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

extern Dungeon_Space_Struct **current_dungeon;
extern character_t player_character;
extern char *distance_map;
extern char *distance_dungeon;
extern char *distance_dungeon_tunneler;

void Set_Dungeon(Dungeon_Space_Struct **dungeon);
void Set_Player(character_t player);
void Set_Debug_Info(int seed, int num_rooms);
void populate_monsters(int num_mon, int *seed);
char *Generate_Distance_Dungeon(bool tunneler);
void Draw_Dungeon(int use_curses);
void Draw_Distance_Dungeon(char *char_map);
void Destroy_All(void);
void turn(int *seed);
#endif