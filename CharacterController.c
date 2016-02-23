#include "CharacterController.h"
#include <stdio.h>

player_t pc;
int *character_map;
character_t *character_list;
const character_t NULL_CHARACTER = {.id = -1 };
int num_characters;
char *dis_map;
char *dis_map_tun;

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
	uint8_t powers = 0b0000;
	powers = powers | ((rand()%2 == 0) ? 0x0 : 0x1) | ((rand()%2 == 0) ? 0x0 : 0x2) | ((rand()%2 == 0) ? 0x0 : 0x4) | ((rand()%2 == 0) ? 0x0 : 0x8);
	
	//printf("Monster %d is 0x%x\n", num_characters, powers);
	
	pos_t *open_pos = malloc(sizeof(pos_t));
	pos_t mon_pos;
	int open_count = 0;
	if((0x4 & powers) == 0x4)
	{
		bool pos_found = FALSE;
		int attempts = 0;
		while(pos_found == FALSE && attempts < 10000)
		{
			attempts++;
			int x = (rand()%78)+1;
			int y = (rand()%19)+1;
			if(check_character_map(x, y) == -1)
			{
				mon_pos.x = x;
				mon_pos.y = y;
				pos_found = TRUE;
			}
		}
		if(attempts == 10000)
		{
			return NULL_CHARACTER;
		}
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
						if(check_character_map(x, y) == -1)
						{
							new_pos.x = x;
							new_pos.y = y;
							open_count++;
							open_pos = realloc(open_pos, sizeof(pos_t) + (sizeof(pos_t) * open_count));
							open_pos[open_count-1] = new_pos;
							open_pos[open_count] = NULL_POS;
						}
					break;
					
					case CORRIDOR:
						if(check_character_map(x, y) == -1)
						{
							new_pos.x = x;
							new_pos.y = y;
							open_count++;
							open_pos = realloc(open_pos, sizeof(pos_t) + (sizeof(pos_t) * open_count));
							open_pos[open_count-1] = new_pos;
							open_pos[open_count] = NULL_POS;
						}
					break;
				}
			}
		}
		if(open_count == 0)
		{
			return NULL_CHARACTER;
		}
		mon_pos = open_pos[rand()%open_count];
	}
	
	monster_t monster = {.abilities = powers, .lost = TRUE,.memory = NULL_POS};
	if((monster.abilities & 0x2) == 0x2)
	{
		monster.memory = get_character_by_id(0).pos;
	}
	if((monster.abilities & 0x4) == 0x4 && dungeon[mon_pos.x][mon_pos.y].space_type == ROCK)
	{
		dungeon[mon_pos.x][mon_pos.y] = Dungeon_Space_Struct_create(CORRIDOR, Dungeon_Space_Corridor_create());
	}
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
  character_tag.character_parent = character_parent_create(character_type, ap);
  
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
		return move_monster(&character_list[index], dungeon);
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
	if(turn_difference == 0)
	{
		turn_difference = from.id - to.id;
	}
	return turn_difference;
}

void update_telepath(void)
{
	int m;
	for(m = 0; m < num_characters; m++)
	{
		if((character_list[m].character_type == MONSTER) && ((character_list[m].character_parent.monster.abilities & 0x2) == 0x2))
		{
			character_list[m].character_parent.monster.memory = get_character_by_id(0).pos;
			character_list[m].character_parent.monster.lost = FALSE;
			//printf("Monster %d knows player is at [%d][%d]\n", character_list[m].id, character_list[m].character_parent.monster.memory.x, character_list[m].character_parent.monster.memory.y);
		}
	}
}

void line_of_sight(Dungeon_Space_Struct **dungeon)
{
	int m;
	for(m = 0; m < num_characters; m++)
	{
		if(character_list[m].character_type == MONSTER)
		{
			if((character_list[m].character_parent.monster.abilities & 0x2) == 0x2)
			{
				continue;
			}
			else if((character_list[m].character_parent.monster.abilities & 0x1) == 0x1)
			{
				if(line_of_sight_helper(character_list[m].pos, dungeon) == TRUE)
				{
					character_list[m].character_parent.monster.memory = get_character_by_id(0).pos;
					character_list[m].character_parent.monster.lost = FALSE;
					printf("Monster %d memorized player at [%d][%d]\n", character_list[m].id, character_list[m].character_parent.monster.memory.x, character_list[m].character_parent.monster.memory.y);
				}
				else
				{
					character_list[m].character_parent.monster.lost = TRUE;
				}
			}
			else
			{
				if(line_of_sight_helper(character_list[m].pos, dungeon) == TRUE)
				{
					character_list[m].character_parent.monster.memory = get_character_by_id(0).pos;
					//printf("Monster %d saw player at [%d][%d]\n", character_list[m].id, character_list[m].character_parent.monster.memory.x, character_list[m].character_parent.monster.memory.y);
				}
				else
				{
					character_list[m].character_parent.monster.memory = NULL_POS;
					//printf("Monster %d lost sight of player\n", character_list[m].id);
				}
			}
		}
	}
}

