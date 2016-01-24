#include "dungeonLevelGenerator.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>

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
	int num_attempts = 0;
	for(r = 0; r < num_rooms; r++)
	{
		bool overlap = TRUE;
		num_attempts = 0;
		while(((rooms[r].x + rooms[r].width > 79) || (rooms[r].y + rooms[r].height > 20)) || (rooms[r].x < 0 || rooms[r].y < 0) || overlap == TRUE)
		{
			rooms[r].x = (rand()%78)+1;
			rooms[r].y = (rand()%19)+1;
			
			if(num_attempts > 2000)
			{
				return FALSE;
			}
			num_attempts++;
			
			int pr;
			overlap = FALSE;
			
			for(pr = 0; pr < r; pr++)
			{	
				bool x_overlap = FALSE;
				bool y_overlap = FALSE;
				if(rooms[r].x == rooms[pr].x)
				{
					x_overlap = TRUE;
				}
				else if(rooms[r].x < rooms[pr].x)
				{
					if((rooms[r].x + rooms[r].width) >= rooms[pr].x)
					{
						x_overlap = TRUE;
					}
				}
				else if(rooms[r].x > rooms[pr].x)
				{
					if((rooms[pr].x + rooms[pr].width) >= rooms[r].x)
					{
						x_overlap = TRUE;
					}
				}
				
				if(rooms[r].y == rooms[r].y)
				{
					y_overlap = TRUE;
				}
				else if(rooms[r].y < rooms[pr].y)
				{
					if((rooms[r].y + rooms[r].height) >= rooms[pr].y)
					{
						y_overlap = TRUE;
					}
				}
				else if(rooms[r].y > rooms[pr].y)
				{
					if((rooms[pr].y + rooms[pr].height) >= rooms[r].y)
					{
						y_overlap = TRUE;
					}
				}
				
				if(x_overlap == TRUE && y_overlap == TRUE)
				{
					overlap = TRUE;
					break;
				}
			}
			
			printf("rooms[%d].x = %d\n", r, rooms[r].x);
			printf("rooms[%d].y = %d\n", r, rooms[r].y);
		}
		
		printf("Number of attempts = %d\n", num_attempts);
		
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

void Connect_Rooms(Dungeon_Space_Room *rooms, int num_rooms)
{
	Dungeon_Space_Room sorted_rooms[num_rooms];
	sorted_rooms[0] = rooms[0];
	int r;
	int sr;
	for(sr = 0; sr < num_rooms - 1; sr++)
	{
		Dungeon_Space_Room closest;
		int distance = INT_MAX;
		for(r = 0; r < num_rooms; r++)
		{
			int local_distance = sqrt(pow(rooms[r].x - sorted_rooms[sr].x,2)+pow(rooms[r].y - sorted_rooms[sr].y,2));
			if(local_distance < distance && local_distance > 0)
			{
				distance = local_distance;
				closest = rooms[r];
			}
		}
		sorted_rooms[sr+1] = closest;
	}
	
	printf("Sorted order:\n");
	for(sr = 0; sr < num_rooms; sr++)
	{
		printf("sorted_rooms[%d] = {x = %d, y = %d, w = %d, h = %d}\n", sr, sorted_rooms[sr].x, sorted_rooms[sr].y, sorted_rooms[sr].width, sorted_rooms[sr].height);
	}
}

void Draw_Dungeon()
{
	int x;
	int y;
	for(y = 0; y < 21; y++)
	{
		for(x = 0; x < 80; x++)
		{
			switch(dungeon_map[x][y].space_type)
			{
				case ROCK :
				
					if(dungeon_map[x][y].space_union.rock.density == INT_MAX)
					{
						printf("R");
					}
					else printf(" ");
				
				break;
				case ROOM :
				
					printf(".");
				
				break;
				case CORRIDOR :
					printf("#");
				break;
			}
		}
		printf("\n");
	}
}