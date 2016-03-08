#include "GameStateManager.h"

Dungeon_Space_Struct **current_dungeon;
character_t player_character;
char *distance_map;
graph_t graphed_dungeon;
char *distance_dungeon;
char *distance_dungeon_tunneler;
int seed_state, num_rooms_state;
int game_state = 0;
int input = -1;
int scroll_index = 0;
int level = 0;
stair_t stair_set[2];
int stair_player = -1;

void Set_Dungeon(Dungeon_Space_Struct **dungeon)
{
	current_dungeon = dungeon;
}

void Set_Player(character_t player)
{
	player_character = player;
}

void Set_Stairs(stair_t stairs)
{
	//printf("Stair pos = [%d][%d]\n", stairs.location.x, stairs.location.y);
	if(stairs.direction == DOWNSTAIRS)
	{
		//printf("I'm here\n");
		stair_set[0] = stairs;
	}
	else
	{
		//printf("Stair = [%d][%d]\n", stairs.location.x, stairs.location.y);
		stair_set[1] = stairs;
	}
}

void Set_Debug_Info(int seed, int num_rooms)
{
	seed_state = seed;
	num_rooms_state = num_rooms;
}

void populate_monsters(int num_mon, int *seed)
{
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
	
	int m;
	for(m = 0; m < num_mon; m++)
	{
		create_monster(current_dungeon, &seed_local);
	}
}

