#include "ObjectParser.h"

vector<objectClass> objectList;

vector<objectClass> parseObjects()
{
	string line;
	string file = "/.rlg327/object_desc.txt";
	string home = getenv("HOME");
	ifstream objectFile((home + file).c_str());
	bool beginObject, name, description, type, color, hit, dodge, def, weight, attr, val, speed, damage, endObject, readingDesc;
	beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = readingDesc = false;
	objectClass obj;
	
	if(objectFile.is_open())
	{
		getline(objectFile, line);
		if(line.compare("RLG327 OBJECT DESCRIPTION 1") != 0)
		{
			return objectList;
		}
		while(getline(objectFile, line))
		{
			if(!beginObject && !name && !description && !type && !color && !hit && !dodge && !def && !weight && !attr && !val && !speed && !damage && !endObject && line.compare("BEGIN OBJECT") == 0)
			{
				beginObject = true;
			}
			else if(beginObject == true)
			{
				size_t found;
				if((found = line.find("NAME ")) != string::npos && found == 0 && !readingDesc)
				{
					if(!name)
					{
						name = true;
						obj.name = line.substr(line.find_first_not_of(" ", 5));
						//cout << "Monster's name = " << obj.name << endl;
					}
					else
					{
						beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
						obj = objectClass();
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
							//cout << "Monster's description = " << obj.description << endl;
						}
						else if(line.size() <= 78)
						{
							obj.description += line + '\n';
						}
					}
					else
					{
						beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
						obj = objectClass();
						//skip monster
					}
				}
				else if((found = line.find("TYPE ")) != string::npos && found == 0)
				{
					if(!type)
					{
						type = true;
						//obj.type = line.substr(line.find_first_not_of(" ", 5))[0];
						int index = 5;
						string objType;
						object_type_t parsedObjType = objtype_no_type;
						bool gotType = false;
						bool isEquipment = false;
						bool isTwoHanded = false;
						char objSymbol = '*';
						//cout << "Monster powers = ";
						while((objType = line.substr(line.find_first_not_of(" ", index), line.find_first_of(" ", index) - index)).compare("") != 0)
						{
							//cout << "Testing " << objType << endl;
							if(objType.compare("WEAPON") == 0 && !gotType)
							{
								parsedObjType = objtype_WEAPON;
								gotType = true;
								isEquipment = true;
								objSymbol = '|';
							}
							else if(objType.compare("OFFHAND") == 0)
							{
								if(gotType)
								{
									isTwoHanded = true;
									objSymbol = '^';
									break;
								}
								parsedObjType = objtype_OFFHAND;
								gotType = true;
								isEquipment = true;
								objSymbol = ')';
							}
							else if(objType.compare("RANGED") == 0 && !gotType)
							{
								parsedObjType = objtype_RANGED;
								gotType = true;
								isEquipment = true;
							objSymbol = '}';
							}
							else if(objType.compare("ARMOR") == 0 && !gotType)
							{
								parsedObjType = objtype_ARMOR;
								gotType = true;
								isEquipment = true;
								objSymbol = '[';
							}
							else if(objType.compare("HELMET") == 0 && !gotType)
							{
								parsedObjType = objtype_HELMET;
								gotType = true;
								isEquipment = true;
								objSymbol = ']';
							}
							else if(objType.compare("CLOAK") == 0 && !gotType)
							{
								parsedObjType = objtype_CLOAK;
								gotType = true;
								isEquipment = true;
								objSymbol = '(';
							}
							else if(objType.compare("GLOVES") == 0 && !gotType)
							{
								parsedObjType = objtype_GLOVES;
								gotType = true;
								isEquipment = true;
								objSymbol = '{';
							}
							else if(objType.compare("BOOTS") == 0 && !gotType)
							{
								parsedObjType = objtype_BOOTS;
								gotType = true;
								isEquipment = true;
								objSymbol = '\\';
							}
							else if(objType.compare("RING") == 0 && !gotType)
							{
								parsedObjType = objtype_RING;
								gotType = true;
								isEquipment = true;
								objSymbol = '=';
							}
							else if(objType.compare("AMULET") == 0 && !gotType)
							{
								parsedObjType = objtype_AMULET;
								gotType = true;
								isEquipment = true;
								objSymbol = '"';
							}
							else if(objType.compare("LIGHT") == 0 && !gotType)
							{
								parsedObjType = objtype_LIGHT;
								gotType = true;
								isEquipment = true;
								objSymbol = '_';
							}
							else if(objType.compare("SCROLL") == 0 && !gotType)
							{
								parsedObjType = objtype_SCROLL;
								gotType = true;
								objSymbol = '~';
							}
							else if(objType.compare("BOOK") == 0 && !gotType)
							{
								parsedObjType = objtype_BOOK;
								gotType = true;
								objSymbol = '?';
							}
							else if(objType.compare("FLASK") == 0 && !gotType)
							{
								parsedObjType = objtype_FLASK;
								gotType = true;
								objSymbol = '!';
							}
							else if(objType.compare("GOLD") == 0 && !gotType)
							{
								parsedObjType = objtype_GOLD;
								gotType = true;
								objSymbol = '$';
							}
							else if(objType.compare("AMMUNITION") == 0 && !gotType)
							{
								parsedObjType = objtype_AMMUNITION;
								gotType = true;
								objSymbol = '/';
							}
							else if(objType.compare("FOOD") == 0 && !gotType)
							{
								parsedObjType = objtype_FOOD;
								gotType = true;
								objSymbol = ',';
							}
							else if(objType.compare("WAND") == 0 && !gotType)
							{
								parsedObjType = objtype_WAND;
								gotType = true;
								objSymbol = '-';
							}
							else if(objType.compare("CONTAINER") == 0 && !gotType)
							{
								parsedObjType = objtype_CONTAINER;
								gotType = true;
								objSymbol = '%';
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
						obj.type = parsedObjType;
						obj.equipment = isEquipment;
						obj.twoHanded = isTwoHanded;
						obj.symbol = objSymbol;
						//cout << "Monster type = " << obj.type << endl;
					}
					else
					{
						beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
						obj = objectClass();
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
							obj.color = COLOR_RED;
						}
						else if(colorName.compare("GREEN") == 0)
						{
							obj.color = COLOR_GREEN;
						}
						else if(colorName.compare("BLUE") == 0)
						{
							obj.color = COLOR_BLUE;
						}
						else if(colorName.compare("CYAN") == 0)
						{
							obj.color = COLOR_CYAN;
						}
						else if(colorName.compare("YELLOW") == 0)
						{
							obj.color = COLOR_YELLOW;
						}
						else if(colorName.compare("MAGENTA") == 0)
						{
							obj.color = COLOR_MAGENTA;
						}
						else if(colorName.compare("WHITE") == 0)
						{
							obj.color = COLOR_WHITE;
						}
						else if(colorName.compare("BLACK") == 0)
						{
							obj.color = COLOR_BLACK;
						}
						else
						{
							//skip monster
						}
						//cout << "Monster color = " << obj.color << endl;
					}
					else
					{
						beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
						obj = objectClass();
						//skip monster
					}
				}
				else if((found = line.find("HIT ")) != string::npos && found == 0)
				{
					if(!hit)
					{
						hit = true;
						int base = -1, dice = -1, sides = -1;
						
						string baseRaw = line.substr(line.find_first_not_of(" ", 4), (dice = line.find_first_of("+", 4)) - 4);
						if(!isdigit(baseRaw.c_str()[0]) || dice == -1)
						{
							beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
							obj = objectClass();
							//skip monster
						}
						else
						{
							dice++;
						}
						base = atoi(baseRaw.c_str());
						
						string diceRaw = line.substr(line.find_first_not_of(" ", dice), (sides = line.find_first_of("d", dice)) - dice);
						if(!isdigit(diceRaw.c_str()[0]) || sides == -1)
						{
							beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
							obj = objectClass();
							//skip monster
						}
						else
						{
							sides++;
						}
						dice = atoi(diceRaw.c_str());
						
						string sidesRaw = line.substr(line.find_first_not_of(" ", sides));
						if(!isdigit(sidesRaw.c_str()[0]))
						{
							beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
							obj = objectClass();
							//skip monster
						}
						sides = atoi(sidesRaw.c_str());
						
						Dice hitDice(base, dice, sides);
						obj.hit = hitDice;
						
						//cout << "Monster speed = " << obj.damage.toString() << endl;
					}
					else
					{
						beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
						obj = objectClass();
						//skip monster
					}
				}
				else if((found = line.find("DODGE ")) != string::npos && found == 0)
				{
					if(!dodge)
					{
						dodge = true;
						int base = -1, dice = -1, sides = -1;
						
						string baseRaw = line.substr(line.find_first_not_of(" ", 6), (dice = line.find_first_of("+", 6)) - 6);
						if(!isdigit(baseRaw.c_str()[0]) || dice == -1)
						{
							beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
							obj = objectClass();
							//skip monster
						}
						else
						{
							dice++;
						}
						base = atoi(baseRaw.c_str());
						
						string diceRaw = line.substr(line.find_first_not_of(" ", dice), (sides = line.find_first_of("d", dice)) - dice);
						if(!isdigit(diceRaw.c_str()[0]) || sides == -1)
						{
							beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
							obj = objectClass();
							//skip monster
						}
						else
						{
							sides++;
						}
						dice = atoi(diceRaw.c_str());
						
						string sidesRaw = line.substr(line.find_first_not_of(" ", sides));
						if(!isdigit(sidesRaw.c_str()[0]))
						{
							beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
							obj = objectClass();
							//skip monster
						}
						sides = atoi(sidesRaw.c_str());
						
						Dice dodgeDice(base, dice, sides);
						obj.dodge = dodgeDice;
						
						//cout << "Monster speed = " << obj.damage.toString() << endl;
					}
					else
					{
						beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
						obj = objectClass();
						//skip monster
					}
				}
				else if((found = line.find("DEF ")) != string::npos && found == 0)
				{
					if(!def)
					{
						def = true;
						int base = -1, dice = -1, sides = -1;
						
						string baseRaw = line.substr(line.find_first_not_of(" ", 4), (dice = line.find_first_of("+", 4)) - 4);
						if(!isdigit(baseRaw.c_str()[0]) || dice == -1)
						{
							beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
							obj = objectClass();
							//skip monster
						}
						else
						{
							dice++;
						}
						base = atoi(baseRaw.c_str());
						
						string diceRaw = line.substr(line.find_first_not_of(" ", dice), (sides = line.find_first_of("d", dice)) - dice);
						if(!isdigit(diceRaw.c_str()[0]) || sides == -1)
						{
							beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
							obj = objectClass();
							//skip monster
						}
						else
						{
							sides++;
						}
						dice = atoi(diceRaw.c_str());
						
						string sidesRaw = line.substr(line.find_first_not_of(" ", sides));
						if(!isdigit(sidesRaw.c_str()[0]))
						{
							beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
							obj = objectClass();
							//skip monster
						}
						sides = atoi(sidesRaw.c_str());
						
						Dice defDice(base, dice, sides);
						obj.defence = defDice;
						
						//cout << "Monster speed = " << obj.damage.toString() << endl;
					}
					else
					{
						beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
						obj = objectClass();
						//skip monster
					}
				}
				else if((found = line.find("WEIGHT ")) != string::npos && found == 0)
				{
					if(!weight)
					{
						weight = true;
						int base = -1, dice = -1, sides = -1;
						
						string baseRaw = line.substr(line.find_first_not_of(" ", 7), (dice = line.find_first_of("+", 7)) - 7);
						if(!isdigit(baseRaw.c_str()[0]) || dice == -1)
						{
							beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
							obj = objectClass();
							//skip monster
						}
						else
						{
							dice++;
						}
						base = atoi(baseRaw.c_str());
						
						string diceRaw = line.substr(line.find_first_not_of(" ", dice), (sides = line.find_first_of("d", dice)) - dice);
						if(!isdigit(diceRaw.c_str()[0]) || sides == -1)
						{
							beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
							obj = objectClass();
							//skip monster
						}
						else
						{
							sides++;
						}
						dice = atoi(diceRaw.c_str());
						
						string sidesRaw = line.substr(line.find_first_not_of(" ", sides));
						if(!isdigit(sidesRaw.c_str()[0]))
						{
							beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
							obj = objectClass();
							//skip monster
						}
						sides = atoi(sidesRaw.c_str());
						
						Dice weightDice(base, dice, sides);
						obj.weight = weightDice;
						
						//cout << "Monster speed = " << obj.damage.toString() << endl;
					}
					else
					{
						beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
						obj = objectClass();
						//skip monster
					}
				}
				else if((found = line.find("SPEED ")) != string::npos && found == 0)
				{
					if(!speed)
					{
						speed = true;
						int base = -1, dice = -1, sides = -1;
						
						string baseRaw = line.substr(line.find_first_not_of(" ", 6), (dice = line.find_first_of("+", 6)) - 6);
						if(!isdigit(baseRaw.c_str()[0]) || dice == -1)
						{
							beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
							obj = objectClass();
							//skip monster
						}
						else
						{
							dice++;
						}
						base = atoi(baseRaw.c_str());
						
						string diceRaw = line.substr(line.find_first_not_of(" ", dice), (sides = line.find_first_of("d", dice)) - dice);
						if(!isdigit(diceRaw.c_str()[0]) || sides == -1)
						{
							beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
							obj = objectClass();
							//skip monster
						}
						else
						{
							sides++;
						}
						dice = atoi(diceRaw.c_str());
						
						string sidesRaw = line.substr(line.find_first_not_of(" ", sides));
						if(!isdigit(sidesRaw.c_str()[0]))
						{
							beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
							obj = objectClass();
							//skip monster
						}
						sides = atoi(sidesRaw.c_str());
						
						Dice speedDice(base, dice, sides);
						obj.speed = speedDice;
						
						//cout << "Monster speed = " << obj.speed.toString() << endl;
					}
					else
					{
						beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
						obj = objectClass();
						//skip monster
					}
				}
				else if((found = line.find("DAM ")) != string::npos && found == 0)
				{
					if(!damage)
					{
						damage = true;
						int base = -1, dice = -1, sides = -1;
						
						string baseRaw = line.substr(line.find_first_not_of(" ", 4), (dice = line.find_first_of("+", 4)) - 4);
						if(!isdigit(baseRaw.c_str()[0]) || dice == -1)
						{
							beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
							obj = objectClass();
							//skip monster
						}
						else
						{
							dice++;
						}
						base = atoi(baseRaw.c_str());
						
						string diceRaw = line.substr(line.find_first_not_of(" ", dice), (sides = line.find_first_of("d", dice)) - dice);
						if(!isdigit(diceRaw.c_str()[0]) || sides == -1)
						{
							beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
							obj = objectClass();
							//skip monster
						}
						else
						{
							sides++;
						}
						dice = atoi(diceRaw.c_str());
						
						string sidesRaw = line.substr(line.find_first_not_of(" ", sides));
						if(!isdigit(sidesRaw.c_str()[0]))
						{
							beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
							obj = objectClass();
							//skip monster
						}
						sides = atoi(sidesRaw.c_str());
						
						Dice damageDice(base, dice, sides);
						obj.damage = damageDice;
						
						//cout << "Monster speed = " << obj.damage.toString() << endl;
					}
					else
					{
						beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
						obj = objectClass();
						//skip monster
					}
				}
				else if((found = line.find("ATTR ")) != string::npos && found == 0)
				{
					if(!attr)
					{
						attr = true;
						int base = -1, dice = -1, sides = -1;
						
						string baseRaw = line.substr(line.find_first_not_of(" ", 5), (dice = line.find_first_of("+", 5)) - 5);
						if(!isdigit(baseRaw.c_str()[0]) || dice == -1)
						{
							beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
							obj = objectClass();
							//skip monster
						}
						else
						{
							dice++;
						}
						base = atoi(baseRaw.c_str());
						
						string diceRaw = line.substr(line.find_first_not_of(" ", dice), (sides = line.find_first_of("d", dice)) - dice);
						if(!isdigit(diceRaw.c_str()[0]) || sides == -1)
						{
							beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
							obj = objectClass();
							//skip monster
						}
						else
						{
							sides++;
						}
						dice = atoi(diceRaw.c_str());
						
						string sidesRaw = line.substr(line.find_first_not_of(" ", sides));
						if(!isdigit(sidesRaw.c_str()[0]))
						{
							beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
							obj = objectClass();
							//skip monster
						}
						sides = atoi(sidesRaw.c_str());
						
						Dice attrDice(base, dice, sides);
						obj.attribute = attrDice;
						
						//cout << "Monster speed = " << obj.damage.toString() << endl;
					}
					else
					{
						beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
						obj = objectClass();
						//skip monster
					}
				}
				else if((found = line.find("VAL ")) != string::npos && found == 0)
				{
					if(!val)
					{
						val = true;
						int base = -1, dice = -1, sides = -1;
						
						string baseRaw = line.substr(line.find_first_not_of(" ", 4), (dice = line.find_first_of("+", 4)) - 4);
						if(!isdigit(baseRaw.c_str()[0]) || dice == -1)
						{
							beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
							obj = objectClass();
							//skip monster
						}
						else
						{
							dice++;
						}
						base = atoi(baseRaw.c_str());
						
						string diceRaw = line.substr(line.find_first_not_of(" ", dice), (sides = line.find_first_of("d", dice)) - dice);
						if(!isdigit(diceRaw.c_str()[0]) || sides == -1)
						{
							beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
							obj = objectClass();
							//skip monster
						}
						else
						{
							sides++;
						}
						dice = atoi(diceRaw.c_str());
						
						string sidesRaw = line.substr(line.find_first_not_of(" ", sides));
						if(!isdigit(sidesRaw.c_str()[0]))
						{
							beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
							obj = objectClass();
							//skip monster
						}
						sides = atoi(sidesRaw.c_str());
						
						Dice valDice(base, dice, sides);
						obj.value = valDice;
						
						//cout << "Monster speed = " << obj.damage.toString() << endl;
					}
					else
					{
						beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
						obj = objectClass();
						//skip monster
					}
				}
				else if(line.compare("END") == 0)
				{
					endObject = true;
					//cout << "begin=" << beginObject << " name="<< name << " desc=" << description << " type=" << type << " color=" << color << " speed=" << speed << " ability=" << ability << " hp=" << hp << " dam=" << damage << " end=" << endObject << endl;
					//beginObject = name = description = type = color = speed = ability = hp = damage = endObject = false;
					//delete obj;
					//obj = new objectClass();
					if(beginObject && name && description && type && color && hit && dodge && def && weight && attr && val && speed && damage && endObject )
					{
						beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
						//cout << "I'm here" << endl;
						objectList.push_back(obj);
						obj = objectClass();
					}
					else
					{
						beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
						obj = objectClass();
						//skip monster
					}
				}
				else if(line.compare("") != 0)
				{
					beginObject = name = description = type = color = hit = dodge = def = weight = attr = val = speed = damage = endObject = false;
					obj = objectClass();
					//skip monster
				}
			}
			//cout << "line: " << line << " | comapre result = " << line.compare("RLG327 MONSTER DESCRIPTION 1") << endl;
			
			
		}
		objectFile.close();
	}
	
	return objectList;
}