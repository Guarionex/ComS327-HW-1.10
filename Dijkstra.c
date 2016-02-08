#include "Dijkstra.h"
#include <stdio.h>

int *distance;
vertex_t *predecessor;

int32_t compare_vertex(const void *key, const void *with)
{
	vertex_t from = *((vertex_t *) key);
	vertex_t to = *((vertex_t *) with);
	if(from.x >= 80 || from.y >= 21)
	{
		switch()
		{
			case ROCK:
			printf("ROCK\n");
			break;
			
			case ROOM:
			printf("ROOM\n");
			break;
			
			case CORRIDOR:
			printf("CORRIDOR\n");
			break;
		}
		printf("From: weight=%d, x=%d, y=%d\n", from.weight, from.x, from.y);
	}
	//printf("From: x=%d y=%d, To: x=%d y=%d\n", from.x, from.y, to.x, to.y);
	//printf("Distance[%d]  and Distance[%d] \n",from.y*80+from.x, to.y*80+to.x);
	int32_t distance_between = distance[from.y*80+from.x] - distance[to.y*80+to.x];
	return distance_between;
}

void Dijkstra(graph_t graph, vertex_t src)
{
	int num_vertices = graph.num_vertices;
	binheap_node_t *nodes[num_vertices];
	distance = malloc(sizeof(int) * num_vertices);
	predecessor = malloc(sizeof(vertex_t) * num_vertices);
	
	binheap_t h;
	binheap_init(&h, compare_vertex, free);	
	
	int v;
	for(v = 0; v < num_vertices; v++)
	{
		int index_y = v/80;
		int index_x = v - (index_y * 80);
		distance[v] = (Compare_Vertices(Get_Vertex(index_x, index_y), src) == TRUE) ? 0 : INT_MAX;
		predecessor[v] = NULL_VERTEX;
		vertex_t *insert_vertex = malloc(sizeof(vertex_t));
		*insert_vertex = graph.vertices[v];
		nodes[v] = binheap_insert(&h, insert_vertex);
		
	}
	
	while(!binheap_is_empty(&h))
	{
		vertex_t *current = (vertex_t *) binheap_remove_min(&h);
		
		edge_t *adjacent_edges = Get_Edges_Of(*current);
		int e;
		for(e = 0; e < 8; e++)
		{
			vertex_t next = adjacent_edges[e].source;
			if(distance[current->y*80+current->x] + next.weight < distance[next.y*80+next.x])
			{
				distance[next.y*80+next.x] = distance[current->y*80+current->x] + next.weight;
				predecessor[next.y*80+next.x] = *current;
				//printf("Num_vertices = %d and next index = %d\n", num_vertices, next.y*80+next.x);
				binheap_decrease_key(&h, nodes[next.y*80+next.x]);
			}
		}
		//free(adjacent_edges);
	}
}

vertex_t *Get_Path(vertex_t target)
{
	vertex_t *path = malloc(sizeof(vertex_t));
	int previous = target.y*80+target.x, path_count = 0;
	
	while(Compare_Vertices(predecessor[previous], NULL_VERTEX) == FALSE)
	{
		path[path_count] = predecessor[previous];
		path_count++;
		path = realloc(path, sizeof(vertex_t) + sizeof(vertex_t) * path_count);
		previous = predecessor[previous].y*80+predecessor[previous].x;
	}
	
	return path;
}

int Get_Cost(vertex_t target)
{
	return distance[target.y*80+target.x];
}