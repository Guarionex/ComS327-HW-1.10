#include "GameStateManager.h"

Dungeon_Space_Struct **current_dungeon;
character_t *player_character;
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
pos_t last_pos;
char memory_dungeon[80][21];
vector<itemClass> levelItems;
char playerMessage[80] = " ";
char monsterMessage[80] = " ";


void Set_Dungeon(Dungeon_Space_Struct **dungeon)
{
	current_dungeon = dungeon;
}

/*void Set_Player(character_t player)
{
	player_character = player;
}*/

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

void Set_Items(vector<itemClass> itemsToSet)
{
	levelItems = itemsToSet;
}

void Set_Debug_Info(int seed, int num_rooms)
{
	seed_state = seed;
	num_rooms_state = num_rooms;
}

void populate_monsters(int num_mon, int *seed, vector<monsterClass> monsterList)
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
		create_monster(current_dungeon, &seed_local, monsterList);
	}
}

char *Generate_Distance_Dungeon(boolean tunneler)
{
	graphed_dungeon = GenerateGraph(current_dungeon, tunneler);
	vertex_t player_vertex = Get_Vertex(get_Character_pos(get_character_by_id(0)).x, get_Character_pos(get_character_by_id(0)).y);
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
	
	
	distance_map = (char *) malloc(1680 * sizeof(char));
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
			else if(get_Character_pos(get_character_by_id(0)).x == x && get_Character_pos(get_character_by_id(0)).y == y && get_Character_alive(get_character_by_id(0)) == TRUE)
			{
				renderer[y*81+x] = '@';
				//printf("%c", renderer[y*80+x]);
			}
			else if(check_character_map(x, y) > 0 && get_Character_alive(get_character_by_id(check_character_map(x, y))) == TRUE)
			{
				renderer[y*81+x] = get_Character_symbol(get_character_by_id(check_character_map(x, y)));
				/*switch(get_Monster_abilities((monster_t *)get_character_by_id(check_character_map(x, y))))
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
				}*/
				//renderer[y*80+x] = get_character_by_id(check_character_map(x, y)).character_parent.monster.abilities;//printf("%x", get_character_by_id(check_character_map(x, y)).character_parent.monster.abilities);
				//printf("%c", renderer[y*80+x]);
			}
			else if(containsItemAt(levelItems, x, y))
			{
				vector<itemClass> itemsHere = getItemsAt(levelItems, x, y);
				if(itemsHere.size() > 1)
				{
					renderer[y*81+x] = '&';
				}
				else
				{
					renderer[y*81+x] = itemsHere[0].symbol;
				}
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
							renderer[y*81+x] = '#';
						}
						//printf("%c", renderer[y*80+x]);
					break;
				}
			}
		}
		//printf("\n");
	}
	
	
	char debug_line[80];
	sprintf(debug_line, "Seed = %d, Input = %d, Monsters alive = %d, Level = %d, HP = %d", seed_state, input, (num_characters - 1) - dead_monsters, level, get_Character_healthPoints(character_list[0]));
	int debug_len = strlen(debug_line);
	int playerMessage_len = strlen(playerMessage);
	int monsterMessage_len = strlen(monsterMessage);
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
		init_pair(12, COLOR_GREEN, COLOR_BLACK);
		init_pair(13, COLOR_MAGENTA, COLOR_BLACK);

		clear();
		
		int d;
		for(d = 0; d < 1701; d++)
		{
			attron(COLOR_PAIR(1));
			mvaddch(0, d%debug_len, debug_line[d%debug_len]);
			/*if(get_Character_pos(get_character_by_id(0)).x	== d-((d/81)*81) && get_Character_pos(get_character_by_id(0)).y == (d/81))
			{
				attron(COLOR_PAIR(8));
			}
			else if(check_character_map(d-((d/81)*81), (d/81)) > 0 && get_Character_alive(get_character_by_id(check_character_map(d-((d/81)*81), (d/81)))) == TRUE)
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
			mvaddch((d/81)+1, d-((d/81)*81), memory_dungeon[d-((d/80)*80)][d/80]);//renderer[d]);*/
			
		}
		
		int u, v;
		for(v = 0; v < 21; v++)
		{
			for(u = 0; u < 80; u++)
			{
				if(memory_dungeon[u][v] == '@')
				{
					attron(COLOR_PAIR(8));
				}
				else if((get_Character_pos(get_character_by_id(0)).x - u >3 || get_Character_pos(get_character_by_id(0)).x - u <-3) || (get_Character_pos(get_character_by_id(0)).y - v >3 || get_Character_pos(get_character_by_id(0)).y - v <-3))
				{
					attron(COLOR_PAIR(1));
				}
				else if(memory_dungeon[u][v] == '~')
				{
					attron(COLOR_PAIR(1));
				}
				else if(memory_dungeon[u][v] == '>')
				{
					attron(COLOR_PAIR(6));
				}
				else if(memory_dungeon[u][v] == '<')
				{
					attron(COLOR_PAIR(4));
				}
				else if(memory_dungeon[u][v] == '#')
				{
					attron(COLOR_PAIR(7));
				}
				else if(memory_dungeon[u][v] == '.')
				{
					attron(COLOR_PAIR(11));
				}
				else if(memory_dungeon[u][v] == ' ')
				{
					attron(COLOR_PAIR(1));
				}
				else if(containsItemAt(levelItems, u, v) && check_character_map(u, v) < 0)
				{
					switch(getItemsAt(levelItems, u, v)[0].color)
					{
						case 0:
						attron(COLOR_PAIR(11));
						break;
						case 1:
						attron(COLOR_PAIR(3));
						break;
						case 2:
						attron(COLOR_PAIR(12));
						break;
						case 3:
						attron(COLOR_PAIR(5));
						break;
						case 4:
						attron(COLOR_PAIR(2));
						break;
						case 5:
						attron(COLOR_PAIR(13));
						break;
						case 6:
						attron(COLOR_PAIR(8));
						break;
						case 7:
						attron(COLOR_PAIR(1));
						break;
					}
				}
				else// if(check_character_map(x, y) > 0)
				{
					switch(get_Character_color(get_character_by_id(check_character_map(u, v))))
					{
						case 0:
						attron(COLOR_PAIR(11));
						break;
						case 1:
						attron(COLOR_PAIR(3));
						break;
						case 2:
						attron(COLOR_PAIR(12));
						break;
						case 3:
						attron(COLOR_PAIR(5));
						break;
						case 4:
						attron(COLOR_PAIR(2));
						break;
						case 5:
						attron(COLOR_PAIR(13));
						break;
						case 6:
						attron(COLOR_PAIR(8));
						break;
						case 7:
						attron(COLOR_PAIR(1));
						break;
					}
					//attron(COLOR_PAIR(3));
				}
				mvaddch(v+1, u, memory_dungeon[u][v]);
				if(v == 20)
				{
					attron(COLOR_PAIR(1));
					mvaddch(22, u%playerMessage_len, playerMessage[u%playerMessage_len]);
					attron(COLOR_PAIR(1));
					mvaddch(23, u%monsterMessage_len, monsterMessage[u%monsterMessage_len]);
				}
			}
		}
		
		refresh();
		
	}
	else
	{
		//initscr();
		clear();
		start_color();
		if(game_state == 1)
		{
			init_pair(9, COLOR_BLACK, COLOR_RED);
			attron(COLOR_PAIR(9));
		}
		if(game_state == 2)
		{
			init_pair(11, COLOR_BLACK, COLOR_WHITE);
			attron(COLOR_PAIR(11));
		}
		
		//printw("%s\n", debug_line);
		int d;
		for(d = 0; d < 1701; d++)
		{
			mvaddch(0, d%debug_len, debug_line[d%debug_len]);
			if(d%80 >= debug_len)
			{
				mvaddch(0, d%80, ' ');
			}
			/*if(get_Character_pos(character_list[0]).y == (d/81)+1 && get_Character_pos(character_list[0]).x == d-((d/81)*81) && game_state == 2)
			{
				mvaddch((d/81)+1, d-((d/81)*81), '@');
			}*/
			//else
			{
				mvaddch((d/81)+1, d-((d/81)*81), renderer[d]);
			}
		}
		if(game_state == 1)
		{
			mvprintw(22, 0, "Dr. Sheaffer is dead                                                            \n");
		}
		else if(game_state == 2)
		{
			mvaddch(last_pos.y+1, last_pos.x, '@');
			mvprintw(22, 0, "Dr. Sheaffer cleared the level, but his adventures continue...                  \n");
		}
		refresh();
		const char *exit_message = (game_state == 5)? "Game Saved, press any key to exit                                               " : "Press any key to exit                                                           \n";
		mvprintw(23, 0, exit_message);
		getch();
		//endwin();
		Destroy_Characters();
	}
	
}

