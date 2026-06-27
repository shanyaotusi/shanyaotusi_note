#include <stdio.h>
#include <stdlib.h>

typedef int Elemtype;

//顺序存储：完全二叉树结构
//左孩子等于自身索引乘以二，右孩子乘以二加一
typedef struct sq_bi_tree{
	Elemtype *data;
	int len;
	int size;
}sq_bi_tree;

//链式存储
typedef struct bi_tree{
	Elemtype data;
	struct bi_tree *lchild, *rchild;
} bi_tree;



