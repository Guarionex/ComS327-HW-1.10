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

bool isstring(char *string);

char *dungeonFolder;
Dungeon_Space_Struct **dungeon;


int main(int argc, char *argv[])
{
	time_t seed;
	Flags flags[argc - 1];
	char *dungeonFileName;
	char *dungeonSaveFileName;
	bool load_param = FALSE;
	bool save_param = FALSE;
	bool nummon_param = FALSE;
	int nummon_value = 0;
	bool loaded = FALSE;
	bool save_param_used = FALSE;
	int num_rooms;
	
	if(argc >= 2)
	{
		int c;
		for(c = 1; c < argc; c++)
		{
			if(load_param == TRUE)
			{
				flags[c - 1] = LOAD;
				load_param = FALSE;
				continue;
			}
			if(save_param == TRUE)
			{
				flags[c - 1] = SAVE;
				save_param = FALSE;
				continue;
			}
			if(nummon_param == TRUE)
			{
				flags[c - 1] = NUMMON;
				nummon_param = FALSE;
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
						save_param = TRUE;
						save_param_used = TRUE;
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
						load_param = TRUE;
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
						nummon_param = TRUE;
						nummon_value = atoi(argv[c+1]);
					}
					else
					{
						printf("Invalid parameter for --nummon\n");
						return 0;
					}
					flags[c - 1] = NUMMON;
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
		int null_seed = -1;
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
		Set_Dungeon(dungeon);
		//player_t player;
		//player.cell = dungeon[18][4];
		//player.pos.x = 18;
		//player.pos.y = 4;
		Set_Player(Place_Player(dungeon, &null_seed));
		Draw_Dungeon();
		printf("\n");
		distance_dungeon = Generate_Distance_Dungeon(FALSE);
		Draw_Distance_Dungeon(distance_dungeon);
		Destroy_All();
		printf("\n");
		distance_dungeon_tunneler = Generate_Distance_Dungeon(TRUE);
		Draw_Distance_Dungeon(distance_dungeon_tunneler);
		loaded = TRUE;
		Destroy_All();
	}
	else
	{
		srand(seed);
		
		int int_seed = seed;
		
		dungeon = Generate_Map(&int_seed, &num_rooms);
		Set_Dungeon(dungeon);
		Set_Player(Place_Player(dungeon, &int_seed));
		Set_Debug_Info(int_seed, num_rooms);
		populate_monsters(nummon_value, &int_seed);
		initscr();
		curs_set(0);
		Draw_Dungeon(1);
		//printf("\n");
		//distance_dungeon = Generate_Distance_Dungeon(FALSE);
		//Draw_Distance_Dungeon(distance_dungeon);
		Destroy_All();
		//printf("\n");
		//distance_dungeon_tunneler = Generate_Distance_Dungeon(TRUE);
		turn(&int_seed);
		//Draw_Distance_Dungeon(distance_dungeon_tunneler);
		Destroy_All();
		endwin();
		Draw_Dungeon(0);
	}
	if(Contains_Flag(flags, (argc - 1), SAVE) == TRUE)
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
			strcat(dungeonFolder, dungeonSaveFileName);
			
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

bool isstring(char *string)
{
	bool start = TRUE;
	bool is_string = TRUE;
	while(*string != '\0')
	{
		if(isdigit(*string) != 0)
		{
			is_string = FALSE;
		}
		else if(start == TRUE)
		{
			start = FALSE;
			if(*string != '-')
			{
				return TRUE;
			}
		}
		else
		{
			return TRUE;
		}
	  string++;
    }
	return is_string;
}
