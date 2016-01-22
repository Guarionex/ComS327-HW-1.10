#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	time_t seed = time(NULL);
	srand(seed);
	printf("Random is %d\n", rand());
	printf("Random is %d\n", rand());
	printf("Random is %d\n", rand());
	
	return 0;
}
