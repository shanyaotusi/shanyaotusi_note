#include <stdio.h>
#include <stdlib.h>

typedef int Elemtype; 
//顺序存储：完全二叉树结构
//左孩子等于自身索引乘以二，右孩子乘以二加一
typedef struct sq_bi_tree{
	Elemtype *elem;
	int len;
	int size;
} *sq_bi_tree;

int get_parent(sq_bi_tree t, int index){
	if(!t || index < 1 ) return -1;
	if(index = 1) return 1;
	else return index/2;
}

int get_lchild(sq_bi_tree t, int index){
	if(!t || index < 1) return -1;
	if(t->len >= index*2) return index*2;
	return -1;
}
int get_rchild(sq_bi_tree t, int index){
	if(!t || index < 1) return -1;
	if(t->len >= index*2+1) return index*2+1;
	return -1;
}

// 链式存储：二叉链表
typedef struct bi_tree{
	Elemtype data;
	struct bi_tree *lchild, *rchild;
} bi_node, *bi_tree;

bi_tree new_bi_tree(){
	bi_tree t = (bi_tree)calloc(1, sizeof(*t));
	if(!t) return NULL;
	return t;
}
