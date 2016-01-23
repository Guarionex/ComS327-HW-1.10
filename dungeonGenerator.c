#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
	printf("Seed is %ld\n", seed);
	printf("Random is %d\n", random_i_1);
	printf("Random is %d\n", random_i_2);
	printf("Random is %d\n", random_i_3);
	printf("Normalized is %d\n", (random_i_1%78)+1);
	printf("Normalized is %d\n", (random_i_2%78)+1);
	printf("Normalized is %d\n", (random_i_3%78)+1);
	printf("Test width is %d\n", (rand()%4)+3);
	printf("Test height is %d\n", (rand()%4)+2);
	num_room =(rand()%3)+5;
	printf("Test num_rooms is %d\n", num_room);
	
	int *int_collection = malloc(sizeof(int) * num_room);
	//int *int_collection_copy;
	/*for(int_collection_copy = int_collection; *int_collection_copy != '\0'; int_collection_copy++)
	{
			*int_collection_copy = (random_i_1%78)+1;
	}*/
	int j;
	for(j = 0; int_collection[j] != '\0'; j++)
	{
		int_collection[j] = (random_i_1%78)+1;
	}
	
	int i;
	printf("int_collection[0] = %d", int_collection[0]);
	for(i = 0; int_collection[i] != '\0'; i++)
	{
			printf("int_collection[%d] = %d", i, int_collection[i]);
	}
	
	return 0;
}