bool line_of_sight_helper(pos_t monster_pos, Dungeon_Space_Struct **dungeon)
{
	bool found_player = FALSE, failed = FALSE;
	int a = -1, b = -1;
	pos_t current = monster_pos;
	
	while(found_player == FALSE && failed == FALSE)
	{
		current.x += a;
		current.y += b;
		//printf("Checking [%d][%d]\n", current.x, current.y);
		switch(dungeon[current.x][current.y].space_type)
		{
			case ROCK:
			if(a == 1 && b == 1)
			{
				failed = TRUE;
			}
			a++;
			if(a > 1)
			{
				a = -1;
				b++;
			}
			if(a == 0 && b == 0)
			{
				a = 1;
			}
			current = monster_pos;
			break;
			
			case ROOM:
			if((get_character_by_id(0).pos.x == current.x) && (get_character_by_id(0).pos.y == current.y))
			{
				found_player = TRUE;
			}
			break;
			
			case CORRIDOR:
			if((get_character_by_id(0).pos.x == current.x) && (get_character_by_id(0).pos.y == current.y))
			{
				found_player = TRUE;
			}
			break;
		}
	}
	
	return found_player;
}

bool move_monster(character_t *player_to_move, Dungeon_Space_Struct **dungeon)
{
	pos_t move_to = {.x = player_to_move->pos.x, .y = player_to_move->pos.y};
	bool moving = FALSE, erratic = FALSE;
	
	if((player_to_move->character_parent.monster.abilities & 0x8) == 0x8)
	{
		if(rand()%2 == 1)
		{
			erratic = TRUE;
			int a = (rand()%3)-1;
			int b = (rand()%3)-1;
			if((player_to_move->character_parent.monster.abilities & 0x4) == 0x0 && dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b].space_type != ROCK)
			{
				move_to.x += a;
				move_to.y += b;
				moving = TRUE;
			}
			else if((player_to_move->character_parent.monster.abilities & 0x4) == 0x4)
			{
				if(dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b].space_type == ROCK)
				{
					if(dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b].space_union.rock.density < 255)
					{
						return moving;
					}
					uint8_t chisel = dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b].space_union.rock.density;
					chisel = ((chisel - 85) < 0) ? 0 : (chisel - 85);
					dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b].space_union.rock.density = chisel;
					if(chisel == 0)
					{
						move_to.x += a;
						move_to.y += b;
						dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b] = Dungeon_Space_Struct_create(CORRIDOR, Dungeon_Space_Corridor_create());
						moving = TRUE;
					}
				}
				else
				{
					move_to.x += a;
					move_to.y += b;
					moving = TRUE;
				}
			}
		}
		//coin toss random move or chosen move
	}
	
	if((player_to_move->character_parent.monster.abilities & 0x1) == 0x1 && erratic == FALSE)
	{
		if(player_to_move->character_parent.monster.memory.x != NULL_POS.x && player_to_move->character_parent.monster.memory.y != NULL_POS.y )
		{
			if((player_to_move->character_parent.monster.abilities & 0x4) == 0x4)
			{
				if(player_to_move->character_parent.monster.lost == FALSE)
				{
					int a = -1, b = -1, i = -1, j = -1, n, smallest_index = 428400;
					for(n = 0; n < 8; n++)
					{
						
						if(distance_converter(dis_map[(player_to_move->pos.y+j)*80+(player_to_move->pos.x+i)]) < smallest_index && dungeon[player_to_move->pos.x+i][player_to_move->pos.y+j].space_type != ROCK)
						{
							smallest_index = distance_converter(dis_map[(player_to_move->pos.y+j)*80+(player_to_move->pos.x+i)]);
							a = i;
							b = j;
						}
						//printf("i = %d, j = %d\n with distance = %d", i, j, distance_converter(dis_map[(player_to_move->pos.y+j)*80+(player_to_move->pos.x+i)]));
						i++;
						if(i > 1)
						{
							i = -1;
							j++;
						}
						if(i == 0 && j == 0)
						{
							i = 1;
						}
						
						
					}
					if(dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b].space_type == ROCK)
					{
						if(dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b].space_union.rock.density < 255)
						{
							return moving;
						}
						uint8_t chisel = dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b].space_union.rock.density;
						chisel = ((chisel - 85) < 0) ? 0 : (chisel - 85);
						dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b].space_union.rock.density = chisel;
						if(chisel == 0)
						{
							move_to.x += a;
							move_to.y += b;
							dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b] = Dungeon_Space_Struct_create(CORRIDOR, Dungeon_Space_Corridor_create());
							moving = TRUE;
						}
					}
					else
					{
						move_to.x += a;
						move_to.y += b;
						moving = TRUE;
					}
				}
				else
				{
					//printf("Player lost\n");
					int a = 0, b = 0;
					if(player_to_move->pos.x - player_to_move->character_parent.monster.memory.x > 0)
					{
						a = -1;
					}
					else if(player_to_move->pos.x - player_to_move->character_parent.monster.memory.x < 0)
					{
						a = 1;
					}
					
					if(player_to_move->pos.y - player_to_move->character_parent.monster.memory.y > 0)
					{
						b = -1;
					}
					else if(player_to_move->pos.y - player_to_move->character_parent.monster.memory.y < 0)
					{
						b = 1;
					}
					
					if(dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b].space_type == ROCK)
					{
						if(dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b].space_union.rock.density < 255)
						{
							return moving;
						}
						uint8_t chisel = dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b].space_union.rock.density;
						chisel = ((chisel - 85) < 0) ? 0 : (chisel - 85);
						dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b].space_union.rock.density = chisel;
						if(chisel == 0)
						{
							move_to.x += a;
							move_to.y += b;
							dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b] = Dungeon_Space_Struct_create(CORRIDOR, Dungeon_Space_Corridor_create());
							moving = TRUE;
						}
					}
					else
					{
						move_to.x += a;
						move_to.y += b;
						moving = TRUE;
					}
					
				}
				moving = TRUE;
			}
			else
			{
				if(player_to_move->character_parent.monster.lost == FALSE)
				{
					int a = -1, b = -1, i = -1, j = -1, n, smallest_index = 428400;
					for(n = 0; n < 8; n++)
					{
						
						if(distance_converter(dis_map[(player_to_move->pos.y+j)*80+(player_to_move->pos.x+i)]) < smallest_index && dungeon[player_to_move->pos.x+i][player_to_move->pos.y+j].space_type != ROCK)
						{
							smallest_index = distance_converter(dis_map[(player_to_move->pos.y+j)*80+(player_to_move->pos.x+i)]);
							a = i;
							b = j;
						}
						//printf("i = %d, j = %d\n with distance = %d", i, j, distance_converter(dis_map[(player_to_move->pos.y+j)*80+(player_to_move->pos.x+i)]));
						i++;
						if(i > 1)
						{
							i = -1;
							j++;
						}
						if(i == 0 && j == 0)
						{
							i = 1;
						}
						
						
					}
					//printf("Smallest is %d\n", smallest_index);
					move_to.x += a;
					move_to.y += b;
					//printf("Player found\n");
				}
				else
				{
					//printf("Player lost\n");
					int a = 0, b = 0;
					if(player_to_move->pos.x - player_to_move->character_parent.monster.memory.x > 0)
					{
						a = -1;
					}
					else if(player_to_move->pos.x - player_to_move->character_parent.monster.memory.x < 0)
					{
						a = 1;
					}
					
					if(player_to_move->pos.y - player_to_move->character_parent.monster.memory.y > 0)
					{
						b = -1;
					}
					else if(player_to_move->pos.y - player_to_move->character_parent.monster.memory.y < 0)
					{
						b = 1;
					}
					
					if(dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b].space_type != ROCK)
					{
						move_to.x += a;
						move_to.y += b;
					}
					
				}
				moving = TRUE;
			}
		}
	}
	else if(erratic == FALSE)
	{
		if(player_to_move->character_parent.monster.memory.x != NULL_POS.x && player_to_move->character_parent.monster.memory.y != NULL_POS.y )
		{
			//find direction
			int a = 0, b = 0;
			if(player_to_move->pos.x - player_to_move->character_parent.monster.memory.x > 0)
			{
				a = -1;
			}
			else if(player_to_move->pos.x - player_to_move->character_parent.monster.memory.x < 0)
			{
				a = 1;
			}
			
			if(player_to_move->pos.y - player_to_move->character_parent.monster.memory.y > 0)
			{
				b = -1;
			}
			else if(player_to_move->pos.y - player_to_move->character_parent.monster.memory.y < 0)
			{
				b = 1;
			}
			
			if((player_to_move->character_parent.monster.abilities & 0x4) == 0x4)
			{
				//chisel
				//if density <= 0 moving = TRUE;
				if(dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b].space_type == ROCK)
				{
					if(dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b].space_union.rock.density < 255)
					{
						return moving;
					}
					uint8_t chisel = dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b].space_union.rock.density;
					chisel = ((chisel - 85) < 0) ? 0 : (chisel - 85);
					dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b].space_union.rock.density = chisel;
					if(chisel == 0)
					{
						move_to.x += a;
						move_to.y += b;
						dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b] = Dungeon_Space_Struct_create(CORRIDOR, Dungeon_Space_Corridor_create());
						moving = TRUE;
					}
				}
				else
				{
					move_to.x += a;
					move_to.y += b;
					moving = TRUE;
				}
			}
			else
			{
				if(dungeon[player_to_move->pos.x+a][player_to_move->pos.y+b].space_type != ROCK)
				{
					move_to.x += a;
					move_to.y += b;
					
					//printf("I'm there\n");
					
					moving = TRUE;
				}
			}
		}
	}
	
	
	
	character_map[player_to_move->pos.y*80+player_to_move->pos.x] = -1;
	player_to_move->pos.x = move_to.x;
	player_to_move->pos.y = move_to.y;
	character_map[player_to_move->pos.y*80+player_to_move->pos.x] = player_to_move->id;
	player_to_move->cell = dungeon[player_to_move->pos.x][player_to_move->pos.y];
	
	return moving;
}

