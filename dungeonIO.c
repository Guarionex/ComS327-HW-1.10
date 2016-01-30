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

Dungeon_Space_Struct **Load_Dungeon(char *file)
{
	FILE *f;
	printf("file = %s\n", file);
	//f = fopen(file, "r");
	//char *header = malloc (6 * sizeof(char));
	/*if(fgets(header, 6, f) != NULL)
	{
		printf("Header is %s\n", header);
	}*/
	//fread(header, sizeof (char), 6, f);
    //printf("Header is %s\n", header);
	
	Dungeon_Space_Struct **dungeon_map_load =  malloc(80 * sizeof(Dungeon_Space_Struct *));
	int x;
	int y;
	for(x = 0; x < 80; x++)
	{
		dungeon_map_load[x] = malloc(21 * sizeof(Dungeon_Space_Struct));
		for(y = 0; y < 21; y++)
		{
			
		}
	}
	
	//fclose(f);
	//free(header);
	
	return dungeon_map_load;
}