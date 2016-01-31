#include "dungeonIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <endian.h>
#include <stdint.h>

Dungeon_Space_Struct **dungeon_map_load;

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
	if(items < 6 || strcmp(header, "RLG327") != 0)
	{
		printf("File header is not in the correct format\n");
		return 0;
	}
    //printf("Header is %s and read %d items\n", header, items);
	
	char *version = malloc( 4 * sizeof(char));
	items = fread(version, sizeof(char), 4, f);
	if(items < 4 || strcmp(version, "\x00\x00\x00\x00") != 0)
	{
		
		printf("File version is not in the correct format\n");
		return 0;
	}
	//printf("Version Marker is %s and read %d items\n", version, items);
	
	char *sizeRaw = malloc( 4 * sizeof(char));
	if((items = fread(sizeRaw, sizeof(char), 4, f)) < 4)
	{
		printf("File size is not in the correct format\n");
		return 0;
	}
	uint32_t sizeBE = *((uint32_t *) sizeRaw);
	//printf("Hex sizeBE = 0x%x\n", sizeBE);
	uint32_t sizeH = be32toh(sizeBE);
	//printf("Hex sizeH = 0x%x\n", sizeH);
	if(sizeH < 1495)
	{
		printf("File is missing information\n");
		return 0;
	}
	//printf("SizeH is %u and read %d items\n", sizeH, items);
	
	dungeon_map_load =  malloc(80 * sizeof(Dungeon_Space_Struct *));
	int x;
	int y;
	int bytesRead = 0;
	for(y = 0; y < 21; y++)
	{
		//printf("Y = %d\n", y);
		
		for(x = 0; x < 80; x++)
		{
			if(y == 0)
			{
				dungeon_map_load[x] = malloc(21 * sizeof(Dungeon_Space_Struct));
			}
			//printf("X = %d\n", x);
			Dungeon_Space_Rock rock;
			Dungeon_Space_Corridor corridor;
			bool is_rock = TRUE;
			if(x == 0 || y == 0 || x == 79 || y == 20)
			{
				//printf("[%d][%d] = border\n", x, y);
				rock = Dungeon_Space_Rock_create(255);
				is_rock = TRUE;
			}
			else
			{
				//printf("[%d][%d] = inside\n", x, y);
				char *densityRaw = malloc( 1 * sizeof(char));
				if((items = fread(densityRaw, sizeof(char), 1, f)) < 1)
				{
					printf("File hardness is not in the correct format\n");
					return 0;
				}
				uint8_t densityBE = *((uint8_t *) densityRaw);
				//printf("Hex densityBE = 0x%x\n", densityBE);
				//uint8_t sizeH = be8toh(sizeBE); //Single byte, don't need to convert
				//printf("Hex sizeH = 0x%x\n", sizeH);
				if(densityBE > 255 || densityBE < 0)
				{
					printf("Hardness format is not correct\n");
					return 0;
				}
				if(densityBE != 0)
				{
					rock = Dungeon_Space_Rock_create(densityBE);
					is_rock = TRUE;
				}
				else if(densityBE == 0)
				{
					corridor = Dungeon_Space_Corridor_create("0");
					is_rock = FALSE;
				}
				//printf("densityBE is %hu and read %d items\n", densityBE, items);
				bytesRead++;
			}
			
			Dungeon_Space_Struct cell = (is_rock == TRUE) ? Dungeon_Space_Struct_create(ROCK, rock) : Dungeon_Space_Struct_create(CORRIDOR, corridor);
			dungeon_map_load[x][y] = cell;
		}
	}
	//printf("Read %d bytes\n", bytesRead);
	if(bytesReads < 1482)
	{
		printf("File cells missing, not in correct format\n");
		return 0;
	}
	
	int room_byte;
	int num_room = 0;
	for(room_byte = 1496; room_byte < sizeH; room_byte += 4)
	{
		num_room++;
		char *roomRaw = malloc( 4 * sizeof(char));
		if((items = fread(roomRaw, sizeof(char), 4, f)) < 4)
		{
			printf("File rooms is not in the correct format\n");
			return 0;
		}
		uint8_t roomXBE = ((uint8_t) roomRaw[0]);
		uint8_t roomYBE = ((uint8_t) roomRaw[1]);
		uint8_t roomWidthBE = ((uint8_t) roomRaw[2]);
		uint8_t roomHeightBE = ((uint8_t) roomRaw[3]);
		/*printf("Hex roomXBE = 0x%x\n", roomXBE);
		printf("Hex roomYBE = 0x%x\n", roomYBE);
		printf("Hex roomWidthBE = 0x%x\n", roomWidthBE);
		printf("Hex roomHeightBE = 0x%x\n", roomHeightBE);*/
		//uint8_t sizeH = be8toh(sizeBE); //Single byte, don't need to convert
		//printf("Hex sizeH = 0x%x\n", sizeH);
		if(roomXBE > 255 || roomXBE < 0 || roomYBE > 255 || roomYBE < 0 || roomWidthBE > 255 || roomWidthBE < 0 || roomHeightBE > 255 || roomHeightBE < 0)
		{
			printf("Hardness format is not correct\n");
			return 0;
		}
		/*printf("roomXBE is %hu and read %d items\n", roomXBE, items);
		printf("roomYBE is %hu and read %d items\n", roomYBE, items);
		printf("roomWidthBE is %hu and read %d items\n", roomWidthBE, items);
		printf("roomHeightBE is %hu and read %d items\n", roomHeightBE, items);*/
		
		Dungeon_Space_Room room = Dungeon_Space_Room_create(roomWidthBE, roomHeightBE);
		room.x = roomXBE;
		room.y = roomYBE;
		
		int w;
		int h;
		for(h = 0; h < room.height; h++)
		{
			for(w = 0; w < room.width; w++)
			{
				Dungeon_Space_Struct cell = Dungeon_Space_Struct_create(ROOM, room);
				dungeon_map_load[room.x+w][room.y+h] = cell;
			}
		}
	}
	if(num_room != (sizeH - 1496)/4)
	{
		printf("File number rooms not correct\n");
		return 0;
	}
	printf("Number of rooms = %d\n", num_room);
	
	fclose(f);
	free(header);
	free(version);
	free(sizeRaw);
	free(densityRaw);
	free(roomRaw);
	
	return dungeon_map_load;
}