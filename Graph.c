#include "Graph.h"

graph_t internal_graph;

 edge_t NULL_EDGE = {,,-1};
vertex_t NULL_VERTEX = {,-1, -1, -1};
graph_t Create_Graph()
{
	internal_graph.num_vertices = 0;
	internal_graph.num_edges = 0;
	internal_graph.vertices = malloc(sizeof(vertex_t));
	internal_graph.edges = malloc(sizeof(edge_t));
	internal_graph.vertices[0] = NULL_VERTEX;
	internal_graph.edges[0] = NULL_EDGE;
	
	return internal_graph;
}

void Destroy_Graph(graph_t *destroy_graph)
{
	free(internal_graph.vertices);
	free(internal_graph.edges);
}

bool Add_Vertex(Dungeon_Space_Struct cell, int x, int y)
{
	vertex_t new_vertex;
	new_vertex.vertexData = cell;
	switch(cell.space_type)
	{
		case ROCK:
			//new_vertex.weight = cell.space_union.rock.density;
			if(cell.space_union.rock.density <= 84) new_vertex.weight = 1;
			else if(cell.space_union.rock.density <= 170) new_vertex.weight = 2;
			else if(cell.space_union.rock.density <= 254) new_vertex.weight = 3;
			else new_vertex.weight = INT_MAX;
		break;
		
		case ROOM:
			new_vertex.weight = 0;
		break;
		
		case CORRIDOR:
			new_vertex.weight = 0;
		break;
	}
	new_vertex.x = x;
	new_vertex.y = y;
	
	internal_graph.num_vertices++;
	internal_graph.vertices = realloc(internal_graph.vertices, sizeof(vertex_t) + (sizeof(vertex_t) * internal_graph.num_vertices));
	internal_graph.vertices[internal_graph.num_vertices-1] = new_vertex;
	internal_graph.vertices[internal_graph.num_vertices] = NULL_VERTEX;
	
	return TRUE;
}

bool Add_Edge(vertex_t *source, vertex_t *target)
{
	edge_t new_edge;
	new_edge.source = source;
	new_edge.target = target;
	new_edge.weight = (Compare_Vertices(*target, NULL_VERTEX) == FALSE) ? *target.weight : INT_MAX;
	
	internal_graph.num_edges++;
	internal_graph.edges = realloc(internal_graph.edges, sizeof(edge_t) + (sizeof(edge_t) * internal_graph.num_edges));
	internal_graph.edges[internal_graph.num_edges-1] = new_edge;
	internal_graph.edges[internal_graph.num_edges] = NULL_EDGE;
	
	return TRUE;
}

vertex_t *Get_Vertex(int x, int y)
{
	int v;
	for(v = 0; v < internal_graph.num_vertices; v++)
	{
		if((internal_graph.vertices[v].x == x) && (internal_graph.vertices[v].y == y))
		{
			return &internal_graph.vertices[v];
		}
	}
	return NULL_VERTEX;
}

bool Compare_Vertices(vertex_t key, vertex_t with)
{
	if((key.x == with.x) && (key.y == with.y))
	{
		return TRUE;
	}
	return FALSE;
}

edge_t *Get_Edges_Of(vertex_t vertex)
{
	edge_t adjacent_edges[8];
	int e, edge_count = 0;
	for(e = 0; e < internal_graph.num_edges; e++)
	{
		edge_t current_edge = internal_graph.edges[e];
		if(Compare_Vertices(current_edge.source, vertex) == TRUE)
		{
			adjacent_edges[edge_count] = current_edge;
			edge_count++;
		}
	}
	
	return adjacent_edges;
}

graph_t GenerateGraph(Dungeon_Space_Struct **dungeon)
{
	graph_t dungeon_graph = Create_Graph();
	
	int y, x;
	for(y = 0; y < 21; y++)
	{
		for(x = 0; x < 80; x++)
		{
			Add_Vertex(dungeon[x][y], x, y);
		}
	}
	
	int v;
	for(v = 0; v < internal_graph.num_vertices; v++)
	{
		int e, a = -1, b = -1;
		for(e = 0; e < 8; e++)
		{
			if((internal_graph.vertices[v].x == 0) || (internal_graph.vertices[v].x == 79) || (internal_graph.vertices[v].y == 0) || (internal_graph.vertices[v].y == 20))
			{
				Add_Edge(&internal_graph.vertices[v], NULL_VERTEX);
			}
			else Add_Edge(&internal_graph.vertices[v], Get_Vertex(internal_graph.vertices[v].x + a, internal_graph.vertices[v].y + b));
			
			a++;
			if(a > 1)
			{
				a = -1;
				b++;
			}
			if(a == 0 && b == 0)
			{
				a = 1;
			}
		}
	}
	
	
}