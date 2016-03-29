#include "MonsterParser.h"

vector<monsterClass> monsterList;

vector<monsterClass> parseMonsters(string fileName)
{
	string line;
	ifstream monsterFile(fileName);
	
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
}