char *Generate_Distance_Dungeon(bool tunneler)
{
	graphed_dungeon = GenerateGraph(current_dungeon, tunneler);
	vertex_t player_vertex = Get_Vertex(get_character_by_id(0).pos.x, get_character_by_id(0).pos.y);
	uint distances_int[graphed_dungeon.num_vertices];
	
	
	/*int numVertex = graphed_dungeon.num_vertices;
	int t;
	for(t = 0; t < numVertex; t++)
	{
		printf("Vertex[%d]: weight=%d, x=%d, y=%d\n", t, graphed_dungeon.vertices[t].weight, graphed_dungeon.vertices[t].x, graphed_dungeon.vertices[t].y);
	}*/
	
	Dijkstra(graphed_dungeon, player_vertex);
	
	int d;
	for(d = 0; d < graphed_dungeon.num_vertices; d++)
	{
		distances_int[d] = Get_Cost(graphed_dungeon.vertices[d]);
		//printf("Int at [%d][%d] in [%d] = %d\n", graphed_dungeon.vertices[d].x , graphed_dungeon.vertices[d].y, d, distances_int[d]);
	}
	//printf("Using distances_int = %d\n", distances_int[0]);
	
	
	distance_map = malloc(1680 * sizeof(char));
	int z;
	for(z = 0; z < 1680; z++)
	{
		//distance_map = malloc(21 * sizeof(char));
		//printf("Before char at [%d][%d] = %c\n", x, y, distance_map[x][y]);
		//printf("Int at [%d][%d] in [%d] = %d\n", x, y, y*80+x, distances_int[y*80+x]);
		//distance_map[x][y] = (char) distances_int[y*80+x];
		//printf("distances_int[0] = %d\n", distances_int[0]);
		switch(distances_int[z])
		{
			case 0:
			distance_map[z] = '0';
			break;
			
			case 1:
			distance_map[z] = '1';
			break;
			
			case 2:
			distance_map[z] = '2';
			break;
			
			case 3:
			distance_map[z] = '3';
			break;
			
			case 4:
			distance_map[z] = '4';
			break;
			
			case 5:
			distance_map[z] = '5';
			break;
			
			case 6:
			distance_map[z] = '6';
			break;
			
			case 7:
			distance_map[z] = '7';
			break;
			
			case 8:
			distance_map[z] = '8';
			break;
			
			case 9:
			distance_map[z] = '9';
			break;
			
			case 10:
			distance_map[z] = 'a';
			break;
			
			case 11:
			distance_map[z] = 'b';
			break;
			
			case 12:
			distance_map[z] = 'c';
			break;
			
			case 13:
			distance_map[z] = 'd';
			break;
			
			case 14:
			distance_map[z] = 'e';
			break;
			
			case 15:
			distance_map[z] = 'f';
			break;
			
			case 16:
			distance_map[z] = 'g';
			break;
			
			case 17:
			distance_map[z] = 'h';
			break;
			
			case 18:
			distance_map[z] = 'i';
			break;
			
			case 19:
			distance_map[z] = 'j';
			break;
			
			case 20:
			distance_map[z] = 'k';
			break;
			
			case 21:
			distance_map[z] = 'l';
			break;
			
			case 22:
			distance_map[z] = 'm';
			break;
			
			case 23:
			distance_map[z] = 'n';
			break;
			
			case 24:
			distance_map[z] = 'o';
			break;
			
			case 25:
			distance_map[z] = 'p';
			break;
			
			case 26:
			distance_map[z] = 'q';
			break;
			
			case 27:
			distance_map[z] = 'r';
			break;
			
			case 28:
			distance_map[z] = 's';
			break;
			
			case 29:
			distance_map[z] = 't';
			break;
			
			case 30:
			distance_map[z] = 'u';
			break;
			
			case 31:
			distance_map[z] = 'v';
			break;
			
			case 32:
			distance_map[z] = 'w';
			break;
			
			case 33:
			distance_map[z] = 'x';
			break;
			
			case 34:
			distance_map[z] = 'y';
			break;
			
			case 35:
			distance_map[z] = 'z';
			break;
			
			case 36:
			distance_map[z] = 'A';
			break;
			
			case 37:
			distance_map[z] = 'B';
			break;
			
			case 38:
			distance_map[z] = 'C';
			break;
			
			case 39:
			distance_map[z] = 'D';
			break;
			
			case 40:
			distance_map[z] = 'E';
			break;
			
			case 41:
			distance_map[z] = 'F';
			break;
			
			case 42:
			distance_map[z] = 'G';
			break;
			
			case 43:
			distance_map[z] = 'H';
			break;
			
			case 44:
			distance_map[z] = 'I';
			break;
			
			case 45:
			distance_map[z] = 'J';
			break;
			
			case 46:
			distance_map[z] = 'K';
			break;
			
			case 47:
			distance_map[z] = 'L';
			break;
			
			case 48:
			distance_map[z] = 'M';
			break;
			
			case 49:
			distance_map[z] = 'N';
			break;
			
			case 50:
			distance_map[z] = 'O';
			break;
			
			case 51:
			distance_map[z] = 'P';
			break;
			
			case 52:
			distance_map[z] = 'Q';
			break;
			
			case 53:
			distance_map[z] = 'R';
			break;
			
			case 54:
			distance_map[z] = 'S';
			break;
			
			case 55:
			distance_map[z] = 'T';
			break;
			
			case 56:
			distance_map[z] = 'U';
			break;
			
			case 57:
			distance_map[z] = 'V';
			break;
			
			case 58:
			distance_map[z] = 'W';
			break;
			
			case 59:
			distance_map[z] = 'X';
			break;
			
			case 60:
			distance_map[z] = 'Y';
			break;
			
			case 61:
			distance_map[z] = 'Z';
			break;
			
			default:
			distance_map[z] = ' ';
			break;
		}
		//printf("Char at [%d][%d] = %c\n", x, y, distance_map[x][y]);
	}
	
	Destroy_Distance();
	return distance_map;
}

