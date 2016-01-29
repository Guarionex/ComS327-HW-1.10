#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "dungeonObjects.h"
#include "dungeonRoomGenerator.h"
#include "dungeonLevelGenerator.h"
#include "dungeonIO.h"

bool isstring(char *string);

int main(int argc, char *argv[])
{
	time_t seed;
	flags = malloc((argc - 1) * sizeof(Flags));
	
	if(argc >= 2)
	{
		int c;
		for(c = 1; c < argc; c++)
		{
			if(isstring(argv[c]) == FALSE)
			{
				seed = atoi(argv[c]);
				flags[c] = SEED;
			}
			else if(strstr(argv[c], "--") != NULL)
			{
				if(strcmp(argv[c], "--save") == 0)
				{
					printf("save\n");
					flags[c] = SAVE;
				}
				else if(strcmp(argv[c], "--load") == 0)
				{
					printf("load\n");
					flags[c] = LOAD;
				}
			}
		}
	}
	if(Contains_Flag(flags, argc - 1, SEED) == FALSE)
	{
		seed = time(NULL);
	}
	srand(seed);
	
	int int_seed = seed;
	
	Dungeon_Space_Struct **dungeon = Generate_Map(&int_seed);
	Draw_Dungeon(dungeon);
	
	return 0;
}

bool isstring(char *string)
{
  while(*string != '\0')
    {
		if(isdigit(*string) != 0)
		{
		  return FALSE;
		}
      string++;
    }
  return TRUE;
}
