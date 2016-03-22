#include "CharacterController.h"
#include <stdio.h>

player_t *pc;
int *character_map;
character_t **character_list;
character_t NULL_CHARACTER = *(new_Character());//{speed : -1, timer : -1, id : -1};
int num_characters;
char *dis_map;
char *dis_map_tun;
int dead_monsters = 0;

playerClass::playerClass()
{
	name = "";
}

playerClass::~playerClass()
{
	name = NULL;
}

playerClass::playerClass(const char *player_name)
{
	name = player_name;
}

player_t *new_Player(void)
{
	return ((player_t *) new playerClass());
}

void destroy_Player(player_t *player_to_destroy)
{
	delete ((playerClass *) player_to_destroy);
}

player_t *new_Player_param(const char *player_name)
{
	return ((player_t *) new playerClass(player_name));
}

monsterClass::monsterClass()
{
	abilities = 0;
	lost = true;
	memoryX = -1;
	memoryY = -1;
}
monsterClass::~monsterClass()
{
	abilities = 0;
	lost = true;
	memoryX = -1;
	memoryY = -1;
}
monsterClass::monsterClass(uint8_t powers, bool is_mon_lost, int memX, int memY)
{
	abilities = powers;
	lost = is_mon_lost;
	memoryX = memX;
	memoryY = memY;
}

monster_t *new_Monster()
{
	return ((monster_t *) new monsterClass());
}

void destroy_Monster(monster_t *monster_to_destroy)
{
	delete ((monsterClass *) monster_to_destroy);
}

monster_t *new_Monster_param(uint8_t abilities, boolean lost, pos_t memory)
{
	return ((monster_t *) new monsterClass(abilities, (lost == TRUE)? true : false, memory.x, memory.y));
}

uint8_t get_Monster_abilities(monster_t *mon)
{
	return ((monsterClass *) mon)->get_abilities();
}

boolean get_Monster_lost(monster_t *mon)
{
	return (((monsterClass *) mon)->get_lost() == true)? TRUE : FALSE;
}

void set_Monster_lost(monster_t *mon, boolean is_mon_lost)
{
	((monsterClass *) mon)->set_lost((is_mon_lost == TRUE)? true : false);
}

pos_t get_Monster_memory(monster_t *mon)
{
	pos_t mon_pos;
	mon_pos.x = ((monsterClass *) mon)->get_memoryX();
	mon_pos.y = ((monsterClass *) mon)->get_memoryY();
	return mon_pos;
}

void set_Monster_memory(monster_t *mon, pos_t new_memory)
{
	((monsterClass *) mon)->set_memoryX(new_memory.x);
	((monsterClass *) mon)->set_memoryY(new_memory.y);
}

characterClass::characterClass()
{
	speed = -1;
	timer = -1;
	id = -1;
}
characterClass::~characterClass()
{
	speed = -1;
	timer = -1;
	id = -1;
}

character_t *new_Character()
{
	return ((character_t *) new characterClass());
}
void destroy_Character(character_t * toon)
{
	delete ((characterClass *) toon);
}

int32_t get_Character_speed(character_t * toon)
{
	return ((characterClass *) toon)->speed;
}

int32_t get_Character_timer(character_t * toon)
{
	return ((characterClass *) toon)->timer;
}

void set_Character_timer(character_t * toon, int32_t new_time)
{
	((characterClass *) toon)->timer = new_time;
}

int get_Character_id(character_t * toon)
{
	return ((characterClass *) toon)->id;
}

boolean get_Character_alive(character_t * toon)
{
	return ((characterClass *) toon)->alive;
}

void set_Character_alive(character_t * toon, boolean status)
{
	((characterClass *) toon)->alive = status;
}

pos_t get_Character_pos(character_t * toon)
{
	return ((characterClass *) toon)->pos;
}

void set_Character_pos(character_t * toon, pos_t new_pos)
{
	((characterClass *) toon)->pos = new_pos;
}

