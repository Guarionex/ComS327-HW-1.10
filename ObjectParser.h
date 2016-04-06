#ifndef OBJECT_PARSER_H
#define OBJECT_PARSER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "dice.h"
#include <ncurses.h>

using namespace std;

//extern vector<monsterClass> parsedMonsters;

typedef enum object_type {
  objtype_no_type,
  objtype_WEAPON,
  objtype_OFFHAND,
  objtype_RANGED,
  objtype_LIGHT,
  objtype_ARMOR,
  objtype_HELMET,
  objtype_CLOAK,
  objtype_GLOVES,
  objtype_BOOTS,
  objtype_AMULET,
  objtype_RING,
  objtype_SCROLL,
  objtype_BOOK,
  objtype_FLASK,
  objtype_GOLD,
  objtype_AMMUNITION,
  objtype_FOOD,
  objtype_WAND,
  objtype_CONTAINER
} object_type_t;

class objectClass
{
	public:
	string name;
	string description;
	object_type_t type;
	short color;
	Dice hit;
	Dice damage;
	Dice dodge;
	Dice defence;
	Dice weight;
	Dice speed;
	Dice attribute;
	Dice value;
	
	bool equipment;
	char symbol;
	bool twoHanded;
	
	objectClass() : name(), description(), type(objtype_no_type), color(-1), hit(), damage(), dodge(), defence(), weight(), speed(), attribute(), value(), equipment(false), symbol(''), twoHanded(false)
	{	
	}
	~objectClass();
};

vector<objectClass> parseObjects();


#endif