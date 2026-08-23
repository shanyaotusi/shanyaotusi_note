#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXLEN 100

typedef struct Arctype {
	int start;
	int end;
	int weight;
} *Arctype;
typedef struct closeEdgeInfo {
	int vertex;// 生成部分的顶点
	Arctype lowcost;// 生成部分顶点与未生成部分的最小边权
} *closeEdgeInfo;
typedef struct triple {
	int vertex;
	Arctype arc;
} *triple;

triple freeTriple(triple, int);
#define Elemtype closeEdgeInfo
#include "heap.h"
// define prior function for heap
int prior(Elemtype a, Elemtype b) {
	if(!a || !a->lowcost) return 0;
	if(!b || !b->lowcost) return 1;
	if(a->lowcost->weight < b->lowcost->weight) return 1;
	else return 0;
}
// define compair function for heap
int compair(Elemtype a, Elemtype b) {
	if(a && b && a->vertex == b->vertex) return 1;
	else return 0;
}
void freeElem(Elemtype elem) {
	if(elem) {
		if(elem->lowcost) {
			free(elem->lowcost);
		}
		free(elem);
	}
}

// init triple array
triple* initTriple(int size) {
	triple *tripleArray = (triple*)malloc(size * sizeof(triple));
	if(!tripleArray) return NULL;
	for(int i = 0;i<size;++i) {
		tripleArray[i] = NULL;
	}
	return tripleArray;
}
// free triple array
triple freeTriple(triple tripleArray, int size) {
	if(!tripleArray) return NULL;
	// free each arc in the triple array
	for(int i = 0;i<size;++i) {
		if(tripleArray) {
			free((tripleArray+i)->arc);
		}
	}
	free(tripleArray);
	return NULL;
}
void addTriple(triple *tripleArray, int vertex, int start, int end, int weight) {
	Arctype arc = (Arctype)malloc(sizeof(struct Arctype));
	if(!arc) return;
	arc->start = start;
	arc->end = end;
	arc->weight = weight;
	tripleArray[vertex] = (triple)malloc(sizeof(struct triple));
	if(!tripleArray[vertex]) return;
	tripleArray[vertex]->vertex = vertex;
	tripleArray[vertex]->arc = arc;
}
void printTriple(triple *tripleArray, int len) {
	for(int i = 0;i<len;++i) {
		if(tripleArray[i]) {
			printf("vertex: %d, arc: {start: %d, end: %d, weight: %d}\n", 
				tripleArray[i]->vertex,
				tripleArray[i]->arc->start, 
				tripleArray[i]->arc->end, 
				tripleArray[i]->arc->weight);
		}
		else {
			printf("vertex: %d, arc: NULL\n", i);
		}
	}
}
// define graph type
typedef struct graph {
	int vertex[MAXLEN][MAXLEN];
	int len;
} *graph;

void print(closeEdgeInfo info) {
	if(info) {
		printf("\t{vertex: %d, lowcost-weight: %d}\n", info->vertex, info->lowcost->weight);
	}
	else {
		printf("\t{info is NULL}\n");
	}
}

int main() {
	// init graph
	graph g = (graph)malloc(sizeof(struct graph));
	if(!g) return 1;
	g->len = 10;
	for(int i = 0;i<g->len;++i) {
	    for(int j = 0;j<=i;++j) {
			if(i==j)
				g->vertex[i][j] = 0;
			else
	       		g->vertex[i][j] = g->vertex[j][i] = rand()%10;
			printf("%d ", g->vertex[i][j]);
	    }
		printf("\n");
	}
	// init triple array
	triple *tripleArray = initTriple(g->len);
	// init heap 
	heap h = newHeap(g->len*(g->len-1));
	// init visited array
	int *visited = (int*)malloc(g->len * sizeof(int));
	if(!visited) return 1;
	for(int i = 0;i<g->len;++i) {
		visited[i] = 0;
	}
	// init other variables
	int count = 0;
	closeEdgeInfo currentVertex_ = (closeEdgeInfo)malloc(sizeof(struct closeEdgeInfo));
	currentVertex_->vertex = 0;
	currentVertex_->lowcost = (Arctype)malloc(sizeof(struct Arctype));
	currentVertex_->lowcost->start = 0;
	currentVertex_->lowcost->end = 0;
	currentVertex_->lowcost->weight = 0;

	if(!currentVertex_) return 1;
	// select shortest edge
	while(count < g->len) {
		printf("(%d) current vertex[%d]\n", count, currentVertex_->vertex);
		visited[currentVertex_->vertex] = 1;
		++count;
		// update heap
		// delete all edges that connect to the current vertexs in the heap
		for(int i = 0;i < g->len;++i) {
			deleteHeapElem(h, currentVertex_, compair, prior);
		}
		// add the minimum edges weight between the current vertex and the unvisited vertexs
		for(int i = 0;i < g->len;++i) {
			// if the vertex is already visited, skip it
			if(visited[i]) continue;
			closeEdgeInfo info = (closeEdgeInfo)malloc(sizeof(struct closeEdgeInfo));
			if(!info) return 1;
			info->vertex = i;
			info->lowcost = NULL;
			// select the minimum edge weight between the current vertex and the unvisited vertex
			for(int j = 0;j < g->len;++j) {
				if(!visited[j] && g->vertex[currentVertex_->vertex][i] > g->vertex[j][i]) {
					info->lowcost = (Arctype)malloc(sizeof(struct Arctype));
					if(!info->lowcost) return 1;
					info->lowcost->start = currentVertex_->vertex;
					info->lowcost->end = i;
					info->lowcost->weight = g->vertex[j][i];
				}
			}
			if(info->lowcost == NULL) {
				info->lowcost = (Arctype)malloc(sizeof(struct Arctype));
				if(!info->lowcost) return 1;
				info->lowcost->start = currentVertex_->vertex;
				info->lowcost->end = i;
				info->lowcost->weight = g->vertex[currentVertex_->vertex][i];
			}
			heapPush(h, info, prior);
		}
		printHeap(h, print);
		printf("visited vertex: ");
		for(int j = 0;j < g->len;++j)
			printf("%d ", visited[j]);
		printf("\n");
		if(getHeapLen(h) == 0) break;
		currentVertex_ = heapPop(h, prior);
		if(!currentVertex_) break;
		addTriple(tripleArray, currentVertex_->vertex, 
			currentVertex_->lowcost->start, 
			currentVertex_->lowcost->end, 
			currentVertex_->lowcost->weight);
	}
	printf("Minimum Spanning Tree is generated:\n");
	printTriple(tripleArray, g->len);
	freeHeap(h, freeElem);
	free(g);
	free(currentVertex_);
	return 0;
}