Dungeon_Space_Struct get_Character_cell(character_t * toon)
{
	return ((characterClass *) toon)->cell;
}

void set_Character_cell(character_t * toon, Dungeon_Space_Struct new_cell)
{
	((characterClass *) toon)->cell = new_cell;
}

character_type_t get_Character_character_type(character_t * toon)
{
	return ((characterClass *) toon)->character_type;
}

void set_Character_all(character_t * toon, int32_t set_speed, int32_t new_time, int toon_id, boolean status, pos_t new_pos, Dungeon_Space_Struct new_cell, character_type_t toon_type)
{
	((characterClass *) toon)->speed = set_speed;
	set_Character_timer(toon, new_time);
	((characterClass *) toon)->id = toon_id;
	set_Character_alive(toon, status);
	set_Character_pos(toon, new_pos);
	set_Character_cell(toon, new_cell);
	((characterClass *) toon)->character_type = toon_type;
}

character_t *Place_Player(Dungeon_Space_Struct **dungeon, int *seed)
{
	pos_t *open_pos = (pos_t *) malloc(sizeof(pos_t));
	open_pos[0] = NULL_POS;
	character_t *player;
	
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
					open_pos = (pos_t *) realloc(open_pos, sizeof(pos_t) + (sizeof(pos_t) * open_count));
					open_pos[open_count-1] = new_pos;
					open_pos[open_count] = NULL_POS;
				break;
				
				case CORRIDOR:
					new_pos.x = x;
					new_pos.y = y;
					open_count++;
					open_pos = (pos_t *) realloc(open_pos, sizeof(pos_t) + (sizeof(pos_t) * open_count));
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
	pos_t new_pos = open_pos[rand()%open_count];
	pc = new_Player_param("Edwin");
	//pc.name = "Edwin";
	player = (character_t *) pc;//character_tag_create(10, 0, 0, TRUE, new_pos, dungeon[new_pos.x][new_pos.y], PLAYER, pc);
	set_Character_all(player, 10, 0, 0, TRUE, new_pos, dungeon[new_pos.x][new_pos.y], PLAYER);
	create_character_list();
	add_character(player);
	free(open_pos);
	return *player;
}

character_t *create_monster(Dungeon_Space_Struct **dungeon, int *seed)
{	
	uint8_t powers = 0b0000;
	powers = powers | ((rand()%2 == 0) ? 0x0 : 0x1) | ((rand()%2 == 0) ? 0x0 : 0x2) | ((rand()%2 == 0) ? 0x0 : 0x4) | ((rand()%2 == 0) ? 0x0 : 0x8);
	
	//printf("Monster %d is 0x%x\n", num_characters, powers);
	
	pos_t *open_pos = (pos_t *) malloc(sizeof(pos_t));
	pos_t mon_pos;
	int open_count = 0;
	if((0x4 & powers) == 0x4)
	{
		boolean pos_found = FALSE;
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
			return &NULL_CHARACTER;
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
							open_pos = (pos_t *) realloc(open_pos, sizeof(pos_t) + (sizeof(pos_t) * open_count));
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
							open_pos = (pos_t *) realloc(open_pos, sizeof(pos_t) + (sizeof(pos_t) * open_count));
							open_pos[open_count-1] = new_pos;
							open_pos[open_count] = NULL_POS;
						}
					break;
				}
			}
		}
		if(open_count == 0)
		{
			return &NULL_CHARACTER;
		}
		mon_pos = open_pos[rand()%open_count];
	}
	
	monster_t *monster = new_Monster_param(powers, TRUE, NULL_POS);
	if((get_Monster_abilities(monster) & 0x2) == 0x2)
	{
		set_Monster_memory(monster, get_Character_pos(get_character_by_id(0)));
	}
	if((get_Monster_abilities(monster) & 0x4) == 0x4 && dungeon[mon_pos.x][mon_pos.y].space_type == ROCK)
	{
		dungeon[mon_pos.x][mon_pos.y] = Dungeon_Space_Struct_create(CORRIDOR, Dungeon_Space_Corridor_create());
	}
	character_t *mon = (character_t *) monster; //character_tag_create((rand()%16)+5, 0, num_characters, TRUE, mon_pos, dungeon[mon_pos.x][mon_pos.y], MONSTER, monster);
	set_Character_all(mon, (rand()%16)+5, 0, num_characters, TRUE, mon_pos, dungeon[mon_pos.x][mon_pos.y], MONSTER);
	add_character(mon);
	free(open_pos);
	return mon;
}