void Draw_Monster_List(void)
{
	char monster_info[num_characters-1][80];
	char debug_line[80];
	sprintf(debug_line, "Seed = %d, Input = %d, Monsters alive = %d, Level = %d, HP = %d", seed_state, input, (num_characters - 1) - dead_monsters, level, get_Character_healthPoints(character_list[0]));
	int m, dead_count = 0;
	uint d;
	clear();
	for(d = 0; d < strlen(debug_line); d++)
	{
		mvaddch(0, d, debug_line[d]);
	}
	start_color();
	init_pair(11, COLOR_BLACK, COLOR_WHITE);
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	attron(COLOR_PAIR(11));
	for(m = 1 + scroll_index; (m < num_characters) && (m < 24+scroll_index); m++)
	{
		/*if(m > 23)
		{
			break;
		}*/
		if(get_Character_alive(character_list[m]) == FALSE)
		{
			//mvprintw(m, 0, "                                                                                ");
			dead_count++;
			continue;
		}
		pos_t distance_to_player = {get_Character_pos(character_list[0]).x - get_Character_pos(character_list[m]).x, get_Character_pos(character_list[0]).y - get_Character_pos(character_list[m]).y};
		sprintf(monster_info[m-1], "%c: is %d %s and %d %s = %s, hp=%d", get_Character_symbol(character_list[m]), (distance_to_player.x > 0)? distance_to_player.x : distance_to_player.x*-1,(distance_to_player.x > 0) ? "west" : "east", (distance_to_player.y > 0)? distance_to_player.y : distance_to_player.y*-1,(distance_to_player.y > 0) ? "north" : "south", get_Character_name(character_list[m]).c_str(), get_Character_healthPoints(character_list[m]));
		uint c;
		for(c = 0; c < strlen(monster_info[m-1]); c++)
		{
			mvaddch(m - dead_count - scroll_index, c, monster_info[m-1][c]);
		}
		int l;
		for(l = strlen(monster_info[m-1]); l < 80; l++)
		{
			mvaddch(m - dead_count - scroll_index, l, ' ');
		}
	}
	if(m < 24)
	{
		for(; m < 24; m++)
		{
			mvprintw(m, 0, "                                                                                ");
		}
	}
	attron(COLOR_PAIR(1));
	refresh();
}

