#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	huffman_tree hft = heap_pop(h, prior);
	free_heap(h);
	return hft;
}

void trav_huffman(huffman_tree h, char* key, char* code, int pos, char* codes[], int *index){
	// 输入需确保code长度足够
	if(!h) return;
	if(h->e == '#'){
		code[pos] = '0';
		trav_huffman(h->lchild, key, code, pos+1, codes, index);
		code[pos] = '1';
		trav_huffman(h->rchild, key, code, pos+1, codes, index);
	}else{
		code[pos] = '\0';
		strcpy(codes[*index], code);
		key[*index] = h->e;
		++(*index);
	}
}
void generate_huffman_code(huffman_tree t, char* key, char* codes[]){
	int *i=(int*)malloc(sizeof(int));
	*i = 0;
	char* c=(char*)calloc(50, sizeof(char));
	trav_huffman(t, key, c, 0, codes, i);
}

int main(int argc, char* argv[]){
	int wt[] = { 0 , 2 , 1 , 1 , 4 , 6 , 8 , 5 , 4 };
	char cs[] = {'0','a','b','c','d','e','f','g','h'};
	char *key = (char*)calloc(26, sizeof(char));
	if(!key) return -1;
	char** codes = (char**)calloc(26, sizeof(char*));
	if(!codes) return -1;
	for(int i=0;i<26;++i){
		codes[i] = (char*)malloc(50*sizeof(char));
		if(!codes[i]) return -1; 
	}
	huffman_tree hft = generate_huffman_tree(wt, cs, 8);
	generate_huffman_code(hft, key, codes);
	for(int i=0;i<8;i++){
		printf("key: %c codes: %s\n", key[i], codes[i]);
	}
	return 0;
}