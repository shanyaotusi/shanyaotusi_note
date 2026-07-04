/**
 * 堆/优先队列
 *  关键操作：调堆，入堆，删除
 */
#ifndef _HEAP_H_
#define _HEAP_H_

#ifndef Elemtype
#define Elemtype int
#endif

typedef struct heap *heap;
heap new_heap(int);
//优先级函数
int (*prior) (Elemtype, Elemtype);
void swap_el(Elemtype*, Elemtype*);
int heap_drop(heap, int);
int heap_push(heap, Elemtype);
Elemtype heap_pop(heap);
#endif