void Draw_Equipment(void)
{
	char debug_line[80];
	sprintf(debug_line, "Seed = %d, Input = %d, Monsters alive = %d, Level = %d, HP = %d", seed_state, input, (num_characters - 1) - dead_monsters, level, get_Character_healthPoints(character_list[0]));
	uint d, e;
	for(d = 0; d < strlen(debug_line); d++)
	{
		mvaddch(0, d, debug_line[d]);
	}
	mvprintw(4, 19, "+----------------------------------------+");
	mvprintw(5, 19, "|             Equipment List             |");
	mvprintw(6, 19, "|a:                                      |");
	mvprintw(7, 19, "|b:                                      |");
	mvprintw(8, 19, "|c:                                      |");
	mvprintw(9, 19, "|d:                                      |");
	mvprintw(10, 19, "|e:                                      |");
	mvprintw(11, 19, "|f:                                      |");
	mvprintw(12, 19, "|g:                                      |");
	mvprintw(13, 19, "|h:                                      |");
	mvprintw(14, 19, "|i:                                      |");
	mvprintw(15, 19, "|j:                                      |");
	mvprintw(16, 19, "|k:                                      |");
	mvprintw(17, 19, "|l:                                      |");
	mvprintw(18, 19, "+----------------------------------------+");
	itemClass equipment;
	for(d = 0; d < 12; d++)
	{
		equipment = get_Player_equipment((player_t *) character_list[0], d);
		for(e = 23; (e - 23) < equipment.name.size() && e < 60; e++)
		{
			//mvprintw(d + 6, e, equipment.name.c_str());
			mvaddch(d + 6, e, (equipment.name.c_str())[e-23]);
		}
		
	}
}

void Draw_Inventory(void)
{
	char debug_line[80];
	sprintf(debug_line, "Seed = %d, Input = %d, Monsters alive = %d, Level = %d, HP = %d", seed_state, input, (num_characters - 1) - dead_monsters, level, get_Character_healthPoints(character_list[0]));
	uint d, e;
	for(d = 0; d < strlen(debug_line); d++)
	{
		mvaddch(0, d, debug_line[d]);
	}
	mvprintw(4, 19, "+----------------------------------------+");
	mvprintw(5, 19, "|             Inventory List             |");
	mvprintw(6, 19, "|0:                                      |");
	mvprintw(7, 19, "|1:                                      |");
	mvprintw(8, 19, "|2:                                      |");
	mvprintw(9, 19, "|3:                                      |");
	mvprintw(10, 19, "|4:                                      |");
	mvprintw(11, 19, "|5:                                      |");
	mvprintw(12, 19, "|6:                                      |");
	mvprintw(13, 19, "|7:                                      |");
	mvprintw(14, 19, "|8:                                      |");
	mvprintw(15, 19, "|9:                                      |");
	mvprintw(16, 19, "+----------------------------------------+");
	itemClass inventory;
	for(d = 0; d < 10; d++)
	{
		inventory = get_Player_item((player_t *) character_list[0], d);
		for(e = 23; (e - 23) < inventory.name.size() && e < 60; e++)
		{
			//mvprintw(d + 6, e, inventory.name.c_str());
			mvaddch(d + 6, e, (inventory.name.c_str())[e-23]);
		}
		
	}
}

