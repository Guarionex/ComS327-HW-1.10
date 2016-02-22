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

extern Dungeon_Space_Struct **current_dungeon;
extern character_t player_character;
extern char *distance_map;

void Set_Dungeon(Dungeon_Space_Struct **dungeon);
void Set_Player(character_t player);
char *Generate_Distance_Dungeon(bool tunneler);
void Draw_Dungeon(void);
void Draw_Distance_Dungeon(char *char_map);
void Destroy_All(void);
void turn(int *seed);
#endif