/**1. 单端队列的链式表示
 * 2. 循环队列的顺序表示
*/
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

sQueue newSQueue(int size){
	sQueue q = (sQueue)malloc(sizeof(struct sQueue));
	if(!q) exit(OVERFLOW);
	q->base = (Elemtype *)malloc(size * sizeof(Elemtype));
	if(!q->base) exit(OVERFLOW);
	q->front = q->end = 0;
	q->size = size;
	return q;
}

sQueue deleteSQueue(sQueue q){
	if(q){
		free(q->base);
		free(q);
	}
	return NULL;
}

void insertSQueue(sQueue q, Elemtype e){
	if((q->end + 1) % q->size == q->front){
		printf("队列已满，无法插入元素\n");
		return;
	}
	q->base[q->end] = e;
	q->end = (q->end + 1) % q->size;
}

void popSQueue(sQueue q, Elemtype *e){
	if(q->front == q->end){
		printf("队列为空，无法删除元素\n");
		return;
	}
	*e = q->base[q->front];
	q->front = (q->front + 1) % q->size;
}