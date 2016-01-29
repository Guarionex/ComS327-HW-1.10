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
	Flags flags[argc - 1];
	
	if(argc >= 2)
	{
		int c;
		for(c = 1; c < argc; c++)
		{
			if(isstring(argv[c]) == FALSE)
			{
				seed = atoi(argv[c]);
				flags[c - 1] = SEED;
			}
			else if(strstr(argv[c], "--") != NULL)
			{
				if(strcmp(argv[c], "--save") == 0)
				{
					printf("save\n");
					flags[c - 1] = SAVE;
				}
				else if(strcmp(argv[c], "--load") == 0)
				{
					if(Contains_Flag(flags, (argc - 1), SEED) == TRUE)
					{
						printf("Usage: ./dungeonGenerator (<int> XOR --load) OR --save");
						return 0;
					}
					printf("load\n");
					flags[c - 1] = LOAD;
				}
			}
		}
	}
	int f;

	if(Contains_Flag(flags, (argc - 1), SEED) == FALSE)
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
