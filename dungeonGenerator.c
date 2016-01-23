#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	time_t seed
	if(argc != 2)
	{
		seed = time(NULL);
	}
	else if(argc == 2)
	{
		seed = atoi(argv[1]);
	}
	 
	srand(seed);
	printf("Random is %d\n", rand());
	printf("Random is %d\n", rand());
	printf("Random is %d\n", rand());
	
	return 0;
}
