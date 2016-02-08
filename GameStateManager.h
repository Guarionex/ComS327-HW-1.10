#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include "dungeonObjects.h"
#include "CharacterController.h"
#include "Graph.h"
#include "Dijkstra.h"
#include <stdio.h>

extern Dungeon_Space_Struct **current_dungeon;
extern player_t pc;
extern char **distance_map;

void Set_Dungeon(Dungeon_Space_Struct **dungeon);
void Set_Player(player_t player);
char **Generate_Distance_Dungeon(void);
void Draw_Dungeon(void);
void Draw_Distance_Dungeon(char **char_map);

#endif