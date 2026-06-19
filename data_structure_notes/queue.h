#include <stdio.h>
#include <stdlib.h>

typedef char Elemtype;

// 单端队列
typedef struct queue_node{
	Elemtype data;
	struct queue_node *next;
} *queue, qu_node;

// 顺序队列
typedef struct{
	Elemtype *base;
	int front, end;
	int size;
} *seq_queue;