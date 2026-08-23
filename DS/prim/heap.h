/**
 * 堆/优先队列
 *  关键操作：调堆，入堆，删除
 *  包含头文件后需自定义优先级函数和元素类型，默认元素类型是int*
 *  优先级函数格式：
 *  int prior(Elemtype a, Elemtype b)
 *  如返回 a > b 为 1 ，a < b 为0 时表示大顶堆
 *  compair函数格式：
 *  int compair(Elemtype a, Elemtype b)
 *  如返回 a == b 为 1 ，a != b 为0 时表示比较两个元素是否相等
 *  freeElem函数格式：
 *  void freeElem(Elemtype e)
 */
#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>

#ifndef Elemtype
#define Elemtype int*
#endif
#define MAX_LEN 1000
#define ERROR -1
#define OK 1
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2

typedef struct heap *heap;
heap newHeap(int);
heap freeHeap(heap, void (*freeElem)(Elemtype));
int heapPush(heap, Elemtype, int (*prior)(Elemtype, Elemtype));
Elemtype heapPop(heap, int (*prior)(Elemtype, Elemtype));
int heapDrop(heap, int, int (*prior)(Elemtype, Elemtype));
int getHeapLen(heap);
int getElemlocation(heap, Elemtype, int (compair)(Elemtype, Elemtype), int (*prior)(Elemtype, Elemtype));
void swapElem(Elemtype*, Elemtype*);
void deleteHeapElem(heap, Elemtype,int (compair)(Elemtype, Elemtype), int (*prior)(Elemtype, Elemtype));
void printHeap(heap, void (*print)(Elemtype));
#endif