/*character_parent_t character_parent_create(character_type_t character_type, va_list ap)
{
  character_parent_t character_parent;

  switch(character_type)
    {
    case PLAYER:
      character_parent.player = va_arg(ap, player_t *);
      break;
    case MONSTER:
      character_parent.monster = va_arg(ap, monster_t *);
      break;
    }

  return character_parent;
}*/

/*character_t character_tag_create(int32_t speed, int32_t timer, int id, boolean alive, pos_t pos, Dungeon_Space_Struct cell, character_type_t character_type, ...)
{
  va_list ap;
  va_start(ap, character_type);
  
  character_t character_tag;
  character_tag.speed = speed;
  character_tag.timer = timer;
  character_tag.id = id;
  character_tag.alive = alive;
  character_tag.pos = pos;
  character_tag.cell = cell;
  character_tag.character_type = character_type;
  character_tag.character_parent = character_parent_create(character_type, ap);
  
  va_end(ap);
  
  return character_tag;
}*/

void create_character_list()
{
	character_list = (character_t **) malloc(sizeof(character_t *));
	character_list[0] = &NULL_CHARACTER;
	num_characters = 0;
	character_map = (int *) malloc(sizeof(int) * 1680);
	int i;
	for(i = 0; i < 1680; i++)
	{
		character_map[i] = -1;
	}
}

void add_character(character_t *new_character)
{
	num_characters++;
	character_list = (character_t **) realloc(character_list, sizeof(character_t *) + (sizeof(character_t *) * num_characters));
	character_list[num_characters - 1] = new_character;
	character_list[num_characters] = &NULL_CHARACTER;
	character_map[get_Character_pos(new_character).y*80+get_Character_pos(new_character).x] = get_Character_id(new_character);
}

/*character_t delete_character(int id)
{
	int i;
	boolean deleted = FALSE;
	character_t killed_character = NULL_CHARACTER;
	for(i = 0; i < num_characters; i++)
	{
		if(get_Character_id(character_list[i]) == id && deleted == FALSE)
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
}*/

character_t *get_character_by_id(int id)
{
	int i;
	for(i = 0; i < num_characters; i++)
	{
		if(get_Character_id(character_list[i]) == id)
		{
			return character_list[i];
		}
	}
	
	return &NULL_CHARACTER;
}

