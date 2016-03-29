#ifndef MONSTER_PARSER_H
#define MONSTER_PARSER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "CharacterController.h"

using namespace std;

//extern vector<monsterClass> parsedMonsters;

vector<monsterClass> parseMonsters(string fileName);


#endif