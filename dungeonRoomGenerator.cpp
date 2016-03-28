#include "dungeonRoomGenerator.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Dungeon_Space_Room generateRoom()
{	
	//int seed_local = seed;
	
	/*if(seed <= 0)
	{
		seed_local = time(NULL);
		seed = seed_local;
	}
	else if(seed > 0)
	{
		seed_local = seed;
	}*/
	
	//srand(seed_local);

	Dungeon_Space_Room room = Dungeon_Space_Room_create((rand()%4)+3, (rand()%4)+2); 
	
	return room;
}

Dungeon_Space_Room *generateMultipleRooms(int *seed)
{
	int seed_local;
	int num_room;
	
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
	
	num_room = (rand()%3)+5;
	//printf("Number of rooms is %d\n", num_room);
	
	Dungeon_Space_Room *room_collection = (Dungeon_Space_Room *) malloc(sizeof(Dungeon_Space_Room) * (num_room+1));
	Dungeon_Space_Room *room_collection_ptr;
	
	for(room_collection_ptr = room_collection; room_collection_ptr != room_collection + num_room; room_collection_ptr++)
	{
		*room_collection_ptr = generateRoom();
	}
	*room_collection_ptr = Dungeon_Space_Room_create(-1, -1);
	return room_collection;
	
}

stair_t Place_Stairs(Dungeon_Space_Struct **dungeon, int *seed, stair_direction_t direction)
{
	pos_t *open_pos = (pos_t *) malloc(sizeof(pos_t));
	open_pos[0] = NULL_POS;
	stair_t stair_well;
	
	int x, y, open_count = 0;
	for(x = 0; x < 80; x++)
	{
		for(y = 0; y < 21; y++)
		{
			pos_t new_pos;
			switch(dungeon[x][y].space_type)
			{
				case ROCK:
				break;
				
				case ROOM:
					new_pos.x = x;
					new_pos.y = y;
					open_count++;
					open_pos = (pos_t *) realloc(open_pos, sizeof(pos_t) + (sizeof(pos_t) * open_count));
					open_pos[open_count-1] = new_pos;
					open_pos[open_count] = NULL_POS;
				break;
				
				case CORRIDOR:
					new_pos.x = x;
					new_pos.y = y;
					open_count++;
					open_pos = (pos_t *) realloc(open_pos, sizeof(pos_t) + (sizeof(pos_t) * open_count));
					open_pos[open_count-1] = new_pos;
					open_pos[open_count] = NULL_POS;
				break;
			}
		}
	}
	
	/*int seed_local;
	
	if(*seed <= 0)
	{
		seed_local = time(NULL);
		*seed = seed_local;
	}
	else if(*seed > 0)
	{
		seed_local = *seed;
	}
	srand(seed_local);*/
	
	pos_t new_pos = open_pos[rand()%open_count];
	//printf("Stair pos = [%d][%d], available positions = %d\n", new_pos.x, new_pos.y, open_count);
	stair_well.location = new_pos;
	stair_well.direction = direction;
	free(open_pos);
	return stair_well;
}