void Draw_Dungeon(int use_curses)
{
	char renderer[1701];
	int x;
	int y;
	for(y = 0; y < 21; y++)
	{
		for(x = 0; x <= 80; x++)
		{
			if(x == 80)
			{
				renderer[y*81+x] = '\n';
				//printf("%c", renderer[y*80+x]);
			}
			else if(get_character_by_id(0).pos.x == x && get_character_by_id(0).pos.y == y && get_character_by_id(0).alive == TRUE)
			{
				renderer[y*81+x] = '@';
				//printf("%c", renderer[y*80+x]);
			}
			else if(check_character_map(x, y) > 0 && get_character_by_id(check_character_map(x, y)).alive == TRUE)
			{
				switch(get_character_by_id(check_character_map(x, y)).character_parent.monster.abilities)
				{
					case 0x0:
						renderer[y*81+x] = '0';
					break;
					
					case 0x1:
						renderer[y*81+x] = '1';
					break;
					
					case 0x2:
						renderer[y*81+x] = '2';
					break;
					
					case 0x3:
						renderer[y*81+x] = '3';
					break;
					
					case 0x4:
						renderer[y*81+x] = '4';
					break;
					
					case 0x5:
						renderer[y*81+x] = '5';
					break;
					
					case 0x6:
						renderer[y*81+x] = '6';
					break;
					
					case 0x7:
						renderer[y*81+x] = '7';
					break;
					
					case 0x8:
						renderer[y*81+x] = '8';
					break;
					
					case 0x9:
						renderer[y*81+x] = '9';
					break;
					
					case 0xa:
						renderer[y*81+x] = 'a';
					break;
					
					case 0xb:
						renderer[y*81+x] = 'b';
					break;
					
					case 0xc:
						renderer[y*81+x] = 'c';
					break;
					
					case 0xd:
						renderer[y*81+x] = 'd';
					break;
					
					case 0xe:
						renderer[y*81+x] = 'e';
					break;
					
					case 0xf:
						renderer[y*81+x] = 'f';
					break;
				}
				//renderer[y*80+x] = get_character_by_id(check_character_map(x, y)).character_parent.monster.abilities;//printf("%x", get_character_by_id(check_character_map(x, y)).character_parent.monster.abilities);
				//printf("%c", renderer[y*80+x]);
			}
			else
			{
				switch(current_dungeon[x][y].space_type)
				{
					case ROCK :
					
						if(current_dungeon[x][y].space_union.rock.density == 255)
						{
							renderer[y*81+x] = '~';
							//printf("%c", renderer[y*80+x]);
						}
						else 
						{
							renderer[y*81+x] = ' ';
							//printf("%c", renderer[y*80+x]);
						}
					
					break;
					case ROOM :
						if(stair_set[0].location.x == x && stair_set[0].location.y == y)
						{
							renderer[y*81+x] = '>';
						}
						else if(level > 0 && stair_set[1].location.x == x && stair_set[1].location.y == y)
						{
							renderer[y*81+x] = '<';
						}
						else
						{
							renderer[y*81+x] = '.';
						}
						//printf("%c", renderer[y*80+x]);
					
					break;
					case CORRIDOR :
						renderer[y*81+x] = '#';
						//printf("%c", renderer[y*80+x]);
					break;
				}
			}
		}
		//printf("\n");
	}
	
	
	char debug_line[80];
	sprintf(debug_line, "Seed = %d, Input = %d, Monsters alive = %d, Level = %d", seed_state, input, (num_characters - 1) - dead_monsters, level);
	int debug_len = strlen(debug_line);
	if(use_curses == 1)
	{
		start_color();
		init_pair(1, COLOR_WHITE, COLOR_BLACK);
		init_pair(2, COLOR_BLUE, COLOR_BLACK);
		init_pair(3, COLOR_RED, COLOR_BLACK);
		init_pair(4, COLOR_BLACK, COLOR_MAGENTA);
		init_pair(5, COLOR_YELLOW, COLOR_BLACK);
		init_pair(6, COLOR_BLACK, COLOR_GREEN);
		init_pair(7, COLOR_BLACK, COLOR_YELLOW);
		init_pair(8, COLOR_CYAN, COLOR_BLACK);
		init_pair(9, COLOR_BLACK, COLOR_RED);
		init_pair(10, COLOR_BLACK, COLOR_BLUE);
		init_pair(11, COLOR_BLACK, COLOR_WHITE);

		clear();
		
		int d;
		for(d = 0; d < 1701; d++)
		{
			mvaddch(0, d%debug_len, debug_line[d%debug_len]);
			if(get_character_by_id(0).pos.x	== d-((d/81)*81) && get_character_by_id(0).pos.y == (d/81))
			{
				attron(COLOR_PAIR(8));
			}
			else if(check_character_map(d-((d/81)*81), (d/81)) > 0 && get_character_by_id(check_character_map(d-((d/81)*81), (d/81))).alive == TRUE)
			{
				attron(COLOR_PAIR(3));
			}
			else if(stair_set[0].location.x == d-((d/81)*81) && stair_set[0].location.y == (d/81))
			{
				attron(COLOR_PAIR(6));
			}
			else if(level > 0 && stair_set[1].location.x == d-((d/81)*81) && stair_set[1].location.y == (d/81))
			{
				attron(COLOR_PAIR(4));
			}
			else if(renderer[d] == '#')
			{
				attron(COLOR_PAIR(7));
			}
			else if(renderer[d] == '.')
			{
				attron(COLOR_PAIR(11));
			}
			else
			{
				attron(COLOR_PAIR(1));
			}
			mvaddch((d/81)+1, d-((d/81)*81), renderer[d]);
			
		}
		refresh();
	}
	else
	{
		int l;
		/*for(l = debug_len; l < 80; l++)
		{
			debug_line[l] = ' ';
		}*/
		initscr();
		clear();
		start_color();
		init_pair(8, COLOR_BLACK, COLOR_RED);
		init_pair(11, COLOR_BLACK, COLOR_WHITE);
		if(game_state == 1)
		{
			attron(COLOR_PAIR(8));
		}
		else if (game_state == 2)
		{
			attron(COLOR_PAIR(11));
		}
		printw("%s\n", debug_line);
		int d;
		for(d = 0; d < 1701; d++)
		{
			if(character_list[0].pos.y == (d/81) && character_list[0].pos.x == d-((d/81)*81) && game_state == 2)
			{
				printw("%c", '@');
			}
			else if(renderer[d] != '\n')
			{
				printw("%c", renderer[d]);
			}
		}
		if(game_state == 1)
		{
			printw("Player is dead                                                                  \n");
		}
		else if(game_state == 2)
		{
			printw("The drunk player wins!                                                          \n");
		}
		refresh();
		printw("Press any key to exit                                                           \n");
		getch();
		endwin();
	}
	
}

