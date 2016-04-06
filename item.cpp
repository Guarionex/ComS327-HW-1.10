#include "item.h"

vector<itemClass> dungeonItems;

itemClass::itemClass(objectClass obj)
{
	name = obj.name;
	description = obj.description;
	type = obj.type;
	color = obj.color;
	hit = obj.hit.roll();
	damage = obj.damage.roll();
	dodge = obj.dodge.roll();
	defence = obj.defence.roll();
	weight = obj.weight.roll();
	speed = obj.speed.roll();
	attribute = obj.attribute.roll();
	value = obj.value.roll();
	equipment = obj.equipment;
	symbol = obj.symbol;
	twoHanded = obj.twoHanded;
}

itemClass::~itemClass()
{
	name = "";
	description = "";
	type = objtype_no_type;
	color = -1;
	hit = -1;
	damage = -1;
	dodge = -1;
	defence = -1;
	weight = -1;
	speed = -1;
	attribute = -1;
	value = -1;
	equipment = false;
	symbol = '*';
	twoHanded = false;
	pos = NULL_POS;
	item_stack = false;
}

vector<itemClass> placeItems(Dungeon_Space_Struct **dungeon, vector<objectClass> objectsToPlace, stair_t down, stair_t *up)
{
	int ol;
	for(ol = 0; ol < objectsToPlace.size(); ol++)
	{
		pos_t *open_pos = (pos_t *) malloc(sizeof(pos_t));
		open_pos[0] = NULL_POS;
		itemClass newItem = item(objectsToPlace[ol]);
		
		int x, y, open_count = 0;
		for(x = 0; x < 80; x++)
		{
			for(y = 0; y < 21; y++)
			{
				pos_t new_pos;
				switch(dungeon[x][y].space_type)
				{
					case ROCK:
					break;
					
					case ROOM:
						if((down.location.x != x && down.location.y != y) || (up != NULL && up.location.x != x && up.location.y != y))
						{
							new_pos.x = x;
							new_pos.y = y;
							open_count++;
							open_pos = (pos_t *) realloc(open_pos, sizeof(pos_t) + (sizeof(pos_t) * open_count));
							open_pos[open_count-1] = new_pos;
							open_pos[open_count] = NULL_POS;
						}
					break;
					
					case CORRIDOR:
						if((down.location.x != x && down.location.y != y) || (up != NULL && up.location.x != x && up.location.y != y))
						{
							new_pos.x = x;
							new_pos.y = y;
							open_count++;
							open_pos = (pos_t *) realloc(open_pos, sizeof(pos_t) + (sizeof(pos_t) * open_count));
							open_pos[open_count-1] = new_pos;
							open_pos[open_count] = NULL_POS;
						}
					break;
				}
			}
		}
		
		
		pos_t new_pos = open_pos[rand()%open_count];
		newItem.pos = new_pos;
		int i;
		for(i = 0; i < dungeonItems.size(); i++)
		{
			if(dungeonItems[i].pos.x == newItem.pos.x && dungeonItems[i].pos.y == newItem.pos.y)
			{
				dungeonItems[i].item_stack = true;
				newItem.item_stack = true;
			}
		}
		dungeonItems.push_back(newItem);

		free(open_pos);
	}
	return dungeonItems;
}