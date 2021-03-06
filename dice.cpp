#include "dice.h"

Dice::Dice()
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
	/*if(seed < 0)
	{
		srand(time(NULL));
	}
	else
	{
		srand(seed);
	}*/
	int r, roll = 0;
	for(r = 0; r < dice; r++)
	{
		roll += ((rand()%sides) + 1);
	}
	roll = base + roll;
	return roll;
}

string Dice::toString()
{
	string diceString = static_cast<ostringstream*>( &(ostringstream() << base) )->str() + "+";
	diceString += static_cast<ostringstream*>( &(ostringstream() << dice) )->str() + "d";
	diceString += static_cast<ostringstream*>( &(ostringstream() << sides) )->str();
	return diceString;
}