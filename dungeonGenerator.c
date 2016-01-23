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
	printf("Normalized is %d\n", (random_i_1%78)+1);
	printf("Normalized is %d\n", (random_i_2%78)+1);
	printf("Normalized is %d\n", (random_i_3%78)+1);
	printf("Test width is %d\n", (rand()%4)+3);
	printf("Test height is %d\n", (rand()%4)+2);
	
	return 0;
}
