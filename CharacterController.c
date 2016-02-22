#include "CharacterController.h"
#include <stdio.h>

player_t pc;
int *character_map;
character_t *character_list;
const character_t NULL_CHARACTER = {.id = -1 };
int num_characters;

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
	player = character_tag_create(10, 0, 0, new_pos, dungeon[new_pos.x][new_pos.y], PLAYER, pc);
	create_character_list();
	add_character(player);
	free(open_pos);
	return player;
}

character_t create_monster(Dungeon_Space_Struct **dungeon, int *seed)
{	
	uint8_t powers = 0x0;
	powers = powers | ((rand()%2 == 0) ? 0x0 : 0x1) | ((rand()%2 == 0) ? 0x0 : 0x2) | ((rand()%2 == 0) ? 0x0 : 0x4) | ((rand()%2 == 0) ? 0x0 : 0x8);
	
	printf("Monster %d is 0x%x\n", num_characters, powers);
	
	pos_t *open_pos = malloc(sizeof(pos_t));
	pos_t mon_pos;
	int open_count = 0;
	if((0x4 & powers) == 0x4)
	{
		mon_pos.x = (rand()%78)+1;
		mon_pos.y = (rand()%19)+1;
	}
	else
	{
		int x, y;
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
		mon_pos = open_pos[rand()%open_count];
	}
	
	monster_t monster = {.abilities = powers};
	character_t mon = character_tag_create((rand()%16)+5, 0, num_characters, mon_pos, dungeon[mon_pos.x][mon_pos.y], MONSTER, monster);
	add_character(mon);
	free(open_pos);
	return mon;
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

character_t character_tag_create(int32_t speed, int32_t timer, int id, pos_t pos, Dungeon_Space_Struct cell, character_type_t character_type, ...)
{
  va_list ap;
  va_start(ap, character_type);
  
  character_t character_tag;
  character_tag.speed = speed;
  character_tag.timer = timer;
  character_tag.id = id;
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
	character_map = malloc(sizeof(int) * 1680);
	int i;
	for(i = 0; i < 1680; i++)
	{
		character_map[i] = -1;
	}
}

void add_character(character_t new_character)
{
	num_characters++;
	character_list = realloc(character_list, sizeof(character_t) + (sizeof(character_t) * num_characters));
	character_list[num_characters - 1] = new_character;
	character_list[num_characters] = NULL_CHARACTER;
	character_map[new_character.pos.y*80+new_character.pos.x] = new_character.id;
}

character_t delete_character(int id)
{
	int i;
	bool deleted = FALSE;
	character_t killed_character = NULL_CHARACTER;
	for(i = 0; i < num_characters; i++)
	{
		if(character_list[i].id == id && deleted == FALSE)
		{
			killed_character = character_list[i];
			character_list[i] = character_list[i+1];
			deleted = TRUE;
		}
		else if(deleted == TRUE) 
		{
			character_list[i] = character_list[i+1];
		}
	}
	
	if(killed_character.id != -1)
	{
		character_map[killed_character.pos.y*80+killed_character.pos.x] = -1;
		num_characters--;
	}
	
	return killed_character;
}

character_t get_character_by_id(int id)
{
	int i;
	for(i = 0; i < num_characters; i++)
	{
		if(character_list[i].id == id)
		{
			return character_list[i];
		}
	}
	
	return NULL_CHARACTER;
}

int get_character_index_by_id(int id)
{
	int i;
	for(i = 0; i < num_characters; i++)
	{
		if(character_list[i].id == id)
		{
			return i;
		}
	}
	
	return -1;
}

int check_character_map(int x, int y)
{
	return character_map[y*80+x];
}

bool move_character(int character_id, int *seed, Dungeon_Space_Struct **dungeon)
{
	int index = get_character_index_by_id(character_id);
	if(index < 0) 
	{ 
		return FALSE;
	}
	
	
	
	switch(character_list[index].character_type)
	{
		case PLAYER:
		return move_player(&character_list[index], rand()%9, dungeon);
		break;
		
		case MONSTER:
		
		break;
	}
	
	return FALSE;
}

bool move_player(character_t *player_to_move, int to, Dungeon_Space_Struct **dungeon)
{
	int a, b;
	switch(to)
	{
		case 0:
		a = -1;
		b = -1;
		break;
		
		case 1:
		a = 0;
		b = -1;
		break;
		
		case 2:
		a = 1;
		b = -1;
		break;
		
		case 3:
		a = -1;
		b = 0;
		break;
		
		case 4:
		a = 0;
		b = 0;
		break;
		
		case 5:
		a = 1;
		b = 0;
		break;
		
		case 6:
		a = -1;
		b = 1;
		break;
		
		case 7:
		a = 0;
		b = 1;
		break;
		
		case 8:
		a = 1;
		b = 1;
		break;
		
		default:
		a = 0;
		b =0;
		break;
	}
	
	switch(dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b].space_type)
	{
		case ROCK:
		if(dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b].space_union.rock.density == 255)
		{
			return TRUE;
		}
		else
		{
			character_map[player_to_move->pos.y*80+player_to_move->pos.x] = -1;
			player_to_move->pos.x = player_to_move->pos.x+a;
			player_to_move->pos.y = player_to_move->pos.y+b;
			character_map[player_to_move->pos.y*80+player_to_move->pos.x] = 0;
			dungeon[player_to_move->pos.x][player_to_move->pos.y] = Dungeon_Space_Struct_create(CORRIDOR, Dungeon_Space_Corridor_create());
			player_to_move->cell = dungeon[player_to_move->pos.x][player_to_move->pos.y];
			return TRUE;
		}
		break;
		
		case ROOM:
		character_map[player_to_move->pos.y*80+player_to_move->pos.x] = -1;
		player_to_move->pos.x = player_to_move->pos.x+a;
		player_to_move->pos.y = player_to_move->pos.y+b;
		character_map[player_to_move->pos.y*80+player_to_move->pos.x] = 0;
		player_to_move->cell = dungeon[player_to_move->pos.x][player_to_move->pos.y];
		return TRUE;
		break;
		
		case CORRIDOR:
		character_map[player_to_move->pos.y*80+player_to_move->pos.x] = -1;
		player_to_move->pos.x = player_to_move->pos.x+a;
		player_to_move->pos.y = player_to_move->pos.y+b;
		character_map[player_to_move->pos.y*80+player_to_move->pos.x] = 0;
		player_to_move->cell = dungeon[player_to_move->pos.x][player_to_move->pos.y];
		return TRUE;
		break;
	}
	
	return FALSE;
}

int32_t compare_character(const void *key, const void *with)
{
	character_t from = *((character_t *) key);
	character_t to = *((character_t *) with);
	
	int32_t turn_difference = from.timer - to.timer;
	return turn_difference;
}