void Draw_Carry_Slot_Dialog(void)
{
	char debug_line[80];
	sprintf(debug_line, "Seed = %d, Input = %d, Monsters alive = %d, Level = %d, HP = %d", seed_state, input, (num_characters - 1) - dead_monsters, level, get_Character_healthPoints(character_list[0]));
	uint d;
	for(d = 0; d < strlen(debug_line); d++)
	{
		mvaddch(0, d, debug_line[d]);
	}
	string dialogType = " ";
	string dialogMessage = " ";
	switch(input)
	{
		case 18:
			dialogType = "Which item to wear?";
			dialogMessage = "Select an inventory slot between 0 - 9";
		break;
		
		case 19:
			dialogType = "Which item to drop?";
			dialogMessage = "Select an inventory slot between 0 - 9";
		break;
		
		case 20:
			dialogType = "Which item to expunge?";
			dialogMessage = "Select an inventory slot between 0 - 9";
		break;
		
		case 21:
			dialogType = "Which item to inspect?";
			dialogMessage = "Select an inventory slot between 0 - 9";
		break;
		
		case 22:
			dialogType = "Which equipment to take off?";
			dialogMessage = "Select an equipment slot between a - l";
		break;
	}
	mvprintw(10, 19, "+----------------------------------------+");
	mvprintw(11, 19, "|                                        |");
	mvprintw(12, 19, "|                                        |");
	mvprintw(13, 19, "+----------------------------------------+");
	
	mvprintw(11, ((40 - dialogType.size())/2) + 20, dialogType.c_str() );
	mvprintw(12, 21, dialogMessage.c_str());
}

