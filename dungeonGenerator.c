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
	bool loaded = FALSE;
	bool save_param_used = FALSE;
	
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
		printf("Usage: ./dungeonGenerator (<int> XOR --load) OR --save\n");
		return 0;
	}
	else if(Contains_Flag(flags, (argc - 1), SEED) == FALSE && Contains_Flag(flags, (argc - 1), LOAD) == FALSE)
	{
		seed = time(NULL);
	}
	
	dungeonFolder = strcat(getenv("HOME"), "/.rlg327/");
	
	if(Contains_Flag(flags, (argc - 1), LOAD) == TRUE)
	{
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
		dungeon = Draw_Dungeon(Load_Dungeon(dungeonFolder));
		loaded = TRUE;
	}
	else
	{
		srand(seed);
		
		int int_seed = seed;
		
		dungeon = Generate_Map(&int_seed);
		Draw_Dungeon(dungeon);
	}
	
	if(Contains_Flag(flags, (argc - 1), SAVE) == TRUE)
	{
		
		
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
		
		printf("dungeonFolder = %s\n", dungeonFolder);
		/*printf("dungeonFileName = %s\n", dungeonFileName);
		printf("dungeonSaveFileName = %s\n", dungeonSaveFileName);*/
		
		Save_Dungeon(dungeon, dungeonFolder);
		
		//save();
		printf("save\n");		
	}
	
	
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
