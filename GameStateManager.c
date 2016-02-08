#include "GameStateManager.h"

Dungeon_Space_Struct **current_dungeon;
player_t pc;

void Set_Dungeon(Dungeon_Space_Struct **dungeon)
{
	current_dungeon = dungeon;
}

void Set_Player(player_t player)
{
	pc = player;
}

char **Generate_Distance_Dungeon(void)
{
	graph_t graphed_dungeon = GenerateGraph(current_dungeon);
	/*vertex_t player_vertex*/ = Get_Vertex(pc.pos.x, pc.pos.y);
	
	char **char_dungeon;
	char_dungeon = malloc(80 * sizeof(char *));
	int x;
	for(x = 0; x < 80; x++)
	{
		char_dungeon = malloc(21 * sizeof(char));	
	}
	
	int numVertex = graphed_dungeon.num_vertices;
	int t;
	for(t = 0; t < numVertex; t++)
	{
		printf("Vertex[%d]: weight=%d, x=%d, y=%d\n", t, graphed_dungeon.vertices[t].weight, graphed_dungeon.vertices[t].x, graphed_dungeon.vertices[t].y);
	}
	
	//Dijkstra(graphed_dungeon, player_vertex);
	
	return char_dungeon;
}

void Draw_Dungeon(void)
{
	int x;
	int y;
	for(y = 0; y < 21; y++)
	{
		for(x = 0; x < 80; x++)
		{
			if(pc.pos.x == x && pc.pos.y == y)
			{
				printf("@");
			}
			else
			{
				switch(current_dungeon[x][y].space_type)
				{
					case ROCK :
					
						if(current_dungeon[x][y].space_union.rock.density == 255)
						{
							printf("R");
						}
						else printf(" ");
					
					break;
					case ROOM :
					
						printf(".");
					
					break;
					case CORRIDOR :
						printf("#");
					break;
				}
			}
		}
		printf("\n");
	}
}

void Draw_Distance_Dungeon(char **char_map)
{
	
}