void Draw_Item_Desc(itemClass itemForDesc)
{
	string desc = itemForDesc.description;
	vector<int> positions;
	uint nLine;
	for(nLine = 0; nLine < desc.length(); nLine++)
	{
		if(desc[nLine] == '\n')
		{
			positions.push_back(nLine);
		}
	}
	
	//sprintf(playerMessage, "Size = %s", nLine);
	int yStart = ((21 - (positions.size()+3))/2)+1;
	mvprintw(yStart, 0, "+------------------------------------------------------------------------------+");
	mvprintw(yStart + 1, 0, "|                                                                              |");
	mvprintw(yStart + 1, 1, itemForDesc.name.c_str());
	uint dIndex, startIndex = 0;
	for(dIndex = 0; dIndex < positions.size(); dIndex++)
	{
		mvprintw(yStart + dIndex + 2, 0, "|                                                                              |");
		mvprintw(yStart + dIndex + 2, 1, itemForDesc.description.substr(startIndex, positions[dIndex]).c_str());
		startIndex = positions[dIndex] + 1;
	}
	mvprintw(yStart + dIndex + 2, 0, "+------------------------------------------------------------------------------+");
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

void remember_dungeon(pos_t player_position)
{
	int x, y;
	for(y = -3; y <= 3; y++)
	{
		for(x = -3; x <= 3; x++)
		{
			if((player_position.x + x) < 80 && (player_position.x + x) > -1 && (player_position.y + y) < 21 && (player_position.y + y) > -1)
			{
				if(check_character_map(player_position.x + x, player_position.y + y) > 0 && get_Character_alive(get_character_by_id(check_character_map(player_position.x + x, player_position.y + y))) == TRUE)
				{
					memory_dungeon[player_position.x + x][player_position.y + y] = get_Character_symbol(get_character_by_id(check_character_map(player_position.x + x, player_position.y + y)));
					/*switch(get_Monster_abilities((monster_t *)get_character_by_id(check_character_map(player_position.x + x, player_position.y + y))))
					{
						case 0x0:
							memory_dungeon[player_position.x + x][player_position.y + y] = '0';
						break;
						
						case 0x1:
							memory_dungeon[player_position.x + x][player_position.y + y] = '1';
						break;
						
						case 0x2:
							memory_dungeon[player_position.x + x][player_position.y + y] = '2';
						break;
						
						case 0x3:
							memory_dungeon[player_position.x + x][player_position.y + y] = '3';
						break;
						
						case 0x4:
							memory_dungeon[player_position.x + x][player_position.y + y] = '4';
						break;
						
						case 0x5:
							memory_dungeon[player_position.x + x][player_position.y + y] = '5';
						break;
						
						case 0x6:
							memory_dungeon[player_position.x + x][player_position.y + y] = '6';
						break;
						
						case 0x7:
							memory_dungeon[player_position.x + x][player_position.y + y] = '7';
						break;
						
						case 0x8:
							memory_dungeon[player_position.x + x][player_position.y + y] = '8';
						break;
						
						case 0x9:
							memory_dungeon[player_position.x + x][player_position.y + y] = '9';
						break;
						
						case 0xa:
							memory_dungeon[player_position.x + x][player_position.y + y] = 'a';
						break;
						
						case 0xb:
							memory_dungeon[player_position.x + x][player_position.y + y] = 'b';
						break;
						
						case 0xc:
							memory_dungeon[player_position.x + x][player_position.y + y] = 'c';
						break;
						
						case 0xd:
							memory_dungeon[player_position.x + x][player_position.y + y] = 'd';
						break;
						
						case 0xe:
							memory_dungeon[player_position.x + x][player_position.y + y] = 'e';
						break;
						
						case 0xf:
							memory_dungeon[player_position.x + x][player_position.y + y] = 'f';
						break;
					}*/
				}
				else if(containsItemAt(levelItems, player_position.x + x, player_position.y + y))
				{
					vector<itemClass> itemsHere = getItemsAt(levelItems, player_position.x + x, player_position.y + y);
					if(itemsHere.size() > 1)
					{
						memory_dungeon[player_position.x + x][player_position.y + y] = '&';
					}
					else
					{
						memory_dungeon[player_position.x + x][player_position.y + y] = itemsHere[0].symbol;
					}
				}
				else
				{
					switch(current_dungeon[player_position.x + x][player_position.y + y].space_type)
					{
						case ROCK:
							memory_dungeon[player_position.x + x][player_position.y + y] = ' ';
						break;
						
						case ROOM:
							if(stair_set[0].location.x == player_position.x + x && stair_set[0].location.y == player_position.y + y)
							{
								memory_dungeon[player_position.x + x][player_position.y + y] = '>';
							}
							else if(level > 0 && stair_set[1].location.x == player_position.x + x && stair_set[1].location.y == player_position.y + y)
							{
								memory_dungeon[player_position.x + x][player_position.y + y] = '<';
							}
							else
							{
								memory_dungeon[player_position.x + x][player_position.y + y] = '.';
							}
						break;
						
						case CORRIDOR:
							if(stair_set[0].location.x == player_position.x + x && stair_set[0].location.y == player_position.y + y)
							{
								memory_dungeon[player_position.x + x][player_position.y + y] = '>';
							}
							else if(level > 0 && stair_set[1].location.x == player_position.x + x && stair_set[1].location.y == player_position.y + y)
							{
								memory_dungeon[player_position.x + x][player_position.y + y] = '<';
							}
							else
							{
								memory_dungeon[player_position.x + x][player_position.y + y] = '#';
							}
						break;
					}
				}
			}
		}
	}
	memory_dungeon[player_position.x][player_position.y] = '@';
	
	for(y = 0; y < 21; y++)
	{
		for(x = 0; x < 80; x++)
		{
			if(current_dungeon[x][y].space_union.rock.density == 255)
			{
				memory_dungeon[x][y] = '~';
			}
			/*if((player_position.x - x >=3 || player_position.x - x <=-3) || (player_position.y - y >=3 || player_position.y - y <=-3))
			{
				
			}*/
			if(memory_dungeon[x][y] != '@' && memory_dungeon[x][y] != '.' && memory_dungeon[x][y] != '#' && memory_dungeon[x][y] != ' ' && memory_dungeon[x][y] != '>' && memory_dungeon[x][y] != '<' && memory_dungeon[x][y] != '~'
				&& ((player_position.x - x >3 || player_position.x - x <-3) || (player_position.y - y >3 || player_position.y - y <-3)))
				{
					memory_dungeon[x][y] = (current_dungeon[x][y].space_type == ROOM) ? '.' : '#';
				}
		}
	}
}

int turn(int *seed, int num_mon)
{
	int r, q;
	for(q = 0;q < 21; q++)
	{
		for(r = 0; r < 80; r++)
		{
			memory_dungeon[r][q] = ' ';
		}
	}
	
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
		/*nodes[p] = */binheap_insert(&h, *(character_list + get_character_index_by_id(p))/*character_list + p*/);
	}
	line_of_sight(current_dungeon);
	while(!binheap_is_empty(&h))
	{
		character_t *current = (character_t *) binheap_remove_min(&h);
		
		pos_t moving_to = {0, 0};
		
		if(get_Character_character_type(current) == PLAYER)
		{
			remember_dungeon(get_Character_pos(current));
			if(get_Character_alive(character_list[0]) == FALSE)
			{
				//printf("Player is dead\n");
				game_state = 1;
				free(distance_dungeon);
				free(distance_dungeon_tunneler);
				break;
			}
			if(dead_monsters == num_characters - 1)
			{
				last_pos.x = get_Character_pos(character_list[0]).x;
				last_pos.y = get_Character_pos(character_list[0]).y;
				free(distance_dungeon);
				free(distance_dungeon_tunneler);
				//printf("The drunk player wins!\n");
				game_state = 2;
				break;
			}
			if(game_state == 3 || game_state == 5)
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
			distance_dungeon = Generate_Distance_Dungeon((boolean) FALSE);
			//Draw_Distance_Dungeon(distance_dungeon);
			set_distance(distance_dungeon);
			if(game_state != 4)
			{
				free(distance_dungeon_tunneler);
				Destroy_Graph(&graphed_dungeon);
			}
			distance_dungeon_tunneler = Generate_Distance_Dungeon((boolean) TRUE);
			set_distance_tunneler(distance_dungeon_tunneler);
			if(game_state == 4)
			{
				dead_monsters = 0;
				num_characters = num_mon+1;
				game_state = 0;
			}
			update_telepath();
			line_of_sight(current_dungeon);
			if(containsItemAt(levelItems, get_Character_pos(current).x, get_Character_pos(current).y))
			{
				vector<itemClass> itemsHere = getItemsAt(levelItems, get_Character_pos(current).x, get_Character_pos(current).y);
				string nameOfItem = "Inventory is full";
				uint itemInvariant;
				for(itemInvariant = 0; itemInvariant < 10; itemInvariant++)
				{
					itemClass itemInInventory = get_Player_item((player_t *) current, itemInvariant);
					if(itemInInventory.type == objtype_no_type && itemsHere.size() > 0)
					{
						nameOfItem = "Picked up " + itemsHere[0].name;
						set_Player_item((player_t *) current, itemsHere[0], itemInvariant);
						removeItemAt(&levelItems, get_Character_pos(current).x, get_Character_pos(current).y, itemsHere[0].name);
						itemsHere.erase(itemsHere.begin());
						//break;
					}
					
				}
				sprintf(playerMessage, "%s ", nameOfItem.c_str());
			}
			Draw_Dungeon(1);
			//sleep(3);
			define_new_keys();
			input = -1;
			while(input < 0 && game_state != 3 && game_state !=5)
			{
				input = input_handler(getch());
				if(input < 9)
				{
					moving_to = get_direction((command_t) input);
				}
				if(input == 13 || input == 14)
				{
					if(input == 13 && get_Character_pos(character_list[0]).x == stair_set[0].location.x && get_Character_pos(character_list[0]).y == stair_set[0].location.y)
					{
						level++;
						stair_player = DOWNSTAIRS;
						game_state = 3;
					}
					else if(level > 0 && input == 14 && get_Character_pos(character_list[0]).x == stair_set[1].location.x && get_Character_pos(character_list[0]).y == stair_set[1].location.y)
					{
						level--;
						stair_player = UPSTAIRS;
						game_state = 3;
					}
				}
				/*while(input == 9)
				{
					Draw_Monster_List();
					int menu_input = input_handler(getch());
					if(menu_input == ESCAPE)
					{
						Draw_Dungeon(1);
						input = input_handler(getch());
						if(input < 9)
						{
							moving_to = get_direction((command_t) input);
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
				while(input == 16)
				{
					Draw_Equipment();
					int menu_input = input_handler(getch());
					if(menu_input == ESCAPE)
					{
						Draw_Dungeon(1);
						input = input_handler(getch());
						if(input < 9)
						{
							moving_to = get_direction((command_t) input);
						}
						if(input == 16)
						{
							continue;
						}
						break;
					}
				}
				while(input == 17)
				{
					Draw_Inventory();
					int menu_input = input_handler(getch());
					if(menu_input == ESCAPE)
					{
						Draw_Dungeon(1);
						input = input_handler(getch());
						if(input < 9)
						{
							moving_to = get_direction((command_t) input);
						}
						if(input == 17)
						{
							continue;
						}
						break;
					}
				}*/
				if(input == 16 || input == 17 || input == 9 || input == 18 || input == 19 || input == 20 || input == 21 || input == 22)
				{
					input = menu_helper(input, input, &moving_to);
				}
				if(input == 15)
				{
					game_state = 5;
				}
				if(input > 8)
				{
					input = -1;
				}
			}
		}
		
		if(game_state != 3 && game_state != 5)
		{
			string moveMessage = move_character(get_Character_id(current), seed, current_dungeon, moving_to);
			if(get_Character_character_type(current) == PLAYER)
			{
				sprintf(playerMessage, "%s",  moveMessage.c_str());
				if(moveMessage.find("kills") != string::npos)
				{
					sprintf(monsterMessage, "%s",  " ");
				}
			}
			else if(moveMessage.compare(" ") != 0)
			{
				sprintf(monsterMessage, "%s ",  moveMessage.c_str());
			}
		}
		set_Character_timer(current, get_Character_timer(current)+(100/get_Character_speed(current)));
		/*nodes[p] = */binheap_insert(&h, current);
	}
	
	if(game_state != 1 && game_state != 2 && game_state != 5)
	{
		Destroy_Characters();
	}
	//Destroy_All();
	binheap_delete(&h);
	return level;
}

