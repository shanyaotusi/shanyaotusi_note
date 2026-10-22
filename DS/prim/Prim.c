#include <stdio.h>
#include <stdlib.h>

#define VERTEXNUM 10
#define INFINITY 999

typedef struct graph {
    int vertexs[VERTEXNUM][VERTEXNUM];
    int num;
} graph;

// index of arc in graph matrix
typedef struct arc {
    int i, j;
} arc;

typedef struct closeEdge {
    int adjvex;// vertex in the generated span
    int lowcost;// lowest weight arc, 0 means generated span
} closeEdge;

// get minimum edge in closeEdges, return index
// use heap to make this better 
int select_min_edge(closeEdge* cedges)
{
	int lowest = INFINITY, min = -1;
	for (int i = 1;i < VERTEXNUM; ++i) {
		if (cedges[i].lowcost != 0 &&
			cedges[i].lowcost < lowest) {
			lowest = cedges[i].lowcost;
			min = i;
		}
	}
	return min;
}

// update closeEdges
void update_closeEdges(graph* graph, closeEdge* cedges, int idx)
{
	// compair graph[idx][i] with cedges[i], replace it if cedge bigger
	for (int i = 0;i < VERTEXNUM; ++i) {
		if (graph->vertexs[idx][i] != 0 && 
			graph->vertexs[idx][i] < cedges[i].lowcost) {
			cedges[i].lowcost = graph->vertexs[idx][i];
			cedges[i].adjvex = idx;
		}
	}
}

graph* prim_gen_minSpanTree(graph* graph)
{
    // init resource
    struct graph* ptree = (struct graph*)malloc(sizeof(struct graph));
    if (!ptree) return NULL;
	for (int i = 0; i < VERTEXNUM; ++i)
		for (int j = 0; j < VERTEXNUM; ++j)
			graph->vertexs[i][j] = INFINITY;

    ptree->num = VERTEXNUM;
    closeEdge cedges[VERTEXNUM] = {{0,0}};

	// add first edge
	for (int i = 0; i < VERTEXNUM; ++i) {
		cedges[i].adjvex = 0;
		cedges[i].lowcost = graph->vertexs[0][i];
	}

	for (int i = 1; i < VERTEXNUM; ++i) {
		// select min edge
		int min = select_min_edge(cedges);
		if (min == -1) break;
		ptree->vertexs[cedges[min].adjvex][min] 
			= graph->vertexs[cedges[min].adjvex][min];
		// maintain cedges
		cedges[min].lowcost = 0;
		update_closeEdges(graph, cedges, min);
	}
	
	return ptree;
}

int main()
{
	return 0;
}
