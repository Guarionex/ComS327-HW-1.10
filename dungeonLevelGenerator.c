#include "dungeonLevelGenerator.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

Dungeon_Space_Struct **dungeon_map;

void Create_Blank_Map(int *seed)
{
	dungeon_map =  malloc(80 * sizeof(Dungeon_Space_Struct *));
	
	int seed_local;
	
	if(seed <= 0)
	{
		seed_local = time(NULL);
		*seed = seed_local;
	}
	else if(seed > 0)
	{
		seed_local = *seed;
	}
	
	srand(seed_local);
	
	int x;
	int y;
	for(x = 0; x < 80; x++)
	{
		dungeon_map[x] = malloc(21 * sizeof(Dungeon_Space_Struct));
		for(y = 0; y < 21; y++)
		{
			Dungeon_Space_Rock rock = Dungeon_Space_Rock_create((x == 0 || y == 0 || x == 79 || y == 20) ? INT_MAX : (rand()%100)+1);
			Dungeon_Space_Struct cell = Dungeon_Space_Struct_create(ROCK, rock);
			dungeon_map[x][y] = cell;
		}
	}
}

bool Place_Rooms(Dungeon_Space_Room *rooms, int num_rooms)
{
	
	int r;
	for(r = 0; r < num_rooms; r++)
	{
		printf("rooms[%d].x = %d\n", r, rooms[r].x);
		printf("rooms[%d].y = %d\n", r, rooms[r].y);
		while((rooms[r].x + rooms[r].width > 80) || (rooms[r].y + rooms[r].height > 21))
		{
			rooms[r].x = (rand()%78)+1;
			rooms[r].y = (rand()%19)+1;
		}
		
		int w;
		int h;
		for(h = 0; h < rooms[r].height; h++)
		{
			for(w = 0; w < rooms[r].width; w++)
			{
				Dungeon_Space_Struct cell = Dungeon_Space_Struct_create(ROOM, rooms[r]);
				dungeon_map[rooms[r].x+w][rooms[r].y+h] = cell;
			}
		}
		
	}
	
	
	
	return TRUE;
}

void Draw_Dungeon()
{
	int x;
	int y;
	for(y = 0; y < 21; y++)
	{
		for(x = 0; x < 80; x++)
		{
			if(dungeon_map[x][y].space_type == ROCK)
			{
				if(dungeon_map[x][y].space_union.rock.density == INT_MAX)
				{
					printf("R");
				}
				else printf(" ");
			}
			else if(dungeon_map[x][y].space_type == ROOM);
			{
				printf(".");
			}
		}
		printf("\n");
	}
}