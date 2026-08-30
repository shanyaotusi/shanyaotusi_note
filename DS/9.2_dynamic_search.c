#include <stdio.h>
#include <stdlib.h>

#define Elemtype int

// 二叉搜索树
typedef struct bi_search_tree {
	Elemtype data;
	struct bi_search_tree *lchild, *rchild;
} bi_node ,*bi_tree;

// AVL树（平衡二叉树）
typedef struct AVL_tree {
	Elemtype data;
	int bl;// 平衡因子
	struct AVL_tree *lchild, *rchild;
} AVL_node, *AVL_tree;

// 平衡二叉搜索
typedef enum AVLTYPE {
	ll,lr,
	rl,rr
} AVL_TYPE;
// 调整函数
void maintainAVL(AVL_node *pnode, AVL_node *anode, AVL_TYPE type) {
	if(!pnode) {
		puts("maintainAVL: wrong args!");
		return;
	}
	int isLeft = -1;
	if(pnode->lchild == anode) 
		isLeft = 1;
	else if(pnode->rchild == anode) 
		isLeft = 0;
	else {
		puts("maintainAVL: wrong args!");
		return;
	} 
	switch (type) {
	case ll:
		AVL_node *bnode = anode->lchild, *cnode = anode->lchild->lchild;
		if(isLeft) pnode->lchild = bnode;
		else pnode->rchild = bnode;
		anode->lchild = bnode->rchild;
		bnode->rchild = anode;
		break;
	case lr:
		AVL_node *bnode = anode->lchild, *cnode = anode->lchild->rchild;
		if(isLeft) pnode->lchild = cnode;
		else pnode->rchild = cnode;
		anode->lchild = cnode->rchild;
		bnode->rchild = cnode->lchild;
		cnode->lchild = bnode;
		cnode->rchild = anode;
		break;
	case rl:
		AVL_node *bnode = anode->lchild, *cnode = anode->lchild->rchild;
		if(isLeft) pnode->lchild = cnode;
		else pnode->rchild = cnode;
		anode->rchild = cnode->lchild;
		bnode->lchild = cnode->rchild;
		cnode->lchild = anode;
		cnode->rchild = bnode;
		break;
	case rr:
		AVL_node *bnode = anode->rchild, *cnode = anode->rchild->rchild;
		if(isLeft) pnode->lchild = bnode;
		else pnode->rchild = bnode;
		anode->rchild = bnode->lchild;
		bnode->lchild = anode;
		break;
	default:
		break;
	}
}


// 红黑树
typedef enum color {
	red,black
} color;
typedef struct rb_tree {
	color color;
	Elemtype data;
	struct rb_tree *parent, *lchild, *rchild;
} rb_node, *rb_tree;

// B树，
typedef struct b_tree{
	Elemtype *data;// 数据块
	struct b_tree *child;// 指针数组，数量比数据块多一
	int len;// 数据个数
	int size;
} b_node, *b_tree;
// B+树
typedef struct bp_tree{
	Elemtype *data;// 数据块
	struct bp_tree *child;// 指针数组，数量比数据块多一
	int len;// 数据个数
	int size;
} bp_node, *bp_tree;