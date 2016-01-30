#include "dungeonIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <endian.h>
#include <stdint.h>

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
	if((f = fopen(file, "r")) == NULL)
	{
		if (errno == EINVAL) 
		{
			printf ("The mode is invalid %s\n", file);
		}
		else 
		{
			printf ("File error\n");
		}
		return 0;
	}
	
	char *header = malloc (6 * sizeof(char));
	int items = fread(header, sizeof(char), 6, f);
	/*uint64_t headerBE = *((uint64_t *) header);
	printf("Hex headerBE = 0x%lx\n", headerBE);
	uint64_t headerH = be64toh(headerBE);
	printf("Hex headerH = 0x%lx\n", headerH);*/
	if(items < 6 || strcmp(header, "RLG327") != 0)
	{
		printf("File is not in the correct format\n");
		return 0;
	}
    printf("Header is %s and read %d items\n", header, items);
	
	char *version = malloc( 4 * sizeof(char));
	items = fread(version, sizeof(char), 4, f);
	if(items < 4 || strcmp(version, "\x00\x00\x00\x00") != 0)
	{
		
		printf("File is not in the correct format\n");
		return 0;
	}
	printf("Version Marker is %s and read %d items\n", version, items);
	
	char *size = malloc( 4 * sizeof(char));
	items = fread(size, sizeof(char), 4, f);
	uint32_t sizeBE = *((uint32_t *) size);
	printf("Hex sizeBE = 0x%x\n", sizeBE);
	uint32_t sizeH = be32toh(sizeBE);
	printf("Hex sizeH = 0x%x\n", sizeH);
	/*if(items < 4 || strcmp(size, "\x00\x00\x00\x00") != 0)
	{
		
		printf("File is not in the correct format\n");
		return 0;
	}*/
	printf("Size is %u and read %d items\n", sizeH, items);
	
	fclose(f);
	free(header);
	free(version);
	free(size);
	
	
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
	
	
	
	return dungeon_map_load;
}