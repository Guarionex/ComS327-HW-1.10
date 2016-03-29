#include "MonsterParser.h"

vector<monsterClass> monsterList;

vector<monsterClass> parseMonsters()
{
	string line;
	string file = "/.rlg327/monster_desc.txt";
	string home = getenv("HOME");
	ifstream monsterFile((home + file).c_str());
	bool beginMonster = name = description = color = speed = ability = hp = damage = false;
	
	if(monsterFile.is_open())
	{
		if(line.compare("RLG327 MONSTER DESCRIPTION 1") != 0)
		{
			return monsterList;
		}
		while(getline(monsterFile, line))
		{
			cout << "line: " << line << "| comapre result = " << line.compare("RLG327 MONSTER DESCRIPTION 1") << endl;
			if(line.compare("RLG327 MONSTER DESCRIPTION 1") == 0)
			{
				cout << "header same" << endl;
			}
			
		}
		monsterFile.close();
	}
	
	return monsterList;
}