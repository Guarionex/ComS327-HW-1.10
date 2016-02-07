#import "CharacterController.h"

player_t pc;

player_t Place_Player(Dungeon_Space_Struct **dungeon, int seed)
{
	pos_t *open_pos = malloc(sizeof(pos_t));
	open_pos[0] = NULL;
	
	int x, y, open_count = 0;
	for(x = 0; x < 80; x++)
	{
		for(y = 0; y < 21; y++)
		{
			switch(dungeon[x][y].space_type)
			{
				case ROCK:
				break;
				
				case ROOM:
					pos_t new_pos;
					new_pos.x = x;
					new_pos.y = y;
					open_count++;
					open_pos = realloc(open_pos, sizeof(pos_t) + (sizeof(pos_t) * open_count));
					open_pos[open_count-1] = new_pos;
					open_pos[open_count] = NULL;
				break;
				
				case CORRIDOR:
					pos_t new_pos;
					new_pos.x = x;
					new_pos.y = y;
					open_count++;
					open_pos = realloc(open_pos, sizeof(pos_t) + (sizeof(pos_t) * open_count));
					open_pos[open_count-1] = new_pos;
					open_pos[open_count] = NULL;
				break;
			}
		}
	}
	
	srand(seed);
	pc.pos = open_pos[rand()%open_count];
	pc.cell = dungeon[pc.pos.x][pc.pos.y];
	
	return pc;
}