int get_character_index_by_id(int id)
{
	int i;
	for(i = 0; i < num_characters; i++)
	{
		if(get_Character_id(character_list[i]) == id)
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

boolean move_character(int character_id, int *seed, Dungeon_Space_Struct **dungeon, ...)
{
	int index = get_character_index_by_id(character_id);
	if(index < 0 || get_Character_alive(character_list[index]) == FALSE) 
	{ 
		return FALSE;
	}
	
	va_list ap;
	va_start(ap, dungeon);
	
	switch(get_Character_character_type(character_list[index]))
	{
		case PLAYER:
		return move_player(character_list[index], va_arg(ap, pos_t), dungeon);
		break;
		
		case MONSTER:
		return move_monster(character_list[index], dungeon);
		break;
	}
	va_end(ap);
	return FALSE;
}

boolean move_player(character_t *player_to_move, pos_t to, Dungeon_Space_Struct **dungeon)
{
	int a = to.x, b = to.y;
	/*switch(to)
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
	}*/
	
	switch(dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b].space_type)
	{
		case ROCK:
		if(dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b].space_union.rock.density == 255)
		{
			return TRUE;
		}
		else
		{
		/*	character_map[player_to_move->pos.y*80+player_to_move->pos.x] = -1;
			player_to_move->pos.x = player_to_move->pos.x+a;
			player_to_move->pos.y = player_to_move->pos.y+b;
			if(character_map[player_to_move->pos.y*80+player_to_move->pos.x] > 0)
			{
				int dead_index = get_character_index_by_id(character_map[player_to_move->pos.y*80+player_to_move->pos.x]);
				if(character_list[dead_index].alive == TRUE)
				{
					character_list[dead_index].alive = FALSE;
					dead_monsters++;
				}
			}
			character_map[player_to_move->pos.y*80+player_to_move->pos.x] = 0;
			dungeon[player_to_move->pos.x][player_to_move->pos.y] = Dungeon_Space_Struct_create(CORRIDOR, Dungeon_Space_Corridor_create());
			player_to_move->cell = dungeon[player_to_move->pos.x][player_to_move->pos.y];*/
			return TRUE;
		}
		break;
		
		case ROOM:
		character_map[get_Character_pos(player_to_move).y*80+get_Character_pos(player_to_move).x] = -1;
		//player_to_move->pos.x = player_to_move->pos.x+a;
		//player_to_move->pos.y = player_to_move->pos.y+b;
		pos_t dest;
		dest.x = get_Character_pos(player_to_move).x+a;
		dest.y = get_Character_pos(player_to_move).y+b;
		set_Character_pos(player_to_move, dest);
		if(character_map[get_Character_pos(player_to_move).y*80+get_Character_pos(player_to_move).x] > 0)
		{
			int dead_index = get_character_index_by_id(character_map[get_Character_pos(player_to_move).y*80+get_Character_pos(player_to_move).x]);
			if(get_Character_alive(character_list[dead_index]) == TRUE)
			{
				set_Character_alive(character_list[dead_index], FALSE);
				dead_monsters++;
			}
		}
		character_map[get_Character_pos(player_to_move).y*80+get_Character_pos(player_to_move).x] = 0;
		set_Character_cell(player_to_move, dungeon[get_Character_pos(player_to_move).x][get_Character_pos(player_to_move).y]);
		return TRUE;
		break;
		
		case CORRIDOR:
		character_map[get_Character_pos(player_to_move).y*80+get_Character_pos(player_to_move).x] = -1;
		//player_to_move->pos.x = player_to_move->pos.x+a;
		//player_to_move->pos.y = player_to_move->pos.y+b;
		pos_t destCor;
		destCor.x = get_Character_pos(player_to_move).x+a;
		destCor.y = get_Character_pos(player_to_move).y+b;
		set_Character_pos(player_to_move, destCor);
		if(character_map[get_Character_pos(player_to_move).y*80+get_Character_pos(player_to_move).x] > 0)
		{
			int dead_index = get_character_index_by_id(character_map[get_Character_pos(player_to_move).y*80+get_Character_pos(player_to_move).x]);
			if(get_Character_alive(character_list[dead_index]) == TRUE)
			{	
				set_Character_alive(character_list[dead_index], FALSE);
				dead_monsters++;
			}

		}
		character_map[get_Character_pos(player_to_move).y*80+get_Character_pos(player_to_move).x] = 0;
		set_Character_cell(player_to_move, dungeon[get_Character_pos(player_to_move).x][get_Character_pos(player_to_move).y]);
		return TRUE;
		break;
	}
	
	return FALSE;
}

int32_t compare_character(const void *key, const void *with)
{
	character_t *from = ((character_t *) key);
	character_t *to = ((character_t *) with);
	
	int32_t turn_difference = get_Character_timer(from) - get_Character_timer(to);
	if(turn_difference == 0)
	{
		turn_difference = get_Character_id(from) - get_Character_id(to);
	}
	return turn_difference;
}

