#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 1000
#define Elemtype int
#define ERROR -1
#define OK 1
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2

// 单端队列
typedef struct qNode{
	Elemtype data;
	struct qNode *next;
} *qNode;

typedef struct queue{
	qNode front, rear;
	int size;
} *queue;

// 循环队列的顺序表示
typedef struct sQueue{
	Elemtype *base;
	int front, end;
	int size;
} *sQueue;

sQueue newSQueue(int size);
sQueue deleteSQueue(sQueue q);
void insertSQueue(sQueue q, Elemtype e);
void popSQueue(sQueue q, Elemtype *e);

#endif