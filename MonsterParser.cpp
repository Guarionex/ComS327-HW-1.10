#include "MonsterParser.h"

vector<monsterClass> monsterList;

vector<monsterClass> parseMonsters()
{
	string line;
	string file = "/.rlg327/monster_desc.txt";
	string home = getenv("HOME");
	ifstream monsterFile((home + file).c_str());
	bool beginMonster, name, description, symbol, color, speed, ability, hp, damage, endMonster, readingDesc;
	beginMonster = name = description = symbol = color = speed = ability = hp = damage = endMonster = readingDesc = false;
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
				if((found = line.find("NAME ")) != string::npos && found == 0 && !readingDesc)
				{
					if(!name)
					{
						name = true;
						mon->name = line.substr(line.find_first_not_of(" ", 5));
						//cout << "Monster's name = " << mon->name << endl;
					}
					else
					{
						//skipp monster
					}
				}
				else if(line.compare("DESC") == 0 || readingDesc)
				{
					if(!description)
					{
						if(!readingDesc)
						{
							readingDesc = true;
						}
						else if(line.compare(".") == 0)
						{
							readingDesc = false;
							description = true;
							//cout << "Monster's description = " << mon->description << endl;
						}
						else if(line.size() <= 78)
						{
							mon->description += line + '\n';
						}
					}
					else
					{
						//skip monster
					}
				}
				else if((found = line.find("SYMB ")) != string::npos && found == 0)
				{
					if(!symbol)
					{
						mon->symbol = line.substr(line.find_first_not_of(" ", 5))[0];
						//cout << "Monster symbol = " << mon->symbol << endl;
					}
					else
					{
						//skip monster
					}
				}
				else if((found = line.find("COLOR ")) != string::npos && found == 0)
				{
					if(!color)
					{ 
						color = true;
						string colorName = line.substr(line.find_first_not_of(" ", 6));
						if(colorName.compare("RED") == 0)
						{
							mon->color = COLOR_RED;
						}
						else if(colorName.compare("GREEN") == 0)
						{
							mon->color = COLOR_GREEN;
						}
						else if(colorName.compare("BLUE") == 0)
						{
							mon->color = COLOR_BLUE;
						}
						else if(colorName.compare("CYAN") == 0)
						{
							mon->color = COLOR_CYAN;
						}
						else if(colorName.compare("YELLOW") == 0)
						{
							mon->color = COLOR_YELLOW;
						}
						else if(colorName.compare("MAGENTA") == 0)
						{
							mon->color = COLOR_MAGENTA;
						}
						else if(colorName.compare("WHITE") == 0)
						{
							mon->color = COLOR_WHITE;
						}
						else if(colorName.compare("BLACK") == 0)
						{
							mon->color = COLOR_BLACK;
						}
						else
						{
							//skip monster
						}
						//cout << "Monster color = " << mon->color << endl;
					}
					else
					{
						//skip monster
					}
				}
				else if((found = line.find("SPEED ")) != string::npos && found == 0)
				{
					if(!speed)
					{
						int base = -1;//, dice = -1, sides = -1;
						
						string baseRaw = line.substr(line.find_first_not_of(" ", 6), line.find_first_of("+", 6) - 6);
						if(!isdigit(baseRaw.c_str()))
						{
							//skip monster
						}
						base = atoi(baseRaw.c_str());
						
						cout << "Monster speed = " << base << endl;
					}
					else
					{
						//skip monster
					}
				}
				else if((found = line.find("ABIL ")) != string::npos && found == 0)
				{
					if(!ability)
					{
						int index = 5;
						string power;
						uint8_t abil = 0b00000;
						//cout << "Monster powers = ";
						while((power = line.substr(line.find_first_not_of(" ", index), line.find_first_of(" ", index) - index)).compare("") != 0)
						{
							//cout << power << endl;
							if(power.compare("SMART") == 0)
							{
								abil = abil | 0b00001;
							}
							else if(power.compare("TELE") == 0)
							{
								abil = abil | 0b00010;
							}
							else if(power.compare("TUNNEL") == 0)
							{
								abil = abil | 0b00100;
							}
							else if(power.compare("ERRATIC") == 0)
							{
								abil = abil | 0b01000;
							}
							else if(power.compare("PASS") == 0)
							{
								abil = abil | 0b10000;
							}
							else
							{
								//skip monster
							}
							if((index = line.find_first_of(" ", index)) == -1)
							{
								break;
								
							}
							else
							{
								index++;
							}
						}
						mon->set_abilities(abil);
						//printf("Monster ability is 0x%x\n", mon->get_abilities());
					}
					else
					{
						// skip monster
					}
				}
				else if(line.compare("END") == 0)
				{
					beginMonster = name = description = symbol = color = speed = ability = hp = damage = endMonster = false;
					delete mon;
					mon = new monsterClass();
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