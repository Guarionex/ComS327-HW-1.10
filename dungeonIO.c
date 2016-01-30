#include "dungeonIO.h"
#include <stdio.h>
#include <stdlib.h>

bool Contains_Flag(Flags *flag, int size, Flags contains)
{
	int f;
	for(f = 0; f < size; f++)
	{
		//printf("flag = %d\n", flag[f]);
		if(flag[f] == contains)
		{
			return TRUE;
		}
	}
	
	return FALSE;
}

/*Dungeon_Space_Struct **Load_Dungeon(char *file)
{
	FILE *f;
	f = fopen(file, "r");
	
	
}*/