#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "dungeonObjects.h"
#include "Graph.h"
#include "binheap.h"
#include <stdint.h>
#include <limits.h>

/*typedef struct distance
{
	vertex_t distance_to;
	int distance_cost;
} distance_t;

typedef struct predecessor
{
	
} predecessor_t;*/

int32_t compare(const void *key, const void *with);
void Dijkstra(Graph *graph, vertex_t src);
vertex_t *Get_Path(vertex_t target);
int Get_Cost(vertex_t target);


#endif