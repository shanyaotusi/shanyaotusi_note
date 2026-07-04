#include <stdio.h>
#include <stdlib.h>

// haffman最小生成树
typedef struct huffman_tree{
	char e;
	int weight;
	struct haffman_tree *lchild, *rchild;
} *haffman_tree;

// 宏定义实现模板化 heap元素替换为haffman节点
#define Elemtype haffman_tree
#include "heap.h"

// 权重小的优先
int comp(Elemtype a, Elemtype b){
	return a->weight <= b->weight;
}
// 优先级函数指针赋值
prior = comp;

// 初始化
haffman_tree new_haffman_tree(char e, int weight){
	haffman_tree t = (haffman_tree)calloc(1, sizeof(*t));
	if(!t) return NULL;
	t->e = e;
	t->weight = weight;
	return t;
}
// 合并节点
haffman_tree merge_haffman_node(haffman_tree node1, haffman_tree node2){
	haffman_tree t = (haffman_tree)calloc(1, sizeof(*t));
	if(!t) return NULL;
	t->lchild = node1;
	t->rchild = node2;
	t->e = '#';// 特殊字符标记分支节点
	t->weight = node1->weight + node2->weight;
	return t;
}
// 根据权重数组生成haffman树
haffman_tree generate_haffman_tree(int weight[], char cs[], int num){
	if(!weight || !cs || num<1) return NULL;
	// 创建优先队列（小顶堆）
	heap h = new_heap((num*num+1)/2);
	if(!h) return NULL;
	int i = 1;
	// 初始化优先队列
	while(i <= num){
		Elemtype e = {cs[i], weight[i], NULL, NULL};
		heap_push(h, e);
	}
	while(h->len > 1){
		haffman_tree min1 = heap_pop(h);
		haffman_tree min2 = heap_pop(h);
		haffman_tree merged = merge_haffman_node(min1, min2);
		heap_push(h, merged);
	}
	return heap_pop(h);
}

