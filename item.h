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
	bool offensiveMagic;
	bool defensiveMagic;
	
	itemClass() : name("Empty"), description("This slot is empty"), type(objtype_no_type), color(-1), hit(0), damage(Dice()), dodge(0), defence(0), weight(0), speed(0), attribute(0), value(0), equipment(false), symbol('*'), twoHanded(false), pos(NULL_POS), item_stack(false), offensiveMagic(false), defensiveMagic(false)
	{	
	}
	itemClass(objectClass obj);
	~itemClass();
	
};

class projectileClass
{
	public:
	string name;
	short color;
	pos_t pos;
	pos_t direction;
	int damage;
	
	projectileClass() : name(), color(-1), pos(NULL_POS), direction(NULL_POS), damage(0)
	{
	}
	projectileClass(string newName, short newColor, pos_t newPos, pos_t newDirection, int newDamage);
	~projectileClass();
};

vector<itemClass> placeItems(Dungeon_Space_Struct **dungeon, vector<objectClass> objectsToPlace, stair_t down, stair_t *up);
void drop_itemAt(vector<itemClass> *listOfItems, itemClass dropping, int x, int y);
bool containsItemAt(vector<itemClass> search, int x, int y);
vector<itemClass> getItemsAt(vector<itemClass> search, int x, int y);
void removeItemAt(vector<itemClass> *search, int x, int y, string nameToRemove);
bool containsProjAt(vector<projectileClass> search, int x, int y);
vector<projectileClass> getProjAt(vector<projectileClass> search, int x, int y);
void removeProjAt(vector<projectileClass> *search, int x, int y, string nameToRemove);


#endif