void update_telepath(void)
{
	int m;
	for(m = 0; m < num_characters; m++)
	{
		if((get_Character_character_type(character_list[m]) == MONSTER) && ((get_Monster_abilities((monster_t *)character_list[m]) & 0x2) == 0x2))
		{
			set_Monster_memory((monster_t *)character_list[m], get_Character_pos(get_character_by_id(0)));
			set_Monster_lost((monster_t *)character_list[m], FALSE);
			//printf("Monster %d knows player is at [%d][%d]\n", character_list[m].id, character_list[m].character_parent.monster.memory.x, character_list[m].character_parent.monster.memory.y);
		}
	}
}

void line_of_sight(Dungeon_Space_Struct **dungeon)
{
	int m;
	for(m = 0; m < num_characters; m++)
	{
		if(get_Character_character_type(character_list[m]) == MONSTER)
		{
			if((get_Monster_abilities((monster_t *)character_list[m]) & 0x2) == 0x2)
			{
				continue;
			}
			else if((get_Monster_abilities((monster_t *)character_list[m]) & 0x1) == 0x1)
			{
				if(line_of_sight_helper(get_Character_pos(character_list[m]), dungeon) == TRUE)
				{
					set_Monster_memory((monster_t *)character_list[m], get_Character_pos(get_character_by_id(0)));
					set_Monster_lost((monster_t *)character_list[m], FALSE);
					//printf("Monster %d memorized player at [%d][%d]\n", character_list[m].id, character_list[m].character_parent.monster.memory.x, character_list[m].character_parent.monster.memory.y);
				}
				else
				{
					set_Monster_lost((monster_t *)character_list[m], TRUE);
				}
			}
			else
			{
				if(line_of_sight_helper(get_Character_pos(character_list[m]), dungeon) == TRUE)
				{
					set_Monster_memory((monster_t *)character_list[m], get_Character_pos(get_character_by_id(0)));
					//printf("Monster %d saw player at [%d][%d]\n", character_list[m].id, character_list[m].character_parent.monster.memory.x, character_list[m].character_parent.monster.memory.y);
				}
				else
				{
					set_Monster_memory((monster_t *)character_list[m], NULL_POS);
					//printf("Monster %d lost sight of player\n", character_list[m].id);
				}
			}
		}
	}
}

boolean line_of_sight_helper(pos_t monster_pos, Dungeon_Space_Struct **dungeon)
{
	boolean found_player = FALSE, failed = FALSE;
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
			if((get_Character_pos(get_character_by_id(0)).x == current.x) && (get_Character_pos(get_character_by_id(0)).y == current.y))
			{
				found_player = TRUE;
			}
			break;
			
			case CORRIDOR:
			if((get_Character_pos(get_character_by_id(0)).x == current.x) && (get_Character_pos(get_character_by_id(0)).y == current.y))
			{
				found_player = TRUE;
			}
			break;
		}
	}
	
	return found_player;
}

