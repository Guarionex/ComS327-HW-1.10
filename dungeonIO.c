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

bool Contains_Room(Dungeon_Space_Room *rooms, int size, Dungeon_Space_Room room)
{
	int r;
	for(r = 0; r < size; r++)
	{
		if(rooms[r].x == room.x && rooms[r].y == room.y)
		{
			return TRUE;
		}
	}
	
	return FALSE;
}

Dungeon_Space_Struct **Load_Dungeon(char *file, int *num_rooms)
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
		return NULL;
	}
	
	char *header = malloc (6 * sizeof(char));
	int items = fread(header, sizeof(char), 6, f);
	if(items < 6 || strcmp(header, "RLG327") != 0)
	{
		printf("File header is not in the correct format\n");
		return NULL;
	}
    //printf("Header is %s and read %d items\n", header, items);
	
	char *version = malloc( 4 * sizeof(char));
	items = fread(version, sizeof(char), 4, f);
	if(items < 4 || strcmp(version, "\x00\x00\x00\x00") != 0)
	{
		
		printf("File version is not in the correct format\n");
		return NULL;
	}
	//printf("Version Marker is %s and read %d items\n", version, items);
	
	char *sizeRaw = malloc( 4 * sizeof(char));
	if((items = fread(sizeRaw, sizeof(char), 4, f)) < 4)
	{
		printf("File size is not in the correct format\n");
		return NULL;
	}
	uint32_t sizeBE = *((uint32_t *) sizeRaw);
	//printf("Hex sizeBE = 0x%x\n", sizeBE);
	uint32_t sizeH = be32toh(sizeBE);
	//printf("Hex sizeH = 0x%x\n", sizeH);
	if(sizeH < 1495)
	{
		printf("File is missing information\n");
		return NULL;
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
					return NULL;
				}
				uint8_t densityBE = *((uint8_t *) densityRaw);
				//printf("Hex densityBE = 0x%x\n", densityBE);
				//uint8_t sizeH = be8toh(sizeBE); //Single byte, don't need to convert
				//printf("Hex sizeH = 0x%x\n", sizeH);
				if(densityBE > 255 || densityBE < 0)
				{
					printf("Hardness format is not correct\n");
					return NULL;
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
				free(densityRaw);
			}
			
			Dungeon_Space_Struct cell = (is_rock == TRUE) ? Dungeon_Space_Struct_create(ROCK, rock) : Dungeon_Space_Struct_create(CORRIDOR, corridor);
			dungeon_map_load[x][y] = cell;
		}
	}
	//printf("Read %d bytes\n", bytesRead);
	if(bytesRead != 1482)
	{
		printf("File cells is not in correct format\n");
		return NULL;
	}
	
	int room_byte;
	int total_num_room = 0;
	for(room_byte = 1496; room_byte < sizeH; room_byte += 4)
	{
		total_num_room++;
		char *roomRaw = malloc( 4 * sizeof(char));
		if((items = fread(roomRaw, sizeof(char), 4, f)) < 4)
		{
			printf("File rooms is not in the correct format\n");
			return NULL;
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
			return NULL;
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
		free(roomRaw);
	}
	if(total_num_room != (sizeH - 1496)/4)
	{
		printf("File number rooms not correct\n");
		return NULL;
	}
	printf("Number of rooms = %d\n", total_num_room);
	*num_rooms = total_num_room;
	
	fclose(f);
	free(header);
	free(version);
	free(sizeRaw);
	
	return dungeon_map_load;
}


int Save_Dungeon(Dungeon_Space_Struct **dungeon_map_save, char *file, int num_rooms)
{
	FILE *f;
	printf("file = %s\n", file);
	if((f = fopen(file, "w")) == NULL)
	{
		if (errno == EINVAL) 
		{
			printf ("The mode is invalid %s\n", file);
		}
		else 
		{
			printf ("File error\n");
		}
		return -1;
	}
	
	char *header = "RLG327"; //malloc(6 * sizeof(char));
	//printf("Header = %s\n", header);
	int items = fwrite(header, sizeof(char), 6, f);
	if(items < 6)
	{
		printf("File header write failed\n");
		return -1;
	}
    //printf("Header is %s and read %d items\n", header, items);
	
	char *version = "\x00\x00\x00\x00";//malloc( 4 * sizeof(char));
	items = fwrite(version, sizeof(char), 4, f);
	if(items < 4)
	{
		
		printf("File version writing failed\n");
		return -1;
	}
	//printf("Version Marker is %s and read %d items\n", version, items);
	
	uint32_t fileSizeH = (num_rooms * 4) + 1496;
	uint32_t fileSizeBE = htobe32(fileSizeH);
	//char *sizeRaw = malloc( 4 * sizeof(char));
	if((items = fwrite(&fileSizeBE, sizeof(char), 4, f)) < 4)
	{
		printf("File size writing failed\n");
		return 0;
	}
	//printf("SizeH is %u and read %d items\n", sizeH, items);
	
	Dungeon_Space_Room *rooms = malloc(sizeof(Dungeon_Space_Room) * num_rooms);
	printf("Before rocks\n");
	int x, y, room_index = 0;
	for(x = 0; x < 80; x++)
	{
		for(y = 0; y < 21; y++)
		{
			if(x == 0 || y == 0 || x == 79 || y == 20)
			{
				continue;
			}
			
			uint8_t density;
			switch(dungeon_map_save[x][y].space_type)
			{
				case ROCK:
					density = dungeon_map_save[x][y].space_union.rock.density;
				break;
				
				case ROOM:
					density = dungeon_map_save[x][y].space_union.room.density;
					if(Contains_Room(rooms, num_rooms, dungeon_map_save[x][y].space_union.room) == FALSE)
					{
						rooms[room_index] = dungeon_map_save[x][y].space_union.room;
						room_index++;
					}
				break;
				
				case CORRIDOR:
					density = dungeon_map_save[x][y].space_union.corridor.density;
					printf("Corridor at [%d][%d]\n", x, y);
				break;
			}
			
			if((items = fwrite(&density, sizeof(char), 1, f)) < 1)
			{
				printf("File hardness writing failed\n");
				return 0;
			}
			
			
			
		}
	}
	printf("Before rooms\n");
	int r;
	char *roomToWrite = malloc( 4 * sizeof(char));
	for(r = 0; r < num_rooms; r++)
	{
		
		roomToWrite[0] = rooms[r].x;
		roomToWrite[1] = rooms[r].y;
		roomToWrite[2] = rooms[r].width;
		roomToWrite[3] = rooms[r].height;
		
		if((items = fwrite(roomToWrite, sizeof(char), 4, f)) < 4)
		{
			printf("File room writing failed\n");
		}
	}
	printf("End of save\n");
	//free(roomToWrite);
	printf("Freed roomToWrite\n");
	free(rooms);
	printf("Freed rooms\n");
	fclose(f);
	printf("Closed f\n");
	
	return 0;
}