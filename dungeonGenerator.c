#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dungeonObjects.h"
#include "dungeonRoomGenerator.h"
#include "dungeonLevelGenerator.h"

int main(int argc, char *argv[])
{
	time_t seed;
	if(argc != 2)
	{
		seed = time(NULL);
	}
	else if(argc == 2)
	{
		seed = atoi(argv[1]);
	}
	 
	srand(seed);
	int random_i_1 = rand();
	int random_i_2 = rand();
	int random_i_3 = rand();
	int num_room;
	int int_seed = seed;
	printf("Seed is %ld\n", seed);
	printf("int_Seed is %d\n", int_seed);
	printf("Random is %d\n", random_i_1);
	printf("Random is %d\n", random_i_2);
	printf("Random is %d\n", random_i_3);
	printf("Normalized is %d\n", (random_i_1%78)+1);
	printf("Normalized is %d\n", (random_i_2%78)+1);
	printf("Normalized is %d\n", (random_i_3%78)+1);
	printf("Test width is %d\n", (rand()%4)+3);
	printf("Test height is %d\n", (rand()%4)+2);
	num_room =(rand()%3)+5;
	//printf("Test num_rooms is %d\n", num_room);
	
	int *int_collection = malloc(sizeof(int) * num_room);
	int *int_collection_copy;
	for(int_collection_copy = int_collection; int_collection_copy != int_collection+num_room-1; int_collection_copy++)
	{
			*int_collection_copy = (rand()%78)+1;
	}
	/*int j;
	for(j = 0; j < num_room; j++)
	{
		int_collection[j] = (random_i_1%78)+1;
	}*/
	
	int i;
	printf("int_collection[0] = %d\n", int_collection[0]);
	for(i = 0; int_collection[i] != '\0'; i++)
	{
			printf("int_collection[%d] = %d\n", i, int_collection[i]);
	}
	
	
	
	Dungeon_Space_Room *rooms;
	rooms = generateMultipleRooms(&int_seed);
	//printf("Room 0 is %d wide and %d long\n", rooms[0].width, rooms[0].height);
	//printf("Room 1 is %d wide and %d long\n", rooms[1].width, rooms[1].height);
	//printf("Room 2 is %d wide and %d long\n", rooms[2].width, rooms[2].height);
	printf("size of rooms/rooms[0] is %ld\n", sizeof(rooms)/sizeof(*rooms));
	printf("size of rooms is %ld\n", sizeof(rooms));
	printf("size of *rooms is %ld\n", sizeof(*rooms));
	int total_num_rooms = 0;
	printf("Is it true width at 0 is -1? its %d\n", rooms[total_num_rooms].width);
	for(total_num_rooms = 0; rooms[total_num_rooms].width != -1; total_num_rooms++)
	{
		
		printf("Room %d is %d wide and %d long\n", total_num_rooms, rooms[total_num_rooms].width, rooms[total_num_rooms].height);
	}
	printf("total_num_rooms = %d\n", total_num_rooms);
	
	Dungeon_Space_Rock rock = Dungeon_Space_Rock_create((rand()%100)+1);
	Dungeon_Space_Struct cell = Dungeon_Space_Struct_create(ROCK, rock);
	if(cell.space_type == ROCK)
	{
		printf("The cell is a rock with a density of %d\n", cell.space_union.rock.density);
	}
	
	Create_Blank_Map(&int_seed);
	printf("Seed is %d\n", int_seed);
	bool success = FALSE;
	int attempts = 0;
	while(success == FALSE || attempts > 2000)
	{
		success = Place_Rooms(rooms, total_num_rooms);
		attempts++;
	}
	if(success == FALSE) 
	{
		printf("Room placement failed after %d attempts\n", attempts);
	}
	Connect_Rooms(rooms, total_num_rooms);
	Draw_Dungeon();
	
	return 0;
}
