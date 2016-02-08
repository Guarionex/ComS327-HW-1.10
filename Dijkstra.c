#include "Dijkstra.h"

int *distance;
vertex_t *predecessor;

int32_t compare_vertex(const void *key, const void *with)
{
	vertex_t from = (vertex_t) *key;
	vertex_t to = (vertex_t) *with;
	
	int32_t distance_between = distance[from.y*80+from.x] - distance[to.y*80+to.x];
	return distance_between;
}

void Dijkstra(Graph graph, vertex_t src)
{
	int num_vertices = graph.num_vertices;
	binheap_node_t nodes[num_vertices];
	distance = malloc(sizeof(int) * num_vertices);
	predecessor = malloc(sizeof(vertex_t) * num_vertices);
	
	binheap_t h;
	binheap_init(&h, compare_vertex, NULL);	
	
	int v;
	for(v = 0; v < num_vertices; v++)
	{
		int index_y = v/80;
		int index_x = v - (index_y * 80);
		distance[v] = (Compare_Vertices(Get_Vertex(index_x, index_y), src) == TRUE) ? 0 : INT_MAX;
		predecessor[v] = NULL_VERTEX;
		
		nodes[v] = binheap_insert(&h, graph.vertices + v);
	}
	
	while(!binheap_is_empty(&h))
	{
		vertex_t current = (vertex_t) *(binheap_remove_min(&h));
		
		edge_t adjacent_edges[8] = Get_Edges_Of(current);
		int e;
		for(e = 0; e < 8; e++)
		{
			vertex_t next = adjacent_edges[e].source;
			if(distance[current.y*80+current.x] + next.weight < distance[next.y*80+next.x])
			{
				distance[next.y*80+next.x] = distance[current.y*80+current.x] + next.weight;
				predecessor[next.y*80+next.x] = current;
				binheap_decrease_key(&h, nodes[next.y*80+next.x]);
			}
		}
	}
}