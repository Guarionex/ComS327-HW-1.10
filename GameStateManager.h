#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include "dungeonObjects.h"
#include "CharacterController.h"
#include <stdio.h>

extern Dungeon_Space_Struct **current_dungeon;
extern player_t pc;

void Set_Dungeon(Dungeon_Space_Struct **dungeon);
void Set_Player(player_t player);
void Draw_Dungeon(void);

#endif