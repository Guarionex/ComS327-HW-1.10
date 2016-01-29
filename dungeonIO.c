#include "dungeonIO.h"
#include <stdio.h>

bool Contains_Flag(Flags *flag, int size, Flags contains)
{
	int f;
	for(f = 0; f < size; f++)
	{
		printf("flag = %d\n", flag[f]);
		switch(contains)
		{
			case SEED:
				if(flag[f] == SEED) return TRUE;
			break;
			
			case SAVE:
				if(flag[f] == SAVE) return TRUE;
			break;
			
			case LOAD:
				if(flag[f] == LOAD) return TRUE;
			break;
		}
	}
	
	return FALSE;
}