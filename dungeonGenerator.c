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
	printf("Seed is %ld\n", seed);
	printf("Random is %d\n", random_i_1);
	printf("Random is %d\n", random_i_2);
	printf("Random is %d\n", random_i_3);
	printf("Random is %d\n", random_i_1);
	printf("Random is %d\n", random_i_2);
	printf("Random is %d\n", random_i_3);
	
	return 0;
}
