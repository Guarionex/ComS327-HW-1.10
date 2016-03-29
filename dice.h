#ifndef DICE_H
#define DICE_H

#include <stdlib.h>
#include <time.h> 
#include <sstream>
#include <string>

using namespace std;

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
	string toString();
};

#endif