int menu_helper(int menu_type, int commandInput, pos_t *moving_to)
{
	input = commandInput;
	while(commandInput == menu_type)
	{
		if(menu_type == 16)
		{
			Draw_Equipment();
		}
		else if(menu_type == 17)
		{
			Draw_Inventory();
		}
		else if(menu_type == 9)
		{
			Draw_Monster_List();
		}
		else if(menu_type >= 18 && menu_type <= 22)
		{
			Draw_Carry_Slot_Dialog();
		}
		int dialogInput = getch();
		int menu_input = input_handler(dialogInput);
		if(menu_input == ESCAPE)
		{
			Draw_Dungeon(1);
			commandInput = input_handler(getch());
			if(commandInput < 9)
			{
				*moving_to = get_direction((command_t) commandInput);
			}
			if(commandInput == menu_type)
			{
				continue;
			}
			if(commandInput == 16 || commandInput == 17 || commandInput == 9 || commandInput == 18 || commandInput == 19 || commandInput == 20 || commandInput == 21 || commandInput == 22)
			{
					commandInput = menu_helper(commandInput, commandInput, moving_to);
			}
			break;
		}
		else if(menu_type == 9 && ((num_characters - 1)- dead_monsters > 23 && ((menu_input == 12 && ((num_characters - 1)- dead_monsters) - scroll_index > 23) || (menu_input == 11 && scroll_index > 0))))
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
		else if(menu_type == 18 && (dialogInput - 48) >= 0 && (dialogInput - 48) <= 9)
		{
			wear_helper(dialogInput - 48);
			Draw_Dungeon(1);
			break;
		}
		else if(menu_type == 19 && (dialogInput - 48) >= 0 && (dialogInput - 48) <= 9)
		{
			drop_helper(dialogInput - 48);
			Draw_Dungeon(1);
			break;
		}
		else if(menu_type == 20 && (dialogInput - 48) >= 0 && (dialogInput - 48) <= 9)
		{
			expunge_helper(dialogInput - 48);
			Draw_Dungeon(1);
			break;
		}
		else if(menu_type == 21 && (dialogInput - 48) >= 0 && (dialogInput - 48) <= 9)
		{
			Draw_Dungeon(1);
			Draw_Item_Desc(get_Player_item((player_t *) character_list[0], dialogInput - 48));
		}
		else if(menu_type == 22 && (dialogInput - 97) >= 0 && (dialogInput - 97) <= 11)
		{
			take_off_helper(dialogInput - 97);
			Draw_Dungeon(1);
			break;
		}
	}
	return commandInput;
}

