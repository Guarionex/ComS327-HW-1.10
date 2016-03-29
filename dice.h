#ifndef DICE_H
#define DICE_H

#include <stdlib.h>
#include <time.h> 

class Dice
{
	public:
	int base;
	int dice;
	int sides;
	
	Dice();
	Dice(int nBase, int nDice, int nSides);
	~Dice();
	int roll(int seed);
	std::string toString();
};

#endif