#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dungeonObjects.h"
#include "dungeonRoomGenerator.h"
#include "dungeonLevelGenerator.h"

int main(int argc, char *argv[])
{
	time_t seed;
	if(argc != 2)
	{
		seed = time(NULL);
	}
	else if(argc == 2)
	{
		seed = atoi(argv[1]);
	}
	srand(seed);
	
	int int_seed = seed;
	
	Dungeon_Space_Struct **dungeon = Generate_Map(&int_seed);
	Draw_Dungeon(dungeon);
	
	return 0;
}
