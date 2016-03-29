#include "MonsterParser.h"

vector<monsterClass> monsterList;

vector<monsterClass> parseMonsters()
{
	string line;
	ifstream monsterFile(getenv("HOME") + "/.rlg327/monster_desc.txt");
	
	if(monsterFile.is_open())
	{
		while(getline(monsterFile, line))
		{
			if(line.compare("RLG327 MONSTER DESCRIPTION 1"))
			{
				cout << "header same" << endl;
			}
			else
			{
				cout << "header not same" << endl;
			}
		}
		monsterFile.close();
	}
	
	return monsterList;
}