bool wear_helper(int slot)
{
	itemClass itemToWear = get_Player_item((player_t *) character_list[0], slot);
	if(itemToWear.type == objtype_no_type || !itemToWear.equipment)
	{
		sprintf(playerMessage, "Cannot equip %s", itemToWear.name.c_str());
		return false;
	}
	int equipIndex = 0;
	switch(itemToWear.type)
	{
		case objtype_WEAPON:
			equipIndex = 0;
		break;
		
		case objtype_OFFHAND:
			equipIndex = 1;
		break;
		
		case objtype_RANGED:
			equipIndex = 2;
		break;
		
		case objtype_ARMOR:
			equipIndex = 3;
		break;
		
		case objtype_HELMET:
			equipIndex = 4;
		break;
		
		case objtype_CLOAK:
			equipIndex = 5;
		break;
		
		case objtype_GLOVES:
			equipIndex = 6;
		break;
		
		case objtype_BOOTS:
			equipIndex = 7;
		break;
		
		case objtype_AMULET:
			equipIndex = 8;
		break;
		
		case objtype_LIGHT:
			equipIndex = 9;
		break;
		
		case objtype_RING:
			equipIndex = 10;
		break;
		
		default:
			return false;
		break;
	}
	
	itemClass equipToReplace = get_Player_equipment((player_t *) character_list[0], equipIndex);
	if(equipToReplace.type == objtype_no_type)
	{
		set_Player_equipment((player_t *) character_list[0], itemToWear, equipIndex);
		set_Player_item((player_t *) character_list[0], itemClass(), slot);
	}
	else
	{
		if(equipToReplace.type == objtype_RING && (get_Player_equipment((player_t *) character_list[0], equipIndex+1)).type == objtype_no_type)
		{
			set_Player_equipment((player_t *) character_list[0], itemToWear, equipIndex+1);
			set_Player_item((player_t *) character_list[0], itemClass(), slot);
		}
		else if(equipToReplace.type == objtype_RING)
		{
			itemClass ringTemp = get_Player_equipment((player_t *) character_list[0], equipIndex+1);
			set_Player_equipment((player_t *) character_list[0], ringTemp, equipIndex);
			set_Player_item((player_t *) character_list[0], equipToReplace, slot);
			set_Player_equipment((player_t *) character_list[0], itemToWear, equipIndex+1);
		}
		else
		{
			set_Player_item((player_t *) character_list[0], equipToReplace, slot);
			set_Player_equipment((player_t *) character_list[0], itemToWear, equipIndex);
		}
	}
	sprintf(playerMessage, "Equipped %s", itemToWear.name.c_str());
	return true;
}

