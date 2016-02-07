#include "CharacterController.h"
#include <stdio.h>

player_t pc;

player_t Place_Player(Dungeon_Space_Struct **dungeon, int *seed)
{
	pos_t *open_pos = malloc(sizeof(pos_t));
	open_pos[0] = NULL_POS;
	
	int x, y, open_count = 0;
	for(x = 0; x < 80; x++)
	{
		for(y = 0; y < 21; y++)
		{
			pos_t new_pos;
			switch(dungeon[x][y].space_type)
			{
				case ROCK:
				break;
				
				case ROOM:
					new_pos.x = x;
					new_pos.y = y;
					open_count++;
					open_pos = realloc(open_pos, sizeof(pos_t) + (sizeof(pos_t) * open_count));
					open_pos[open_count-1] = new_pos;
					open_pos[open_count] = NULL_POS;
				break;
				
				case CORRIDOR:
					new_pos.x = x;
					new_pos.y = y;
					open_count++;
					open_pos = realloc(open_pos, sizeof(pos_t) + (sizeof(pos_t) * open_count));
					open_pos[open_count-1] = new_pos;
					open_pos[open_count] = NULL_POS;
				break;
			}
		}
	}
	
	int seed_local;
	
	if(seed <= 0)
	{
		seed_local = time(NULL);
		*seed = seed_local;
		printf("Seed from time\n");
	}
	else if(seed > 0)
	{
		seed_local = *seed;
		printf("Seed from input %d\n", seed_local);
	}
	srand(seed_local);
	pc.pos = open_pos[rand()%open_count];
	pc.cell = dungeon[pc.pos.x][pc.pos.y];
	free(open_pos);
	return pc;
}