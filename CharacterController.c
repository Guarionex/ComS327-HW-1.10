#include "CharacterController.h"

player_t pc;
int *character_map;
character_t *character_list;
const character_t NULL_CHARACTER = {.id = -1 };
num_characters;

character_t Place_Player(Dungeon_Space_Struct **dungeon, int *seed)
{
	pos_t *open_pos = malloc(sizeof(pos_t));
	open_pos[0] = NULL_POS;
	character_t player;
	
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
	//pc.pos = open_pos[rand()%open_count];
	pos_t new_pos = open_pos[rand()%open_count];
	//pc.cell = dungeon[pc.pos.x][pc.pos.y];
	pc.name = "Edwin";
	player = character_tag_create(10, 10, new_pos, dungeon[new_pos.x][new_pos.y], PLAYER, pc);
	create_character_list();
	add_character(player);
	free(open_pos);
	return player;
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
      character_parent.monster = va_arg(ap, monster_t);
      break;
    }

  return character_parent;
}

character_t character_tag_create(int speed, int timer, pos_t pos, Dungeon_Space_Struct cell, character_type_t character_type, ...)
{
  va_list ap;
  va_start(ap, character_type);
  
  character_t character_tag;
  character_tag.speed = speed;
  character_tag.timer = timer;
  character_tag.pos = pos;
  character_tag.cell = cell;
  character_tag.character_type = character_type;
  character_tag.character_parent_t = character_parent_create(character_type, ap);
  
  va_end(ap);
  
  return character_tag;
}

void create_character_list()
{
	character_list = malloc(sizeof(character_t));
	character_list[0] = NULL_CHARACTER;
	num_characters = 0;
}

void add_character(character_t new_character)
{
	num_characters++;
	character_list = realloc(character_list, sizeof(character_t) + (sizeof(character_t) * num_characters));
	character_list[num_characters - 1] = new_character;
	character_list[num_characters] = NULL_CHARACTER;
}