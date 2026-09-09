#ifndef BTREE_H
#define BTRRE_H

#define MAX_LEN 1000
#define ERROR -1
#define OK 1
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2

#include <stdio.h>
#include <stdlib.h>

typedef int Elemtype;

// B树，
typedef struct bTree{
	Elemtype *data;// 数据块
	struct bTree *child;// 指针数组，数量比数据块多一
	int len;// 数据个数
	int size;
} bNode, *bTree;


// B+树
typedef struct bpTree{
	Elemtype *data;// 数据块
	struct bpTree *child;// 
	int len;// 数据个数
	int size;
} bpNode, *bpTree;

#endif