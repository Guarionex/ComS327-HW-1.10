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
	
	Dungeon_Space_Room *room_collection = malloc(sizeof(Dungeon_Space_Room) * num_room+1);
	Dungeon_Space_Room *room_collection_ptr;
	
	for(room_collection_ptr = room_collection; room_collection_ptr != room_collection + num_room; room_collection_ptr++)
	{
		*room_collection_ptr = generateRoom();
	}
	*room_collection_ptr = Dungeon_Space_Room_create(-1, -1);
	return room_collection;
	
}
