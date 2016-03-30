#include "MonsterParser.h"

vector<monsterClass> monsterList;

vector<monsterClass> parseMonsters()
{
	string line;
	string file = "/.rlg327/monster_desc.txt";
	string home = getenv("HOME");
	ifstream monsterFile((home + file).c_str());
	bool beginMonster, name, description, symbol, color, speed, ability, hp, damage, endMonster;
	beginMonster = name = description = symbol = color = speed = ability = hp = damage = endMonster = false;
	monsterClass *mon = new monsterClass();
	
	if(monsterFile.is_open())
	{
		getline(monsterFile, line);
		if(line.compare("RLG327 MONSTER DESCRIPTION 1") != 0)
		{
			return monsterList;
		}
		while(getline(monsterFile, line))
		{
			if(beginMonster == false && name == false && description == false && symbol == false && color == false && speed == false && ability == false && hp == false && damage == false && endMonster == false && line.compare("BEGIN MONSTER") == 0)
			{
				beginMonster = true;
			}
			else if(beginMonster == true)
			{
				size_t found;
				if((found = line.find("NAME ")) != string::npos && found == 0)
				{
					if(name == false)
					{
						name = true;
						mon->name = line.substr(5);
						cout << "Monster's name = " << mon->name << endl;
					}
					else
					{
						//skipp monster
					}
				}
				
				if(line.compare("END") == 0)
				{
					beginMonster = name = description = symbol = color = speed = ability = hp = damage = endMonster = false;
					if(beginMonster == true && name == true && description == true && symbol == true && color == true && speed == true && ability == true && hp == true && damage == true && endMonster == true )
					{
						beginMonster = name = description = symbol = color = speed = ability = hp = damage = endMonster = false;
						//add monster
					}
					else
					{
						//skip monster
					}
				}
			}
			//cout << "line: " << line << " | comapre result = " << line.compare("RLG327 MONSTER DESCRIPTION 1") << endl;
			
			
		}
		monsterFile.close();
	}
	
	return monsterList;
}