#include <stdio.h>
#include <stdlib.h>

// haffman最小生成树
typedef struct huffman_tree{
	char e;
	int weight;
	struct huffman_tree *lchild, *rchild;
} *huffman_tree;

// 宏定义实现模板化 heap元素替换为haffman节点
#define Elemtype huffman_tree
#include "heap.h"

// 权重小的优先
int comp(Elemtype a, Elemtype b){
	return a->weight <= b->weight;
}

//优先级函数
int (*prior)(Elemtype, Elemtype) = comp;

// 初始化
huffman_tree new_huffman_tree(char e, int weight){
	huffman_tree t = (huffman_tree)calloc(1, sizeof(*t));
	if(!t) return NULL;
	t->e = e;
	t->weight = weight;
	return t;
}
// 合并节点
huffman_tree merge_huffman_node(huffman_tree tree1, huffman_tree tree2){
	huffman_tree t = (huffman_tree)calloc(1, sizeof(*t));
	if(!t) return NULL;
	t->lchild = tree1;
	t->rchild = tree2;
	t->e = '#';// 特殊字符标记分支节点
	t->weight = tree1->weight + tree2->weight;
	return t;
}
// 根据权重数组生成haffman树
huffman_tree generate_huffman_tree(int weight[], char cs[], int num){
	if(!weight || !cs || num<1) return NULL;
	// 创建优先队列（小顶堆）
	heap h = new_heap(2*num);
	if(!h) return NULL;
	int i = 1;
	// 初始化优先队列
	while(i <= num){
		huffman_tree e = new_huffman_tree(cs[i], weight[i]);
		heap_push(h, e, prior);
		++i;
	}
	while(get_heap_len(h) > 1){
		huffman_tree min1 = heap_pop(h, prior);
		huffman_tree min2 = heap_pop(h, prior);
		huffman_tree merged = merge_huffman_node(min1, min2);
		heap_push(h, merged, prior);
	}
	return heap_pop(h, prior);
}

int main(){
	int wt[] = { 0 , 2 , 1 , 1 , 4 , 6 , 8 , 5 , 4 };
	char cs[] = {'0','a','b','c','d','e','f','g','h'};
	huffman_tree hft = generate_huffman_tree(wt, cs, 8);
	
	return 0;
}