void Draw_Monster_List(void)
{
	char monster_info[num_characters-1][80];
	char debug_line[80];
	sprintf(debug_line, "Seed = %d, Input = %d, Monsters alive = %d, Level = %d", seed_state, input, (num_characters - 1) - dead_monsters, level);
	int m, d, dead_count = 0;
	clear();
	for(d = 0; d < strlen(debug_line); d++)
	{
		mvaddch(0, d, debug_line[d]);
	}
	for(m = 1 + scroll_index; (m < num_characters) && (m < 24+scroll_index); m++)
	{
		/*if(m > 23)
		{
			break;
		}*/
		if(character_list[m].alive == FALSE)
		{
			dead_count++;
			continue;
		}
		pos_t distance_to_player = {character_list[0].pos.x - character_list[m].pos.x, character_list[0].pos.y - character_list[m].pos.y};
		sprintf(monster_info[m-1], "%x: is %d %s and %d %s", character_list[m].character_parent.monster.abilities, (distance_to_player.x > 0)? distance_to_player.x : distance_to_player.x*-1,(distance_to_player.x > 0) ? "west" : "east", (distance_to_player.y > 0)? distance_to_player.y : distance_to_player.y*-1,(distance_to_player.y > 0) ? "north" : "south");
		int c;
		for(c = 0; c < strlen(monster_info[m-1]); c++)
		{
			mvaddch(m - dead_count - scroll_index, c, monster_info[m-1][c]);
		}
	}
	refresh();
}

void Draw_Distance_Dungeon(char *char_map)
{
	int x;
	int y;
	for(y = 0; y < 21; y++)
	{
		for(x = 0; x < 80; x++)
		{
			if(x == 0 || x == 79 || y == 0 || y == 20)
			{
				printf("~");
			}
			else
			{
				if(char_map[y*80+x] == ' ')
				{
					switch(current_dungeon[x][y].space_type)
				{
					case ROCK :
						printf(" ");
					break;
					
					case ROOM :
						printf(".");
					break;
					
					case CORRIDOR :
						printf("#");
					break;
				}
				}
				else 
				{
					printf("%c", char_map[y*80+x]);
				}
			}
			
		}
		printf("\n");
	}
}

void Destroy_All(void)
{
	//Destroy_Dijkstra();
	Destroy_Graph(&graphed_dungeon);
	//free(distance_map);
}