bool take_off_helper(int slot)
{
	itemClass equipTakeOff = get_Player_equipment((player_t *) character_list[0], slot);
	if(equipTakeOff.type == objtype_no_type)
	{
		sprintf(playerMessage, "Slot %c is empty", slot+97);
		return false;
	}
	int inventoryItems;
	for(inventoryItems = 0; inventoryItems < 10; inventoryItems++)
	{
		if((get_Player_item((player_t *) character_list[0], inventoryItems)).type == objtype_no_type)
		{
			break;
		}
	}
	if(inventoryItems == 10)
	{
		sprintf(playerMessage, "%s ", "Inventory is full");
		return false;
	}
	
	set_Player_item((player_t *) character_list[0], equipTakeOff, inventoryItems);
	set_Player_equipment((player_t *) character_list[0], itemClass(), slot);
	sprintf(playerMessage, "Took off %s ", equipTakeOff.name.c_str());
	return true;
}

bool drop_helper(int slot)
{
	itemClass itemToDrop = get_Player_item((player_t *) character_list[0], slot);
	if(itemToDrop.type == objtype_no_type)
	{
		sprintf(playerMessage, "%s ", "Cannot drop an empty slot");
		return false;
	}
	set_Player_item((player_t *) character_list[0], itemClass(), slot);
	drop_itemAt(&levelItems, itemToDrop, get_Character_pos(character_list[0]).x, get_Character_pos(character_list[0]).y);
	sprintf(playerMessage, "Dropped %s", itemToDrop.name.c_str());
	return true;
}

bool expunge_helper(int slot)
{
	itemClass itemToDrop = get_Player_item((player_t *) character_list[0], slot);
	if(itemToDrop.type == objtype_no_type)
	{
		sprintf(playerMessage, "%s ", "Cannot expunge an empty slot");
		return false;
	}
	set_Player_item((player_t *) character_list[0], itemClass(), slot);
	sprintf(playerMessage, "Expunged %s", itemToDrop.name.c_str());
	return true;
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
		
		//SAVE_QUIT
		case 83:
			return SAVE_QUIT;
		break;
		
		//Equipment Menu
		case 69:
			return EQUIPMENT;
		break;
		
		//Inventory Menu
		case 73:
			return INVENTORY;
		break;
		
		//WEAR
		case 87:
			return WEAR;
		break;
		
		//DROP
		case 68:
			return DROP;
		break;
		
		//EXPUNGE
		case 120:
			return EXPUNGE;
		break;
		
		//INSPECT
		case 105:
			return INSPECT;
		break;
		
		//TAKE_OFF
		case 116:
			return TAKE_OFF;
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