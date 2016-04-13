#ifndef ITEM_PARSER_H
#define ITEM_PARSER_H

#include "dungeonObjects.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "dice.h"
#include <ncurses.h>
#include "ObjectParser.h"

using namespace std;

class itemClass
{
	public:
	string name;
	string description;
	object_type_t type;
	short color;
	int hit;
	Dice damage;
	int dodge;
	int defence;
	int weight;
	int speed;
	int attribute;
	int value;
	bool equipment;
	char symbol;
	bool twoHanded;
	pos_t pos;
	bool item_stack;
	
	itemClass() : name("Null"), description(), type(objtype_no_type), color(-1), hit(0), damage(Dice()), dodge(0), defence(0), weight(0), speed(0), attribute(0), value(0), equipment(false), symbol('*'), twoHanded(false), pos(NULL_POS), item_stack(false)
	{	
	}
	itemClass(objectClass obj);
	~itemClass();
	
};

vector<itemClass> placeItems(Dungeon_Space_Struct **dungeon, vector<objectClass> objectsToPlace, stair_t down, stair_t *up);
bool containsItemAt(vector<itemClass> search, int x, int y);
vector<itemClass> getItemsAt(vector<itemClass> search, int x, int y);
void removeItemAt(vector<itemClass> *search, int x, int y, string nameToRemove);

#endif