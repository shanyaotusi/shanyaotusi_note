/**
 * 堆/优先队列
 *  关键操作：调堆，入堆，删除
 */
#ifndef _HEAP_H_
#define _HEAP_H_

#ifndef Elemtype
#define Elemtype int*
#endif

typedef struct heap *heap;
int get_heap_len(heap);
heap new_heap(int);
heap free_heap(heap);
void swap_el(Elemtype*, Elemtype*);
int heap_drop(heap, int, int (*prior)(Elemtype, Elemtype));
int heap_push(heap, Elemtype, int (*prior)(Elemtype, Elemtype));
Elemtype heap_pop(heap, int (*prior)(Elemtype, Elemtype));
#endif