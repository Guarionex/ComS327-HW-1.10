#include "CharacterController.h"

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
	
	if(*seed <= 0)
	{
		seed_local = time(NULL);
		*seed = seed_local;
	}
	else if(*seed > 0)
	{
		seed_local = *seed;
	}
	srand(seed_local);
	pc.pos = open_pos[rand()%open_count];
	pc.cell = dungeon[pc.pos.x][pc.pos.y];
	free(open_pos);
	return pc;
}

character_parent_t character_parent_create(character_type_t character_type, va_list ap)
{
  character_parent_t character_parent;

  switch(character_type)
    {
    case PLAYER:
      character_parent.player = va_arg(ap, player_t);
      break;
    case MONSTER:
      character_parent.monster = va_arg(ap, character_parent.player_t);
      break;
    }

  return character_parent;
}

character_t character_tag_create(int speed, int timer, character_type_t character_type, ...)
{
  va_list ap;
  va_start(ap, character_type);
  
  character_t character_tag;
  character_tag.speed = speed;
  character_tag.timer = timer;
  character_tag.character_type = character_type;
  character_tag.character_parent_t = character_parent_create(character_type, ap);
  
  va_end(ap);
  
  return dungeon_space;
}