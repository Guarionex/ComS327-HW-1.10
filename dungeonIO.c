#include "dungeonIO.h"
#include <stdio.h>

Flags *flags;

bool Contains_Flag(Flags *flag, int size, Flags contains)
{
	int f;
	for(f = 0; f < size; f++)
	{
		printf("flag = %d\n", flag[f]);
		if(flag[f] == contains)
		{
			
			return TRUE;
		}
	}
	
	return FALSE;
}