#include "GameStateManager.h"

Dungeon_Space_Struct **current_dungeon;
player_t pc;
char *distance_map;
graph_t graphed_dungeon;

void Set_Dungeon(Dungeon_Space_Struct **dungeon)
{
	current_dungeon = dungeon;
}

void Set_Player(player_t player)
{
	pc = player;
}

char *Generate_Distance_Dungeon(bool tunneler)
{
	graphed_dungeon = GenerateGraph(current_dungeon, tunneler);
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
	
	
	distance_map = malloc(1680 * sizeof(char));
	int z;
	for(z = 0; z < 1680; z++)
	{
		//distance_map = malloc(21 * sizeof(char));
		//printf("Before char at [%d][%d] = %c\n", x, y, distance_map[x][y]);
		//printf("Int at [%d][%d] in [%d] = %d\n", x, y, y*80+x, distances_int[y*80+x]);
		//distance_map[x][y] = (char) distances_int[y*80+x];
		//printf("distances_int[0] = %d\n", distances_int[0]);
		switch(distances_int[z])
		{
			case 0:
			distance_map[z] = '0';
			break;
			
			case 1:
			distance_map[z] = '1';
			break;
			
			case 2:
			distance_map[z] = '2';
			break;
			
			case 3:
			distance_map[z] = '3';
			break;
			
			case 4:
			distance_map[z] = '4';
			break;
			
			case 5:
			distance_map[z] = '5';
			break;
			
			case 6:
			distance_map[z] = '6';
			break;
			
			case 7:
			distance_map[z] = '7';
			break;
			
			case 8:
			distance_map[z] = '8';
			break;
			
			case 9:
			distance_map[z] = '9';
			break;
			
			case 10:
			distance_map[z] = 'a';
			break;
			
			case 11:
			distance_map[z] = 'b';
			break;
			
			case 12:
			distance_map[z] = 'c';
			break;
			
			case 13:
			distance_map[z] = 'd';
			break;
			
			case 14:
			distance_map[z] = 'e';
			break;
			
			case 15:
			distance_map[z] = 'f';
			break;
			
			case 16:
			distance_map[z] = 'g';
			break;
			
			case 17:
			distance_map[z] = 'h';
			break;
			
			case 18:
			distance_map[z] = 'i';
			break;
			
			case 19:
			distance_map[z] = 'j';
			break;
			
			case 20:
			distance_map[z] = 'k';
			break;
			
			case 21:
			distance_map[z] = 'l';
			break;
			
			case 22:
			distance_map[z] = 'm';
			break;
			
			case 23:
			distance_map[z] = 'n';
			break;
			
			case 24:
			distance_map[z] = 'o';
			break;
			
			case 25:
			distance_map[z] = 'p';
			break;
			
			case 26:
			distance_map[z] = 'q';
			break;
			
			case 27:
			distance_map[z] = 'r';
			break;
			
			case 28:
			distance_map[z] = 's';
			break;
			
			case 29:
			distance_map[z] = 't';
			break;
			
			case 30:
			distance_map[z] = 'u';
			break;
			
			case 31:
			distance_map[z] = 'v';
			break;
			
			case 32:
			distance_map[z] = 'w';
			break;
			
			case 33:
			distance_map[z] = 'x';
			break;
			
			case 34:
			distance_map[z] = 'y';
			break;
			
			case 35:
			distance_map[z] = 'z';
			break;
			
			case 36:
			distance_map[z] = 'A';
			break;
			
			case 37:
			distance_map[z] = 'B';
			break;
			
			case 38:
			distance_map[z] = 'C';
			break;
			
			case 39:
			distance_map[z] = 'D';
			break;
			
			case 40:
			distance_map[z] = 'E';
			break;
			
			case 41:
			distance_map[z] = 'F';
			break;
			
			case 42:
			distance_map[z] = 'G';
			break;
			
			case 43:
			distance_map[z] = 'H';
			break;
			
			case 44:
			distance_map[z] = 'I';
			break;
			
			case 45:
			distance_map[z] = 'J';
			break;
			
			case 46:
			distance_map[z] = 'K';
			break;
			
			case 47:
			distance_map[z] = 'L';
			break;
			
			case 48:
			distance_map[z] = 'M';
			break;
			
			case 49:
			distance_map[z] = 'N';
			break;
			
			case 50:
			distance_map[z] = 'O';
			break;
			
			case 51:
			distance_map[z] = 'P';
			break;
			
			case 52:
			distance_map[z] = 'Q';
			break;
			
			case 53:
			distance_map[z] = 'R';
			break;
			
			case 54:
			distance_map[z] = 'S';
			break;
			
			case 55:
			distance_map[z] = 'T';
			break;
			
			case 56:
			distance_map[z] = 'U';
			break;
			
			case 57:
			distance_map[z] = 'V';
			break;
			
			case 58:
			distance_map[z] = 'W';
			break;
			
			case 59:
			distance_map[z] = 'X';
			break;
			
			case 60:
			distance_map[z] = 'Y';
			break;
			
			case 61:
			distance_map[z] = 'Z';
			break;
			
			default:
			distance_map[z] = ' ';
			break;
		}
		//printf("Char at [%d][%d] = %c\n", x, y, distance_map[x][y]);
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
							printf("~");
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

void Draw_Distance_Dungeon(char *char_map)
{
	int x;
	int y;
	for(y = 0; y < 21; y++)
	{
		for(x = 0; x < 80; x++)
		{
			if(x == 0 || x == 79 || y == 0 || y == 20)
			{
				printf("~");
			}
			else
			{
				if(char_map[y*80+x] == ' ')
				{
					switch(current_dungeon[x][y].space_type)
				{
					case ROCK :
						printf(" ");
					break;
					
					case ROOM :
						printf(".");
					break;
					
					case CORRIDOR :
						printf("#");
					break;
				}
				}
				else 
				{
					printf("%c", char_map[y*80+x]);
				}
			}
			
		}
		printf("\n");
	}
}

void Destroy_All(void)
{
	void Destroy_Graph(graphed_dungeon);
}