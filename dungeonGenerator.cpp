#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "dungeonObjects.h"
#include "dungeonRoomGenerator.h"
#include "dungeonLevelGenerator.h"
#include "dungeonIO.h"
#include "GameStateManager.h"
#include "CharacterController.h"
#include "MonsterParser.h"
#include "ObjectParser.h"

boolean isstring(char *string);

char *dungeonFolder;
Dungeon_Space_Struct **dungeon;


int main(int argc, char *argv[])
{
	time_t seed;
	Flags flags[argc - 1];
	char *dungeonFileName;
	char *dungeonSaveFileName;
	boolean load_param = (boolean) FALSE;
	boolean save_param = (boolean) FALSE;
	boolean nummon_param = (boolean) FALSE;
	int nummon_value = 0;
	boolean loaded = (boolean) FALSE;
	boolean save_param_used = (boolean) FALSE;
	int num_rooms;
	vector<monsterClass> monsterList;
	vector<objectClass> objectList;
	
	if(argc >= 2)
	{
		int c;
		for(c = 1; c < argc; c++)
		{
			if(load_param == TRUE)
			{
				flags[c - 1] = LOAD;
				load_param = (boolean) FALSE;
				continue;
			}
			if(save_param == TRUE)
			{
				flags[c - 1] = SAVE;
				save_param = (boolean) FALSE;
				continue;
			}
			if(nummon_param == TRUE)
			{
				flags[c - 1] = NUMMON;
				nummon_param = (boolean) FALSE;
				continue;
			}
			
			if(isstring(argv[c]) == FALSE)
			{
				seed = atoi(argv[c]);
				flags[c - 1] = SEED;
			}
			else if(strstr(argv[c], "--") != NULL)
			{
				if(strcmp(argv[c], "--save") == 0)
				{
					if(((c + 1) < argc) && strstr(argv[c + 1], "--") == NULL && isstring(argv[c + 1]) == TRUE)
					{
						dungeonSaveFileName = strdup(argv[c + 1]);
						save_param = (boolean) TRUE;
						save_param_used = (boolean) TRUE;
					}
					else
					{
						
						dungeonSaveFileName = strdup("dungeon");
					}
					flags[c - 1] = SAVE;
				}
				else if(strcmp(argv[c], "--load") == 0)
				{
					if(((c + 1) < argc) && strstr(argv[c + 1], "--") == NULL && isstring(argv[c + 1]) == TRUE)
					{
						dungeonFileName = strdup(argv[c + 1]);
						load_param = (boolean) TRUE;
					}
					else
					{
						
						dungeonFileName = strdup("dungeon");
					}
					flags[c - 1] = LOAD;
				}
				else if(strcmp(argv[c], "--nummon") == 0)
				{
					if(((c + 1) < argc) && strstr(argv[c + 1], "--") == NULL && isstring(argv[c + 1]) == FALSE)
					{
						nummon_param = (boolean) TRUE;
						nummon_value = atoi(argv[c+1]);
					}
					else
					{
						printf("Invalid parameter for --nummon\n");
						return 0;
					}
					flags[c - 1] = NUMMON;
				}
				else if(strcmp(argv[c], "--parsemon") == 0)
				{
					monsterList = parseMonsters();
					uint ml;
					for(ml = 0; ml < monsterList.size(); ml++)
					{
						cout << monsterList[ml].name << endl;
						cout << monsterList[ml].description;
						cout << monsterList[ml].symbol << endl;
						switch(monsterList[ml].color)
						{
								case 0:
								cout << "BLACK" << endl;
								break;
								case 1:
								cout << "RED" << endl;
								break;
								case 2:
								cout << "GREEN" << endl;
								break;
								case 3:
								cout << "YELLOW" << endl;
								break;
								case 4:
								cout << "BLUE" << endl;
								break;
								case 5:
								cout << "MAGENTA" << endl;
								break;
								case 6:
								cout << "CYAN" << endl;
								break;
								case 7:
								cout << "WHITE" << endl;
								break;
						}
						cout << monsterList[ml].speedDice.toString() << endl;
						//printf("Monster ability is 0x%x\n", monsterList[ml].get_abilities());
						if((monsterList[ml].get_abilities() & 0b00001) == 0b00001)
						{
							cout << "SMART ";
						}
						if((monsterList[ml].get_abilities() & 0b00010) == 0b00010)
						{
							cout << "TELE ";
						}
						if((monsterList[ml].get_abilities() & 0b00100) == 0b00100)
						{
							cout << "TUNNEL ";
						}
						if((monsterList[ml].get_abilities() & 0b01000 )== 0b01000)
						{
							cout << "ERRATIC ";
						}
						if((monsterList[ml].get_abilities() & 0b10000 )== 0b10000)
						{
							cout << "PASS ";
						}
						cout << endl;
						cout << monsterList[ml].hp.toString() << endl;
						cout << monsterList[ml].damage.toString() << endl << endl;
					}
					flags[c - 1] = PARSEMON;
					//return 0;
				}
				else if(strcmp(argv[c], "--parseobj") == 0)
				{
					objectList = parseObjects();
					uint ol;
					for(ol = 0; ol < objectList.size(); ol++)
					{
						cout << objectList[ol].name << endl;
						cout << objectList[ol].description << endl;
						switch(objectList[ol].type)
						{
							case objtype_no_type:
								cout << "no type" << endl;
							break;
							
							case objtype_WEAPON:
								cout << "WEAPON" << endl;
							break;
							
							case objtype_OFFHAND:
								cout << "OFFHAND" << endl;
							break;
							
							case objtype_RANGED:
								cout << "RANGED" << endl;
							break;
							
							case objtype_LIGHT:
								cout << "LIGHT" << endl;
							break;
							
							case objtype_ARMOR:
								cout << "ARMOR" << endl;
							break;
							
							case objtype_HELMET:
								cout << "HELMET" << endl;
							break;
							
							case objtype_CLOAK:
								cout << "CLOAK" << endl;
							break;
							
							case objtype_GLOVES:
								cout << "GLOVES" << endl;
							break;
							
							case objtype_BOOTS:
								cout << "BOOTS" << endl;
							break;
							
							case objtype_AMULET:
								cout << "AMULET" << endl;
							break;
							
							case objtype_RING:
								cout << "RING" << endl;
							break;
							
							case objtype_SCROLL:
								cout << "SCROLL" << endl;
							break;
							
							case objtype_BOOK:
								cout << "BOOK" << endl;
							break;
							
							case objtype_FLASK:
								cout << "FLASK" << endl;
							break;
								
							case objtype_GOLD:
								cout << "GOLD" << endl;
							break;
							
							case objtype_AMMUNITION:
								cout << "AMMUNITION" << endl;
							break;
							
							case objtype_FOOD:
								cout << "FOOD" << endl;
							break;
							
							case objtype_WAND:
								cout << "WAND" << endl;
							break;
							
							case objtype_CONTAINER:
								cout << "CONTAINER" << endl;
							break;
						}
						switch(objectList[ol].color)
						{
								case 0:
								cout << "BLACK" << endl;
								break;
								case 1:
								cout << "RED" << endl;
								break;
								case 2:
								cout << "GREEN" << endl;
								break;
								case 3:
								cout << "YELLOW" << endl;
								break;
								case 4:
								cout << "BLUE" << endl;
								break;
								case 5:
								cout << "MAGENTA" << endl;
								break;
								case 6:
								cout << "CYAN" << endl;
								break;
								case 7:
								cout << "WHITE" << endl;
								break;
								case -1:
								cout << "no color" << endl;
								break;
						}
						cout << "hit: " << objectList[ol].hit.toString() << endl;
						cout << "damage: " << objectList[ol].damage.toString() << endl;
						cout << "dodge: " << objectList[ol].dodge.toString() << endl;
						cout << "defence: " << objectList[ol].defence.toString() << endl;
						cout << "weight: " << objectList[ol].weight.toString() << endl;
						cout << "speed: " << objectList[ol].speed.toString() << endl;
						cout << "attribute: " << objectList[ol].attribute.toString() << endl;
						cout << "value: " << objectList[ol].value.toString() << endl << endl;
					}
					return 0;
				}
				else
				{
					printf("Invalid argument %s\n", argv[c]);
					return 0;
				}
			}
			else
			{
				printf("Invalid argument %s\n", argv[c]);
				return 0;
			}
		}
	}

	if(Contains_Flag(flags, (argc - 1), SEED) == TRUE && Contains_Flag(flags, (argc - 1), LOAD) == TRUE)
	{
		printf("Usage for load: ./dungeonGenerator --load <optional file name>\n");
		printf("Usage for load/save: ./dungeonGenerator --load <optional file name> --save <optional file name>\n");
		printf("File name cannot be numbers only. Read README for details\n");
		return 0;
	}
	else if(Contains_Flag(flags, (argc - 1), SEED) == FALSE && Contains_Flag(flags, (argc - 1), LOAD) == FALSE)
	{
		seed = time(NULL);
	}
	
	dungeonFolder = strcat(getenv("HOME"), "/.rlg327/");
	
	if(Contains_Flag(flags, (argc - 1), LOAD) == TRUE)
	{
		//int null_seed = -1;
		strcat(dungeonFolder, dungeonFileName);
		//printf("dungeonFile = %s\n", dungeonFile);
		if(access(dungeonFolder, F_OK) == -1)
		{
			if (errno == ENOENT) 
			{
				printf ("%s does not exist\n", dungeonFolder);
			}
			else if (errno == EACCES) 
			{
				printf ("%s is not accessible\n", dungeonFolder);
			}
			return 0;
		}
		if((dungeon = Load_Dungeon(dungeonFolder, &num_rooms)) == NULL)
		{
			printf("Failed to load dungeon\n");
			return 0;
		}
		/*Set_Dungeon(dungeon);
		//player_t player;
		//player.cell = dungeon[18][4];
		//player.pos.x = 18;
		//player.pos.y = 4;
		Set_Player(Place_Player(dungeon, &null_seed));
		Draw_Dungeon(0);
		printf("\n");
		distance_dungeon = Generate_Distance_Dungeon(FALSE);
		Draw_Distance_Dungeon(distance_dungeon);
		Destroy_All();
		printf("\n");
		distance_dungeon_tunneler = Generate_Distance_Dungeon(TRUE);
		Draw_Distance_Dungeon(distance_dungeon_tunneler);
		loaded = TRUE;
		Destroy_All();*/
		
		seed = time(NULL);
		srand(seed);
		int int_seed = seed;
		int level = 0;
		//int stair_used = -1;
		
		initscr();
		raw();
		noecho();
		curs_set(0);
		keypad(stdscr, 1);
		while(game_state == 0 || game_state == 3)
		{
			if(game_state == 3)
			{
				seed = time(NULL);
				srand(seed);
				int_seed = seed;
				game_state = 4;
			}
			if (game_state != 0)
			{
				dungeon = Generate_Map(&int_seed, &num_rooms);
			}
			Set_Dungeon(dungeon);
			character_t *player_to_set = Place_Player(dungeon, &int_seed);
			//Set_Player(player_to_set);
			Set_Debug_Info(int_seed, num_rooms);
			populate_monsters(nummon_value, &int_seed, monsterList);
			stair_t down;
			if(stair_player == UPSTAIRS)
			{
				down.location.x = get_Character_pos(player_to_set).x;
				down.location.y = get_Character_pos(player_to_set).y;
				down.direction = DOWNSTAIRS;
			}
			else 
			{
				down = Place_Stairs(dungeon, &int_seed, DOWNSTAIRS);
				while(level > 0 && down.location.x == get_Character_pos(player_to_set).x && down.location.y == get_Character_pos(player_to_set).y)
					{
						down = Place_Stairs(dungeon, &int_seed, DOWNSTAIRS);
					}
			}
			Set_Stairs(down);
			if(level > 0)
			{
				stair_t up;
				if(stair_player == DOWNSTAIRS)
				{
					up.location.x = get_Character_pos(player_to_set).x;
					up.location.y = get_Character_pos(player_to_set).y;
					up.direction = UPSTAIRS;
				}
				else 
				{
					up = Place_Stairs(dungeon, &int_seed, UPSTAIRS);
					while(down.location.x == up.location.x && down.location.y == up.location.y)
					{
						up = Place_Stairs(dungeon, &int_seed, UPSTAIRS);
					}
				}
				Set_Stairs(up);
			}
			//Draw_Dungeon(1);
			//printf("\n");
			//distance_dungeon = Generate_Distance_Dungeon(FALSE);
			//Draw_Distance_Dungeon(distance_dungeon);
			//Destroy_All();
			//printf("\n");
			//distance_dungeon_tunneler = Generate_Distance_Dungeon(TRUE);
			level = turn(&int_seed, nummon_value);
			
			//Draw_Distance_Dungeon(distance_dungeon_tunneler);
			Destroy_All();
		}
		Draw_Dungeon(0);
		endwin();
	}
	else
	{
		srand(seed);
		
		int int_seed = seed;
		int level = 0;
		//int stair_used = -1;
		
		initscr();
		raw();
		noecho();
		curs_set(0);
		keypad(stdscr, 1);
		while(game_state == 0 || game_state == 3)
		{
			if(game_state == 3)
			{
				seed = time(NULL);
				srand(seed);
				int_seed = seed;
				game_state = 4;
			}
			dungeon = Generate_Map(&int_seed, &num_rooms);
			Set_Dungeon(dungeon);
			character_t *player_to_set = Place_Player(dungeon, &int_seed);
			//Set_Player(player_to_set);
			Set_Debug_Info(int_seed, num_rooms);
			populate_monsters(nummon_value, &int_seed, monsterList);
			stair_t down;
			if(stair_player == UPSTAIRS)
			{
				down.location.x = get_Character_pos(player_to_set).x;
				down.location.y = get_Character_pos(player_to_set).y;
				down.direction = DOWNSTAIRS;
			}
			else 
			{
				down = Place_Stairs(dungeon, &int_seed, DOWNSTAIRS);
				while(level > 0 && down.location.x == get_Character_pos(player_to_set).x && down.location.y == get_Character_pos(player_to_set).y)
					{
						down = Place_Stairs(dungeon, &int_seed, DOWNSTAIRS);
					}
			}
			Set_Stairs(down);
			if(level > 0)
			{
				stair_t up;
				if(stair_player == DOWNSTAIRS)
				{
					up.location.x = get_Character_pos(player_to_set).x;
					up.location.y = get_Character_pos(player_to_set).y;
					up.direction = UPSTAIRS;
				}
				else 
				{
					up = Place_Stairs(dungeon, &int_seed, UPSTAIRS);
					while(down.location.x == up.location.x && down.location.y == up.location.y)
					{
						up = Place_Stairs(dungeon, &int_seed, UPSTAIRS);
					}
				}
				Set_Stairs(up);
			}
			//Draw_Dungeon(1);
			//printf("\n");
			//distance_dungeon = Generate_Distance_Dungeon(FALSE);
			//Draw_Distance_Dungeon(distance_dungeon);
			//Destroy_All();
			//printf("\n");
			//distance_dungeon_tunneler = Generate_Distance_Dungeon(TRUE);
			level = turn(&int_seed, nummon_value);
			
			//Draw_Distance_Dungeon(distance_dungeon_tunneler);
			Destroy_All();
		}
		Draw_Dungeon(0);
		endwin();
	}
	if(Contains_Flag(flags, (argc - 1), SAVE) == TRUE || game_state == 5)
	{
		
		//printf("Made it here\n");
		//printf("getenv = %s\n", getenv("HOME"));
		if(loaded == FALSE)
		{
			//printf("dungeonFolder = %s\n", dungeonFolder);
			if (access(dungeonFolder, F_OK) == -1) 
			{
				mkdir(dungeonFolder, ACCESSPERMS);
				//printf("File created\n");
			}
			//else printf("File exist\n");
			if(game_state == 5)
			{
				char level_file[6] = "level";
				strcat(dungeonFolder, level_file);
			}
			else
			{
				strcat(dungeonFolder, dungeonSaveFileName);
			}
			//printf("Here\n");
		}
		else
		{
			//printf("dungeonFolder = %s\n", dungeonFolder);
			char *substring = strstr(dungeonFolder, dungeonFileName);
			//printf("substring = %s\n", substring);
			if(save_param_used == TRUE)
			{
				strcpy(substring, dungeonSaveFileName);
			}
			else
			{
				strcpy(substring, dungeonFileName);
			}
			//printf("substring = %s\n", substring);
			//printf("dungeonFolder = %s\n", dungeonFolder);
		}
		
		//printf("dungeonFolder = %s\n", dungeonFolder);
		/*printf("dungeonFileName = %s\n", dungeonFileName);
		printf("dungeonSaveFileName = %s\n", dungeonSaveFileName);*/
		
		Save_Dungeon(dungeon, dungeonFolder, num_rooms);
		
		//save();
		//printf("save\n");		
	}
	
	Destroy_Dungeon(dungeon);
	
	return 0;
}

boolean isstring(char *string)
{
	boolean start = (boolean) TRUE;
	boolean is_string = (boolean) TRUE;
	while(*string != '\0')
	{
		if(isdigit(*string) != 0)
		{
			is_string = (boolean) FALSE;
		}
		else if(start == TRUE)
		{
			start = (boolean) FALSE;
			if(*string != '-')
			{
				return (boolean) TRUE;
			}
		}
		else
		{
			return (boolean) TRUE;
		}
	  string++;
    }
	return is_string;
}
