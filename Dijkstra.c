#include "Dijkstra.h"
#include <stdio.h>

uint *distance;
//vertex_t *predecessor;
vertex_t *visited;

int32_t compare_vertex(const void *key, const void *with)
{
	vertex_t from = *((vertex_t *) key);
	vertex_t to = *((vertex_t *) with);
	if(from.x >= 80 || from.y >= 21 || from.x < 0 || from.y < 0)
	{
		printf("From: weight=%d, x=%d, y=%d\n", from.weight, from.x, from.y);
		//return INT_MAX;
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
	distance = malloc(sizeof(uint) * num_vertices);
	//predecessor = malloc(sizeof(vertex_t) * num_vertices);
	visited = malloc(sizeof(vertex_t) * num_vertices);
	vertex_t insert_vertex[num_vertices];
	int visited_count = 0;
	
	binheap_t h;
	binheap_init(&h, compare_vertex, NULL);	
	
	int v;
	for(v = 0; v < num_vertices; v++)
	{
		int index_y = graph.vertices[v].y;
		int index_x = graph.vertices[v].x;
		distance[v] = (Compare_Vertices(Get_Vertex(index_x, index_y), src) == TRUE) ? 0 : 428400;
		//predecessor[v] = NULL_VERTEX;
		//vertex_t *insert_vertex = malloc(sizeof(vertex_t));
		insert_vertex[v] = graph.vertices[v];
		nodes[v] = binheap_insert(&h, insert_vertex + v);
		
	}
	
	while(!binheap_is_empty(&h))
	{
		vertex_t *current = (vertex_t *) binheap_remove_min(&h);
		visited[visited_count] = *current;
		visited_count++;
		
		edge_t *adjacent_edges = Get_Edges_Of(*current);
		int e;
		for(e = 0; e < 8; e++)
		{
			vertex_t next = adjacent_edges[e].target;
			
			if((distance[current->y*80+current->x] + next.weight  < distance[next.y*80+next.x]) && (Contains_Vertex(visited, visited_count, next) == FALSE) && (Compare_Vertices(next, NULL_VERTEX) == FALSE))
			{
				distance[next.y*80+next.x] = distance[current->y*80+current->x] + next.weight;
				//predecessor[next.y*80+next.x] = *current;
				binheap_decrease_key(&h, nodes[next.y*80+next.x]);
			}
		}
		free(adjacent_edges);
	}
	//free(nodes);
	binheap_delete(&h);
}
/*
vertex_t *Get_Path(vertex_t source, vertex_t target)
{
	vertex_t *path = malloc(sizeof(vertex_t));
	path[0] = NULL_VERTEX;
	int previous = target.y*80+target.x, path_count = 0;
	
	while(previous >= 0 && Compare_Vertices(predecessor[previous], source) == FALSE)
	{
		if(predecessor[previous].x < 0 || predecessor[previous].x > 79 || predecessor[previous].y < 0 || predecessor[previous].y > 20)
		{
			previous = predecessor[previous].y*80+predecessor[previous].x;
			//continue;
		}
		else
		{
			path[path_count] = predecessor[previous];
			path_count++;
			path = realloc(path, sizeof(vertex_t) + sizeof(vertex_t) * path_count);
			path[path_count] = NULL_VERTEX;
			previous = predecessor[previous].y*80+predecessor[previous].x;
		}
	}
	
	return path;
}*/

int Get_Cost(vertex_t target)
{
	return distance[target.y*80+target.x];
}

void Destroy_Dijkstra(void)
{
	//free(distance);
	free(predecessor);
	free(visited);
}

void Destroy_Distance(void)
{
	free(distance);
}