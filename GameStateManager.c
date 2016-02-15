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
	
	
	distance_map = malloc(80 * sizeof(char *));
	int x, y;
	for(y = 0; y < 21; y++)
	{
		for(x = 0; x < 80; x++)
		{
			distance_map = malloc(21 * sizeof(char));
			//printf("Before char at [%d][%d] = %c\n", x, y, distance_map[x][y]);
			//printf("Int at [%d][%d] in [%d] = %d\n", x, y, y*80+x, distances_int[y*80+x]);
			//distance_map[x][y] = (char) distances_int[y*80+x];
			switch(distances_int[y*80+x])
			{
				case 0:
				distance_map[x][y] = '0';
				break;
				
				case 1:
				distance_map[x][y] = '1';
				break;
				
				case 2:
				distance_map[x][y] = '2';
				break;
				
				case 3:
				distance_map[x][y] = '3';
				break;
				
				case 4:
				distance_map[x][y] = '4';
				break;
				
				case 5:
				distance_map[x][y] = '5';
				break;
				
				case 6:
				distance_map[x][y] = '6';
				break;
				
				case 7:
				distance_map[x][y] = '7';
				break;
				
				case 8:
				distance_map[x][y] = '8';
				break;
				
				case 9:
				distance_map[x][y] = '9';
				break;
				
				case 10:
				distance_map[x][y] = 'a';
				break;
				
				case 11:
				distance_map[x][y] = 'b';
				break;
				
				case 12:
				distance_map[x][y] = 'c';
				break;
				
				case 13:
				distance_map[x][y] = 'd';
				break;
				
				case 14:
				distance_map[x][y] = 'e';
				break;
				
				case 15:
				distance_map[x][y] = 'f';
				break;
				
				case 16:
				distance_map[x][y] = 'g';
				break;
				
				case 17:
				distance_map[x][y] = 'h';
				break;
				
				case 18:
				distance_map[x][y] = 'i';
				break;
				
				case 19:
				distance_map[x][y] = 'j';
				break;
				
				case 20:
				distance_map[x][y] = 'k';
				break;
				
				case 21:
				distance_map[x][y] = 'l';
				break;
				
				case 22:
				distance_map[x][y] = 'm';
				break;
				
				case 23:
				distance_map[x][y] = 'n';
				break;
				
				case 24:
				distance_map[x][y] = 'o';
				break;
				
				case 25:
				distance_map[x][y] = 'p';
				break;
				
				case 26:
				distance_map[x][y] = 'q';
				break;
				
				case 27:
				distance_map[x][y] = 'r';
				break;
				
				case 28:
				distance_map[x][y] = 's';
				break;
				
				case 29:
				distance_map[x][y] = 't';
				break;
				
				case 30:
				distance_map[x][y] = 'u';
				break;
				
				case 31:
				distance_map[x][y] = 'v';
				break;
				
				case 32:
				distance_map[x][y] = 'w';
				break;
				
				case 33:
				distance_map[x][y] = 'x';
				break;
				
				case 34:
				distance_map[x][y] = 'y';
				break;
				
				case 35:
				distance_map[x][y] = 'z';
				break;
				
				case 36:
				distance_map[x][y] = 'A';
				break;
				
				case 37:
				distance_map[x][y] = 'B';
				break;
				
				case 38:
				distance_map[x][y] = 'C';
				break;
				
				case 39:
				distance_map[x][y] = 'D';
				break;
				
				case 40:
				distance_map[x][y] = 'E';
				break;
				
				case 41:
				distance_map[x][y] = 'F';
				break;
				
				case 42:
				distance_map[x][y] = 'G';
				break;
				
				case 43:
				distance_map[x][y] = 'H';
				break;
				
				case 44:
				distance_map[x][y] = 'I';
				break;
				
				case 45:
				distance_map[x][y] = 'J';
				break;
				
				case 46:
				distance_map[x][y] = 'K';
				break;
				
				case 47:
				distance_map[x][y] = 'L';
				break;
				
				case 48:
				distance_map[x][y] = 'M';
				break;
				
				case 49:
				distance_map[x][y] = 'N';
				break;
				
				case 50:
				distance_map[x][y] = 'O';
				break;
				
				case 51:
				distance_map[x][y] = 'P';
				break;
				
				case 52:
				distance_map[x][y] = 'Q';
				break;
				
				case 53:
				distance_map[x][y] = 'R';
				break;
				
				case 54:
				distance_map[x][y] = 'S';
				break;
				
				case 55:
				distance_map[x][y] = 'T';
				break;
				
				case 56:
				distance_map[x][y] = 'U';
				break;
				
				case 57:
				distance_map[x][y] = 'V';
				break;
				
				case 58:
				distance_map[x][y] = 'W';
				break;
				
				case 59:
				distance_map[x][y] = 'X';
				break;
				
				case 60:
				distance_map[x][y] = 'Y';
				break;
				
				case 61:
				distance_map[x][y] = 'Z';
				break;
				
				default:
				distance_map[x][y] = '~';
				break;
			}
			//printf("Char at [%d][%d] = %c\n", x, y, distance_map[x][y]);
		}
	}
	
	
	return distance_map;
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