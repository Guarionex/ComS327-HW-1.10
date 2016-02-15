#include "GameStateManager.h"

Dungeon_Space_Struct **current_dungeon;
player_t pc;
 char **distance_map;

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
	vertex_t player_vertex = Get_Vertex(pc.pos.x, pc.pos.y);
	uint distances_int[graphed_dungeon.num_vertices];
	
	char **char_dungeon;
	char_dungeon = malloc(80 * sizeof(char *));
	int x, y;
	for(x = 0; x < 80; x++)
	{
		char_dungeon = malloc(21 * sizeof(char));	
	}
	
	/*int numVertex = graphed_dungeon.num_vertices;
	int t;
	for(t = 0; t < numVertex; t++)
	{
		printf("Vertex[%d]: weight=%d, x=%d, y=%d\n", t, graphed_dungeon.vertices[t].weight, graphed_dungeon.vertices[t].x, graphed_dungeon.vertices[t].y);
	}*/
	
	Dijkstra(graphed_dungeon, player_vertex);
	
	int d;
	for(d = 0; d < graphed_dungeon.num_vertices; d++)
	{
		distances_int[d] = Get_Cost(graphed_dungeon.vertices[d]);
		//printf("Int at [%d][%d] in [%d] = %d\n", graphed_dungeon.vertices[d].x , graphed_dungeon.vertices[d].y, d, distances_int[d]);
	}
	//printf("Using distances_int = %d\n", distances_int[0]);
	for(y = 0; y < 21; y++)
	{
		for(x = 0; x < 80; x++)
		{
			//printf("Before char at [%d][%d] = %c\n", x, y, char_dungeon[x][y]);
			//printf("Int at [%d][%d] in [%d] = %d\n", x, y, y*80+x, distances_int[y*80+x]);
			//char_dungeon[x][y] = (char) distances_int[y*80+x];
			switch(distances_int[y*80+x])
			{
				case 0:
				char_dungeon[x][y] = '0';
				break;
				
				case 1:
				char_dungeon[x][y] = '1';
				break;
				
				case 2:
				char_dungeon[x][y] = '2';
				break;
				
				case 3:
				char_dungeon[x][y] = '3';
				break;
				
				case 4:
				char_dungeon[x][y] = '4';
				break;
				
				case 5:
				char_dungeon[x][y] = '5';
				break;
				
				case 6:
				char_dungeon[x][y] = '6';
				break;
				
				case 7:
				char_dungeon[x][y] = '7';
				break;
				
				case 8:
				char_dungeon[x][y] = '8';
				break;
				
				case 9:
				char_dungeon[x][y] = '9';
				break;
				
				case 10:
				char_dungeon[x][y] = 'a';
				break;
				
				case 11:
				char_dungeon[x][y] = 'b';
				break;
				
				case 12:
				char_dungeon[x][y] = 'c';
				break;
				
				case 13:
				char_dungeon[x][y] = 'd';
				break;
				
				case 14:
				char_dungeon[x][y] = 'e';
				break;
				
				case 15:
				char_dungeon[x][y] = 'f';
				break;
				
				case 16:
				char_dungeon[x][y] = 'g';
				break;
				
				case 17:
				char_dungeon[x][y] = 'h';
				break;
				
				case 18:
				char_dungeon[x][y] = 'i';
				break;
				
				case 19:
				char_dungeon[x][y] = 'j';
				break;
				
				case 20:
				char_dungeon[x][y] = 'k';
				break;
				
				case 21:
				char_dungeon[x][y] = 'l';
				break;
				
				case 22:
				char_dungeon[x][y] = 'm';
				break;
				
				case 23:
				char_dungeon[x][y] = 'n';
				break;
				
				case 24:
				char_dungeon[x][y] = 'o';
				break;
				
				case 25:
				char_dungeon[x][y] = 'p';
				break;
				
				case 26:
				char_dungeon[x][y] = 'q';
				break;
				
				case 27:
				char_dungeon[x][y] = 'r';
				break;
				
				case 28:
				char_dungeon[x][y] = 's';
				break;
				
				case 29:
				char_dungeon[x][y] = 't';
				break;
				
				case 30:
				char_dungeon[x][y] = 'u';
				break;
				
				case 31:
				char_dungeon[x][y] = 'v';
				break;
				
				case 32:
				char_dungeon[x][y] = 'w';
				break;
				
				case 33:
				char_dungeon[x][y] = 'x';
				break;
				
				case 34:
				char_dungeon[x][y] = 'y';
				break;
				
				case 35:
				char_dungeon[x][y] = 'z';
				break;
				
				case 36:
				char_dungeon[x][y] = 'A';
				break;
				
				case 37:
				char_dungeon[x][y] = 'B';
				break;
				
				case 38:
				char_dungeon[x][y] = 'C';
				break;
				
				case 39:
				char_dungeon[x][y] = 'D';
				break;
				
				case 40:
				char_dungeon[x][y] = 'E';
				break;
				
				case 41:
				char_dungeon[x][y] = 'F';
				break;
				
				case 42:
				char_dungeon[x][y] = 'G';
				break;
				
				case 43:
				char_dungeon[x][y] = 'H';
				break;
				
				case 44:
				char_dungeon[x][y] = 'I';
				break;
				
				case 45:
				char_dungeon[x][y] = 'J';
				break;
				
				case 46:
				char_dungeon[x][y] = 'K';
				break;
				
				case 47:
				char_dungeon[x][y] = 'L';
				break;
				
				case 48:
				char_dungeon[x][y] = 'M';
				break;
				
				case 49:
				char_dungeon[x][y] = 'N';
				break;
				
				case 50:
				char_dungeon[x][y] = 'O';
				break;
				
				case 51:
				char_dungeon[x][y] = 'P';
				break;
				
				case 52:
				char_dungeon[x][y] = 'Q';
				break;
				
				case 53:
				char_dungeon[x][y] = 'R';
				break;
				
				case 54:
				char_dungeon[x][y] = 'S';
				break;
				
				case 55:
				char_dungeon[x][y] = 'T';
				break;
				
				case 56:
				char_dungeon[x][y] = 'U';
				break;
				
				case 57:
				char_dungeon[x][y] = 'V';
				break;
				
				case 58:
				char_dungeon[x][y] = 'W';
				break;
				
				case 59:
				char_dungeon[x][y] = 'X';
				break;
				
				case 60:
				char_dungeon[x][y] = 'Y';
				break;
				
				case 61:
				char_dungeon[x][y] = 'Z';
				break;
				
				default:
				char_dungeon[x][y] = '~';
				break;
			}
			//printf("Char at [%d][%d] = %c\n", x, y, char_dungeon[x][y]);
		}
	}
	
	
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
	int x;
	int y;
	for(y = 0; y < 21; y++)
	{
		for(x = 0; x < 80; x++)
		{
			
			printf("%c", char_map[x][y]);
			
		}
		printf("\n");
	}
}