boolean move_monster(character_t *player_to_move, Dungeon_Space_Struct **dungeon)
{
	pos_t move_to = {.x = get_Character_pos(player_to_move).x, .y = get_Character_pos(player_to_move).y};
	boolean moving = FALSE, erratic = FALSE;
	
	if((get_Monster_abilities((monster_t *)player_to_move) & 0x8) == 0x8)
	{
		if(rand()%2 == 1)
		{
			erratic = TRUE;
			int a = (rand()%3)-1;
			int b = (rand()%3)-1;
			if((get_Monster_abilities((monster_t *)player_to_move) & 0x4) == 0x0 && dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b].space_type != ROCK)
			{
				move_to.x += a;
				move_to.y += b;
				moving = TRUE;
			}
			else if((get_Monster_abilities((monster_t *)player_to_move) & 0x4) == 0x4)
			{
				if(dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b].space_type == ROCK)
				{
					if(dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b].space_union.rock.density >= 255)
					{
						return moving;
					}
					uint8_t chisel = dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b].space_union.rock.density;
					chisel = ((chisel - 85) < 0) ? 0 : (chisel - 85);
					dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b].space_union.rock.density = chisel;
					if(chisel == 0)
					{
						move_to.x += a;
						move_to.y += b;
						dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b] = Dungeon_Space_Struct_create(CORRIDOR, Dungeon_Space_Corridor_create());
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
	
	if((get_Monster_abilities((monster_t *)player_to_move) & 0x1) == 0x1 && erratic == FALSE)
	{
		if(get_Monster_memory((monster_t *)player_to_move).x != NULL_POS.x && get_Monster_memory((monster_t *)player_to_move).y != NULL_POS.y )
		{
			if((get_Monster_abilities((monster_t *)player_to_move) & 0x4) == 0x4)
			{
				if(get_Monster_lost((monster_t *)player_to_move) == FALSE)
				{
					int a = -1, b = -1, i = -1, j = -1, n, smallest_index = 428400;
					for(n = 0; n < 8; n++)
					{
						
						if(distance_converter(dis_map_tun[(get_Character_pos(player_to_move).y+j)*80+(get_Character_pos(player_to_move).x+i)]) < smallest_index)
						{
							smallest_index = distance_converter(dis_map_tun[(get_Character_pos(player_to_move).y+j)*80+(get_Character_pos(player_to_move).x+i)]);
							a = i;
							b = j;
						}
						//printf("i = %d, j = %d with distance = %d\n", i, j, distance_converter(dis_map_tun[(player_to_move->pos.y+j)*80+(player_to_move->pos.x+i)]));
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
					if(dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b].space_type == ROCK)
					{
						if(dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b].space_union.rock.density >= 255)
						{
							return moving;
						}
						uint8_t chisel = dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b].space_union.rock.density;
						chisel = ((chisel - 85) < 0) ? 0 : (chisel - 85);
						dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b].space_union.rock.density = chisel;
						if(chisel == 0)
						{
							move_to.x += a;
							move_to.y += b;
							dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b] = Dungeon_Space_Struct_create(CORRIDOR, Dungeon_Space_Corridor_create());
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
					if(get_Character_pos(player_to_move).x - get_Monster_memory((monster_t *)player_to_move).x > 0)
					{
						a = -1;
					}
					else if(get_Character_pos(player_to_move).x - get_Monster_memory((monster_t *)player_to_move).x < 0)
					{
						a = 1;
					}
					
					if(get_Character_pos(player_to_move).y - get_Monster_memory((monster_t *)player_to_move).y > 0)
					{
						b = -1;
					}
					else if(get_Character_pos(player_to_move).y - get_Monster_memory((monster_t *)player_to_move).y < 0)
					{
						b = 1;
					}
					
					if(dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b].space_type == ROCK)
					{
						if(dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b].space_union.rock.density >= 255)
						{
							return moving;
						}
						uint8_t chisel = dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b].space_union.rock.density;
						chisel = ((chisel - 85) < 0) ? 0 : (chisel - 85);
						dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b].space_union.rock.density = chisel;
						if(chisel == 0)
						{
							move_to.x += a;
							move_to.y += b;
							dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b] = Dungeon_Space_Struct_create(CORRIDOR, Dungeon_Space_Corridor_create());
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
				if(get_Monster_lost((monster_t *)player_to_move) == FALSE)
				{
					int a = -1, b = -1, i = -1, j = -1, n, smallest_index = 428400;
					for(n = 0; n < 8; n++)
					{
						
						if(distance_converter(dis_map[(get_Character_pos(player_to_move).y+j)*80+(get_Character_pos(player_to_move).x+i)]) < smallest_index && dungeon[get_Character_pos(player_to_move).x+i][get_Character_pos(player_to_move).y+j].space_type != ROCK)
						{
							smallest_index = distance_converter(dis_map[(get_Character_pos(player_to_move).y+j)*80+(get_Character_pos(player_to_move).x+i)]);
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
					if(get_Character_pos(player_to_move).x - get_Monster_memory((monster_t *)player_to_move).x > 0)
					{
						a = -1;
					}
					else if(get_Character_pos(player_to_move).x - get_Monster_memory((monster_t *)player_to_move).x < 0)
					{
						a = 1;
					}
					
					if(get_Character_pos(player_to_move).y - get_Monster_memory((monster_t *)player_to_move).y > 0)
					{
						b = -1;
					}
					else if(get_Character_pos(player_to_move).y - get_Monster_memory((monster_t *)player_to_move).y < 0)
					{
						b = 1;
					}
					
					if(dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b].space_type != ROCK)
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
		if(get_Monster_memory((monster_t *)player_to_move).x != NULL_POS.x && get_Monster_memory((monster_t *)player_to_move).y != NULL_POS.y )
		{
			//find direction
			int a = 0, b = 0;
			if(get_Character_pos(player_to_move).x - get_Monster_memory((monster_t *)player_to_move).x > 0)
			{
				a = -1;
			}
			else if(get_Character_pos(player_to_move).x - get_Monster_memory((monster_t *)player_to_move).x < 0)
			{
				a = 1;
			}
			
			if(get_Character_pos(player_to_move).y - get_Monster_memory((monster_t *)player_to_move).y > 0)
			{
				b = -1;
			}
			else if(get_Character_pos(player_to_move).y - get_Monster_memory((monster_t *)player_to_move).y < 0)
			{
				b = 1;
			}
			
			if((get_Monster_abilities((monster_t *)player_to_move) & 0x4) == 0x4)
			{
				//chisel
				//if density <= 0 moving = TRUE;
				if(dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b].space_type == ROCK)
				{
					if(dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b].space_union.rock.density >= 255)
					{
						return moving;
					}
					uint8_t chisel = dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b].space_union.rock.density;
					chisel = ((chisel - 85) < 0) ? 0 : (chisel - 85);
					dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b].space_union.rock.density = chisel;
					if(chisel == 0)
					{
						move_to.x += a;
						move_to.y += b;
						dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b] = Dungeon_Space_Struct_create(CORRIDOR, Dungeon_Space_Corridor_create());
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
				if(dungeon[get_Character_pos(player_to_move).x+a][get_Character_pos(player_to_move).y+b].space_type != ROCK)
				{
					move_to.x += a;
					move_to.y += b;
					
					//printf("I'm there\n");
					
					moving = TRUE;
				}
			}
		}
	}
	
	
	
	character_map[get_Character_pos(player_to_move).y*80+get_Character_pos(player_to_move).x] = -1;
	//player_to_move->pos.x = move_to.x;
	//player_to_move->pos.y = move_to.y;
	set_Character_pos(player_to_move, move_to);
	if(character_map[get_Character_pos(player_to_move).y*80+get_Character_pos(player_to_move).x] >= 0)
	{
		int dead_index = get_character_index_by_id(character_map[get_Character_pos(player_to_move).y*80+get_Character_pos(player_to_move).x]);
		if(get_Character_alive(character_list[dead_index]) == TRUE)
		{	
				set_Character_alive(character_list[dead_index], FALSE);
				dead_monsters++;
		}
	}
	character_map[get_Character_pos(player_to_move).y*80+get_Character_pos(player_to_move).x] = get_Character_id(player_to_move);
	set_Character_cell(player_to_move, dungeon[get_Character_pos(player_to_move).x][get_Character_pos(player_to_move).y]);
	
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

void Destroy_Characters(void)
{
	destroy_Player((player_t *)character_list[0]);
	int m;
	for(m = 1; m < num_characters; m++)
	{
		destroy_Monster((monster_t *)character_list[m]);
	}
	free(character_list);
	free(character_map);
}