int turn(int *seed, int num_mon)
{
	//binheap_node_t *nodes[num_characters];
	
	binheap_t h;
	binheap_init(&h, compare_character, NULL);	
	
	/*vertex_t *path = Get_Path(Get_Vertex(character_list[0].pos.x, character_list[0].pos.y), Get_Vertex(character_list[1].pos.x, character_list[1].pos.y));
	int l = 1;
	printf("Path is: ");
	while(Compare_Vertices(path[l], NULL_VERTEX) == FALSE)
	{
		printf("[%d][%d]->", path[l].x, path[l].y);
		l++;
	}
	printf("\n");*/
	
	int p;
	for(p = 0; p < num_characters; p++)
	{
		/*nodes[p] = */binheap_insert(&h, character_list + p);
	}
	line_of_sight(current_dungeon);
	while(!binheap_is_empty(&h))
	{
		character_t *current = (character_t *) binheap_remove_min(&h);
		
		pos_t moving_to = {0, 0};
		
		if(current->character_type == PLAYER)
		{
			if(character_list[0].alive == FALSE)
			{
				//printf("Player is dead\n");
				game_state = 1;
				free(distance_dungeon);
				free(distance_dungeon_tunneler);
				break;
			}
			if(dead_monsters == num_characters - 1)
			{
				free(distance_dungeon);
				free(distance_dungeon_tunneler);
				//printf("The drunk player wins!\n");
				game_state = 2;
				break;
			}
			if(game_state == 3)
			{
				free(distance_dungeon);
				free(distance_dungeon_tunneler);
				break;
			}
			if(game_state != 4)
			{
				//dead_monsters = 0;
				//num_characters = num_mon+1;
				free(distance_dungeon);
				Destroy_Graph(&graphed_dungeon);
			}
			distance_dungeon = Generate_Distance_Dungeon(FALSE);
			//Draw_Distance_Dungeon(distance_dungeon);
			set_distance(distance_dungeon);
			if(game_state != 4)
			{
				free(distance_dungeon_tunneler);
				Destroy_Graph(&graphed_dungeon);
			}
			distance_dungeon_tunneler = Generate_Distance_Dungeon(TRUE);
			set_distance_tunneler(distance_dungeon_tunneler);
			if(game_state == 4)
			{
				dead_monsters = 0;
				num_characters = num_mon+1;
				game_state = 0;
			}
			update_telepath();
			line_of_sight(current_dungeon);
			Draw_Dungeon(1);
			//sleep(3);
			define_new_keys();
			input = -1;
			while(input < 0 && game_state != 3)
			{
				input = input_handler(getch());
				if(input < 9)
				{
					moving_to = get_direction(input);
				}
				if(input == 13 || input == 14)
				{
					if(input == 13 && character_list[0].pos.x == stair_set[0].location.x && character_list[0].pos.y == stair_set[0].location.y)
					{
						level++;
						stair_player = DOWNSTAIRS;
						game_state = 3;
					}
					else if(level > 0 && input == 14 && character_list[0].pos.x == stair_set[1].location.x && character_list[0].pos.y == stair_set[1].location.y)
					{
						level--;
						stair_player = UPSTAIRS;
						game_state = 3;
					}
				}
				while(input == 9)
				{
					Draw_Monster_List();
					int menu_input = input_handler(getch());
					if(menu_input == ESCAPE)
					{
						Draw_Dungeon(1);
						input = input_handler(getch());
						if(input < 9)
						{
							moving_to = get_direction(input);
						}
						if(input == 9)
						{
							continue;
						}
						break;
					}
					else if((num_characters - 1)- dead_monsters > 23 && ((menu_input == 12 && ((num_characters - 1)- dead_monsters) - scroll_index > 23) || (menu_input == 11 && scroll_index > 0)))
					{
						if(menu_input == 12)
						{
							scroll_index++;
							continue;
						}
						else if(menu_input == 11)
						{
							scroll_index--;
							continue;
						}
					}
				}
				if(input > 8)
				{
					input = -1;
				}
			}
		}
		
		move_character(current->id, seed, current_dungeon, moving_to);
		current->timer += 100/current->speed;
		/*nodes[p] = */binheap_insert(&h, current);
	}
	
	Destroy_Characters();
	//Destroy_All();
	binheap_delete(&h);
	return level;
}

