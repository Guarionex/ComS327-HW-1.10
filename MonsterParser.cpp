#include "MonsterParser.h"

vector<monsterClass> monsterList;

vector<monsterClass> parseMonsters()
{
	string line;
	string file = "/.rlg327/monster_desc.txt";
	string home = getenv("HOME");
	ifstream monsterFile((home + file).c_str());
	
	if(monsterFile.is_open())
	{
		while(getline(monsterFile, line))
		{
			cout << "line: " << line << "| comapre result = " << line.compare("RLG327 MONSTER DESCRIPTION 1") << endl;
			if(line.compare("RLG327 MONSTER DESCRIPTION 1") == 0)
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