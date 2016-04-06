#ifndef ITEM_PARSER_H
#define ITEM_PARSER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "dice.h"
#include <ncurses.h>
#include "ObjectParser.h"
#include "dungeonObjects.h"

using namespace std;

class itemClass
{
	public:
	string name;
	string description;
	object_type_t type;
	short color;
	int hit;
	int damage;
	int dodge;
	int defense;
	int weight;
	int speed;
	int attribute;
	int value;
	bool equipment;
	char symbol;
	bool twoHanded;
	pos_t pos;
	bool item_stack;
	
	itemClass() : name(), description(), type(objtype_no_type), color(-1), hit(0), damage(0), dodge(0), defence(0), weight(0), speed(0), attribute(0), value(0), equipment(false), symbol('*'), twoHanded(false), pos(NULL_POS), item_stack(false)
	{	
	}
	itemClass(objectClass obj);
	~itemClass();
	
};

vector<itemClass> placeItems(Dungeon_Space_Struct **dungeon, vector<objectClass> objectsToPlace, stair_t down, stair_t *up);

#endif