int input_handler(int key)
{
	switch(key)
	{
		//UP
		case 107:
			return UP;
		break;
		
		case 56:
			return UP;
		break;
		
		case 119:
			return UP;
		break;
		
		case 1008:
			return UP;
		break;
		
		//DOWN
		case 106:
			return DOWN;
		break;
		
		case 50:
			return DOWN;
		break;
		
		case 115:
			return DOWN;
		break;
		
		case 1002:
			return DOWN;
		break;
		
		//LEFT
		case 104:
			return LEFT;
		break;
		
		case 52:
			return LEFT;
		break;
		
		case 97:
			return LEFT;
		break;
		
		case 1004:
			return LEFT;
		break;
		
		//RIGHT
		case 108:
			return RIGHT;
		break;
		
		case 54:
			return RIGHT;
		break;
		
		case 100:
			return RIGHT;
		break;
		
		case 1006:
			return RIGHT;
		break;
		
		//UP_LEFT
		case 121:
			return UP_LEFT;
		break;
		
		case 55:
			return UP_LEFT;
		break;
		
		case 113:
			return UP_LEFT;
		break;
		
		case 1007:
			return UP_LEFT;
		break;
		
		//UP_RIGHT
		case 117:
			return UP_RIGHT;
		break;
		
		case 57:
			return UP_RIGHT;
		break;
		
		case 101:
			return UP_RIGHT;
		break;
		
		case 1009:
			return UP_RIGHT;
		break;
		
		//DOWN_LEFT
		case 98:
			return DOWN_LEFT;
		break;
		
		case 49:
			return DOWN_LEFT;
		break;
		
		case 122:
			return DOWN_LEFT;
		break;
		
		case 1001:
			return DOWN_LEFT;
		break;
		
		//DOWN_RIGHT
		case 110:
			return DOWN_RIGHT;
		break;
		
		case 51:
			return DOWN_RIGHT;
		break;
		
		case 99:
			return DOWN_RIGHT;
		break;
		
		case 1003:
			return DOWN_RIGHT;
		break;
		
		//REST
		case 32:
			return REST;
		break;
		
		case 1005:
			return REST;
		break;
		
		case 1040:
			return REST;
		break;
		
		//MONSTER_LIST
		case 109:
			return MONSTER_LIST;
		break;
		
		//ESCAPE
		case 27:
			return ESCAPE;
		break;
		
		//SCROLL_UP
		case KEY_UP:
			return SCROLL_UP;
		break;
		
		//SCROLL_DOWN
		case KEY_DOWN:
			return SCROLL_DOWN;
		break;
		
		//DOWN_STAIRS
		case 62:
			return DOWN_STAIRS;
		break;
		
		//UP_STAIRS
		case 60:
			return UP_STAIRS;
		break;
	}
	
	
	return key;
}

pos_t get_direction(command_t key)
{
	pos_t direction = {0, 0};
	switch(key)
	{
		case UP:
			direction.x = 0;
			direction.y = -1;
			return direction;
		break;
		
		case DOWN:
			direction.x = 0;
			direction.y = 1;
			return direction;
		break;
		
		case LEFT:
			direction.x = -1;
			direction.y = 0;
			return direction;
		break;
		
		case RIGHT:
			direction.x = 1;
			direction.y = 0;
			return direction;
		break;
		
		case UP_LEFT:
			direction.x = -1;
			direction.y = -1;
			return direction;
		break;
		
		case UP_RIGHT:
			direction.x = 1;
			direction.y = -1;
			return direction;
		break;
		
		case DOWN_LEFT:
			direction.x = -1;
			direction.y = 1;
			return direction;
		break;
		
		case DOWN_RIGHT:
			direction.x = 1;
			direction.y = 1;
			return direction;
		break;
			
		case REST:
			direction.x = 0;
			direction.y = 0;
			return direction;
		break;
		
		default:
		break;
	}
	
	return direction;
}

void define_new_keys(void)
{
	define_key("\033Op", 1000);
	define_key("\033Oq", 1001);
	define_key("\033Or", 1002);
	define_key("\033Os", 1003);
	define_key("\033Ot", 1004);
	define_key("\033Ou", 1005);
	define_key("\033Ov", 1006);
	define_key("\033Ow", 1007);
	define_key("\033Ox", 1008);
	define_key("\033Oy", 1009);
	
	// non-arrow keypad keys (for macros)
	define_key("\033OM", 1010); // Enter
	define_key("\033OP", 1011); // NumLock
	define_key("\033OQ", 1012); // /
	define_key("\033OR", 1013); // *
	define_key("\033OS", 1014); // -
	define_key("\033Oj", 1015); // *
	define_key("\033Ok", 1016); // +
	define_key("\033Ol", 1017); // +
	define_key("\033Om", 1018); // .
	define_key("\033On", 1019); // .
	define_key("\033Oo", 1020); // -

	// variants.  Ugly curses won't allow us to return the same code...
	define_key("\033[1~", 1031); // Home
	define_key("\033[4~", 1034); // End
	define_key("\033[E",  1040); // center arrow
}