/**1. 单端队列的链式表示
 * 2. 循环队列的顺序表示
*/
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// 单端队列
typedef struct qu_node{
	Elemtype data;
	struct queue_node *next;
} *queue, qu_node;

// 循环队列的顺序表示
typedef struct seq_queue{
	Elemtype *base;
	int front, end;
	int size;
} *cir_queue;