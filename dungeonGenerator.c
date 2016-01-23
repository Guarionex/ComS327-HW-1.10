#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dungeonObjects.h"
#include "dungeonRoomGenerator.h"

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
	printf("Room 0 is %d wide and %d long\n", rooms[0].width, rooms[0].height);
	printf("Room 1 is %d wide and %d long\n", rooms[1].width, rooms[1].height)
	printf("size of rooms/rooms[0] is %ld\n", sizeof(rooms)/sizeof(*rooms));
	printf("size of rooms is %ld\n", sizeof(rooms));
	printf("size of *rooms is %ld\n", sizeof(*rooms));
	int k;
	for(k = 0; k < sizeof(rooms)/sizeof(rooms[0]); k++)
	{
		
		printf("Room %d is %d wide and %d long\n", k, rooms[k].width, rooms[k].height);
	}
	
	return 0;
}
