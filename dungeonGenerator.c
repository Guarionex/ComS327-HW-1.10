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

int main(int argc, char *argv[])
{
	time_t seed;
	Flags flags[argc - 1];
	char *dungeonFileName;
	bool load_param = FALSE;
	
	if(argc >= 2)
	{
		int c;
		for(c = 1; c < argc; c++)
		{
			if(load_param == TRUE)
			{
				load_param = FALSE;
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
					flags[c - 1] = SAVE;
				}
				else if(strcmp(argv[c], "--load") == 0)
				{
					if(((c + 1) < argc) && strstr(argv[c + 1], "--") == NULL)
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
	
	char *dungeonFolder = strcat(getenv("HOME"), "/.rlg327/");
	
	if(Contains_Flag(flags, (argc - 1), LOAD) == TRUE)
	{
		char *dungeonFile = strdup(dungeonFolder);
		dungeonFile = strcat(dungeonFile, dungeonFileName);
		printf("dungeonFile = %s\n", dungeonFile);
		if(access(dungeonFile, F_OK) == -1)
		{
			if (errno == ENOENT) 
			{
				printf ("%s does not exist\n", dungeonFile);
			}
			else if (errno == EACCES) 
			{
				printf ("%s is not accessible\n", dungeonFile);
			}
			return 0;
		}
		
		//load()
		//generate()
		//draw()
		printf("load\n");
	}
	else
	{
		srand(seed);
		
		int int_seed = seed;
		
		Dungeon_Space_Struct **dungeon = Generate_Map(&int_seed);
		Draw_Dungeon(dungeon);
	}
	
	if(Contains_Flag(flags, (argc - 1), SAVE) == TRUE)
	{
		
		
		
		if (access(dungeonFolder, F_OK) == -1) 
		{
			mkdir(dungeonFolder, ACCESSPERMS);
			
		}
		
		//save();
		printf("save\n");		
	}
	
	
	return 0;
}

bool isstring(char *string)
{
	bool start = TRUE;
	while(*string != '\0')
	{
		if(isdigit(*string) != 0)
		{
			//printf("*string = %c", *string);
			return FALSE;
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
	return TRUE;
}
