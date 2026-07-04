#include <stdio.h>
#include <stdlib.h>

#define Elemtype int

// 二叉搜索树
typedef struct bi_search_tree{
	Elemtype data;
	struct bi_search_tree *lchild, *rchild;
} bi_node ,*bi_tree;

// AVL树（平衡二叉树）
typedef struct AVL_tree{
	Elemtype data;
	int bl;// 平衡因子
	struct AVL_tree *lchild, *rchild;
} AVL_node, *AVL_tree;
// 红黑树
typedef enum color{
	red,black
} color;
typedef struct rb_tree{
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