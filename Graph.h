#ifndef GRAPH_H
#define GRAPH_H

#include "dungeonObjects.h"
#include <limits.h>
#include <stdlib.h>

typedef struct vertex
{
	Dungeon_Space_Struct vertexData;
	uint weight;
	int x;
	int y;	
} vertex_t;

extern const vertex_t NULL_VERTEX;

typedef struct edge
{
	vertex_t source;
	vertex_t target;
	int weight;
} edge_t;

extern const edge_t NULL_EDGE;

typedef struct graph
{
	int num_vertices;
	int num_edges;
	vertex_t *vertices;
	edge_t *edges;
} graph_t;

extern  graph_t internal_graph;

graph_t Create_Graph();
void Destroy_Graph(graph_t *destroy_graph);
bool Add_Vertex(Dungeon_Space_Struct cell, int x, int y);
bool Add_Edge(vertex_t source, vertex_t target);
vertex_t Get_Vertex(int x, int y);
bool Compare_Vertices(vertex_t key, vertex_t with);
bool Contains_Vertex(vertex_t *vertex_collection, int num_elements, vertex_t find);
edge_t *Get_Edges_Of(vertex_t vertex);
graph_t GenerateGraph(Dungeon_Space_Struct **dungeon, bool tunneler);


#endif