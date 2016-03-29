#include "dice.h"

Dice::Dice();
{
	base = 0;
	dice = 0;
	sides = 0;
}
Dice::Dice(int nBase, int nDice, int nSides)
{
	base = nBase;
	dice = nDice;
	sides = nSides;
}
Dice::~Dice()
{
	base = 0;
	dice = 0;
	sides = 0;
}
int Dice::roll(int seed)
{
	if(seed < 0)
	{
		srand(time(NULL));
	}
	else
	{
		srand(seed);
	}
	int roll = base + (dice * ((rand()%8) + 1));
	return roll;
}
std::string Dice::toString();