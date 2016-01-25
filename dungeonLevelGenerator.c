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
		
		//printf("Number of attempts = %d\n", num_attempts);
		
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
	int sorted_indecis[num_rooms];
	int si;
	for(si = 0; si < num_rooms; si++)
	{
		sorted_indecis[si] = -1;
	}
	sorted_rooms[0] = rooms[0];
	sorted_indecis[0] = 0;
	printf("In connected rooms\n");
	int r;
	int sr;
	for(sr = 0; sr < num_rooms - 1; sr++)
	{
		Dungeon_Space_Room closest;
		int distance = INT_MAX;
		int index;
		for(r = 0; r < num_rooms; r++)
		{
			int i;
			bool already_sorted = FALSE;
			for(i = 0; i < num_rooms; i++)
			{
				if(sorted_indecis[i] == r)
				{
					already_sorted = TRUE;
				}
			}
			if(already_sorted == TRUE)
			{
				continue;
			}
			int local_distance = sqrt(pow(rooms[r].x+(rooms[r].width/2) - sorted_rooms[sr].x+(sorted_rooms[sr].width/2),2)+pow(rooms[r].y+(rooms[r].height/2) - sorted_rooms[sr].y+(sorted_rooms[sr].height/2),2));
			if(local_distance < distance && local_distance > 0)
			{
				distance = local_distance;
				closest = rooms[r];
				index = r;
			}
		}
		sorted_rooms[sr+1] = closest;
		sorted_indecis[sr+1] = index;
		
	}
	
	printf("Sorted order:\n");
	for(sr = 0; sr < num_rooms; sr++)
	{
		printf("sorted_rooms[%d] = {x = %d, y = %d, w = %d, h = %d}\n", sr, sorted_rooms[sr].x, sorted_rooms[sr].y, sorted_rooms[sr].width, sorted_rooms[sr].height);
	}
	
	for(sr = 0; sr < num_rooms; sr++)
	{
		int x0 = sorted_rooms[sr].x + (sorted_rooms[sr].width / 2);
		int y0 = sorted_rooms[sr].y + (sorted_rooms[sr].height / 2);
		int x1 = sorted_rooms[((sr+1) < num_rooms) ? sr+1 : 0].x + (sorted_rooms[((sr+1) < num_rooms) ? sr+1 : 0].width / 2);
		int y1 = sorted_rooms[((sr+1) < num_rooms) ? sr+1 : 0].y + (sorted_rooms[((sr+1) < num_rooms) ? sr+1 : 0].height / 2);
		
		
		
		int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
		int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
		int err = (dx>dy ? dx : -dy)/2, e2;
		
		bool moved_x = FALSE;
		bool moved_y = FALSE;
		for(;;)
		{
			if(moved_x == TRUE && moved_y == TRUE)
			{
				Place_Corridor(x0 - sx, y0, sr);
			}
			Place_Corridor(x0,y0, sr); //int x, int y, int index
			if (x0==x1 && y0==y1) break;
			e2 = err;
			moved_x = FALSE;
			moved_y = FALSE;
			if(e2 >-dx)
			{ 
				err -= dy; 
				x0 += sx; 
				moved_x = TRUE;
			}
			if(e2 < dy)
			{ 
				err += dx; 
				y0 += sy; 
				moved_y = TRUE;
			}
		}
	}
	
}

void Place_Corridor(int x, int y, int id)
{
	char *str = malloc(sizeof(char) * 2);
	snprintf(str, sizeof(char)*2, "%d", id);
	Dungeon_Space_Corridor corridor = Dungeon_Space_Corridor_create(str);
	Dungeon_Space_Struct cell = Dungeon_Space_Struct_create(CORRIDOR, corridor);
	if(x < 0 || x > 79 || y < 0 || y > 20)
	{
		printf("x0 = %d, y0 = %d\n", x, y);
	}
	switch(dungeon_map[x][y].space_type)
	{
		case ROCK:
			dungeon_map[x][y] = cell;
		break;
		
		case ROOM:
			//ignore
		break;
		
		case CORRIDOR:
			//ignore
		break;
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