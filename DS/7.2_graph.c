#include <stdio.h>
#include <stdlib.h>

#define INFINITE 999
#define NodeType int

// 邻接矩阵
typedef struct nei_matrix {
	int n;
	NodeType *vexs;//顶点
	int **arcs;//矩阵
} *nei_matrix;

nei_matrix new_nei_matrix(int num) {
	if(num <= 0) return NULL;
	nei_matrix m;
	if(!(m = (nei_matrix)malloc(sizeof(*m)))) 
		return NULL;
	m->n = num;
	m->vexs = (int*)calloc(num, sizeof(int));
	if(!m->vexs) {
		free(m);
		return NULL;
	}
	m->arcs = (int**)calloc(num*num, sizeof(int));
	if(!m->arcs) {
		free(m->vexs);
		free(m);
		return NULL;
	}
	return m;
}
nei_matrix free_nei_matrix(nei_matrix m) {
	if(m){
		free(m->vexs);
		free(m->arcs);
		free(m);
	}
	return NULL;
}


//弧类型
typedef struct arcnode {
	int weight;
	int adjvex;//指向的顶点索引
	struct arcnode *next;
} arnode, *arcptr;
//邻接表
typedef struct Algraph {
	int n;
	NodeType *vexs;
	arcptr *arcs;
} *Algraph;

Algraph new_Algraph(int num) {
	if(num <= 0) return NULL;
	Algraph g;
	if(!(g = (Algraph)malloc(sizeof(*g))))
		return NULL;
	g->n = num;
	g->vexs = (int*)calloc(num, sizeof(int));
	if(!g->vexs) {
		free(g);
		return NULL;
	}
	g->arcs = (arcptr*)calloc(num, sizeof(arcptr));
	if(!g->vexs) {
		free(g);
		return NULL;
	}
	return g;
}
Algraph free_Algraph(Algraph g) {
	if(g) {
		free(g->arcs);
		free(g->vexs);
		free(g);
	}
	return NULL;
}

//弧节点
typedef struct arcnode_ {
	int weight;
	int from, to;//端点
	struct arcnode_ *prev, *next;//链表指针域
} arcnode_, *arcptr_;
//节点结构体
typedef struct {
	NodeType vex;
	arcptr_ firstin, firstout; 
} vex_node;
//邻接十字表（有向图）
typedef struct Olgraph {
	int n;
	vex_node* vexs;
} *Olgraph;
typedef struct {
	NodeType vex;
	arcptr_ p_arc; 
} vex_node_;
// 邻接多重表（无向图）
typedef struct Olgraph {
	int n;
	vex_node_* vexs;
} *Olgraph;