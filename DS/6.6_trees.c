#include <stdio.h>
#include <stdlib.h>

typedef int Elemtype;

// 双亲表示法
typedef struct node_p{
	int parent;
	Elemtype e;
} node_p, *nodelist_p;

typedef struct tree_p{
	nodelist_p node;
	int len;
	int root;
} *tree_p;

// 孩子表示法
typedef struct node_c{
	int i;//下标
	struct node_c *next;
} *node_c;

typedef struct tree_c{
	Elemtype e;
	node_c child;
} *tree_c;

// 孩子兄弟表示法
//二叉链表
typedef struct bi_tree{
	Elemtype data;
	struct bi_tree *child, *brother;
} node_cb, *tree_cb;

/**
 * 树和森林的应用：
 * 并查集
*/

typedef struct union_find_set{
	nodelist_p nodelist;
	int len;
} *uf_set;

// 并查集查找函数
int uf_find(uf_set set, int pos){
	if(!set) return -999;
	while(set->nodelist[pos].parent > 0) pos = set->nodelist[pos].parent;
	return pos;
}
// 并查集查找函数优化-路径压缩
int uf_find_pc(uf_set set, int pos){
	if(!set) return -999;
	int j = pos;
	while(set->nodelist[pos].parent > 0) pos = set->nodelist[pos].parent;
	while(set->nodelist[j].parent != pos){
		int k = j;
		set->nodelist[k].parent = pos;
		j = set->nodelist[j].parent;
	}
	return pos;
}
/**
 * 递归写法
 * int uf_find(uf_set set, int pos){
 * 	if(!set) return -999;
 * 	if(set->nodelist[pos].parent < 0) return pos;
 * 	return uf_find(set, set->nodelist[pos].parent);
 * }
 *
 * 递归优化写法
 * int uf_find_pc(uf_set set, int pos){
 * 	if(!set) return -999;
 * 	if(set->nodelist[pos].parent < 0) return pos;
 * 	return pos = uf_find(set, set->nodelist[pos].parent);//路径压缩
 * }
*/

// 并查集合并函数
int uf_union(uf_set set, int i, int j){
	if(!set) return 0;
	i = uf_find(set, i);
	j = uf_find(set, j);
	set->nodelist[i].parent = j;
	return 1;
}
// 并查集合并函数优化-加权合并
int uf_union_wt(uf_set set, int i, int j){
	if(!set) return 0;
	i = uf_find(set, i);
	j = uf_find(set, j);
	if(set->nodelist[i].parent > set->nodelist[j].parent)// j权值大
		set->nodelist[i].parent = j;
	else set->nodelist[j].parent = i;
	return 1;
}