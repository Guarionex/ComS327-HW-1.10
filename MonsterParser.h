#ifndef MONSTER_PARSER_H
#define MONSTER_PARSER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctype.h>
#include "CharacterController.h"
#include <ncurses.h>

using namespace std;

//extern vector<monsterClass> parsedMonsters;

vector<monsterClass> parseMonsters();


#endif