void set_distance(char *distance)
{
	dis_map = distance;
}
void set_distance_tunneler(char *distance_tunneller)
{
	dis_map_tun = distance_tunneller;
}

int distance_converter(char symbol)
{
	int value = 428400;
	switch(symbol)
		{
			case '0':
			value = 0;
			break;
			
			case '1':
			value = 1;
			break;
			
			case '2':
			value = 2;
			break;
			
			case '3':
			value = 3;
			break;
			
			case '4':
			value = 4;
			break;
			
			case '5':
			value = 5;
			break;
			
			case '6':
			value = 6;
			break;
			
			case '7':
			value = 7;
			break;
			
			case '8':
			value = 8;
			break;
			
			case '9':
			value = 9;
			break;
			
			case 'a':
			value = 10;
			break;
			
			case 'b':
			value = 11;
			break;
			
			case 'c':
			value = 12;
			break;
			
			case 'd':
			value = 13;
			break;
			
			case 'e':
			value = 14;
			break;
			
			case 'f':
			value = 15;
			break;
			
			case 'g':
			value = 16;
			break;
			
			case 'h':
			value = 17;
			break;
			
			case 'i':
			value = 18;
			break;
			
			case 'j':
			value = 19;
			break;
			
			case 'k':
			value = 20;
			break;
			
			case 'l':
			value = 21;
			break;
			
			case 'm':
			value = 22;
			break;
			
			case 'n':
			value = 23;
			break;
			
			case 'o':
			value = 24;
			break;
			
			case 'p':
			value = 25;
			break;
			
			case 'q':
			value = 26;
			break;
			
			case 'r':
			value = 27;
			break;
			
			case 's':
			value = 28;
			break;
			
			case 't':
			value = 29;
			break;
			
			case 'u':
			value = 30;
			break;
			
			case 'v':
			value = 31;
			break;
			
			case 'w':
			value = 32;
			break;
			
			case 'x':
			value = 33;
			break;
			
			case 'y':
			value = 34;
			break;
			
			case 'z':
			value = 35;
			break;
			
			case 'A':
			value = 36;
			break;
			
			case 'B':
			value = 37;
			break;
			
			case 'C':
			value = 38;
			break;
			
			case 'D':
			value = 39;
			break;
			
			case 'E':
			value = 40;
			break;
			
			case 'F':
			value = 41;
			break;
			
			case 'G':
			value = 42;
			break;
			
			case 'H':
			value = 43;
			break;
			
			case 'I':
			value = 44;
			break;
			
			case 'J':
			value = 45;
			break;
			
			case 'K':
			value = 46;
			break;
			
			case 'L':
			value = 47;
			break;
			
			case 'M':
			value = 48;
			break;
			
			case 'N':
			value = 49;
			break;
			
			case 'O':
			value = 50;
			break;
			
			case 'P':
			value = 51;
			break;
			
			case 'Q':
			value = 52;
			break;
			
			case 'R':
			value = 53;
			break;
			
			case 'S':
			value = 54;
			break;
			
			case 'T':
			value = 55;
			break;
			
			case 'U':
			value = 56;
			break;
			
			case 'V':
			value = 57;
			break;
			
			case 'W':
			value = 58;
			break;
			
			case 'X':
			value = 59;
			break;
			
			case 'Y':
			value = 60;
			break;
			
			case 'Z':
			value = 61;
			break;
			
			default:
			value = 428400;
			break;
		}
		
		return value;
}