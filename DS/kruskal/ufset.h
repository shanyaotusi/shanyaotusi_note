#include <stdio.h>
#include <stdlib.h>
#ifndef Elemtype
#define Elemtype int*
#endif
// 双亲表示法
typedef struct node_p{
	int parent;
	Elemtype e;
} node_p, *nodelist_p;

typedef struct union_find_set{
	nodelist_p nodelist;
	int len;
} *uf_set;
uf_set uf_init(int);
uf_set uf_free(uf_set);
int uf_find(uf_set set, int pos);
int uf_union(uf_set set, int i, int j);