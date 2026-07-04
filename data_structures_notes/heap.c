#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

typedef struct heap{
	Elemtype *elem;
	int len;
	int size;
} *heap;
// 辅助函数
int get_heap_len(heap h){
	return h->len;
}
// 创建堆
heap new_heap(int size){
	if(size < 1) return NULL;
	heap h = (heap)malloc(sizeof(*h));
	if(!h) return NULL;
	h->elem = (Elemtype*)malloc(h->size * sizeof(Elemtype));
	if(!h->elem){
		free(h);
		return NULL;
	}
	h->len = 0;
	return h;
}
// 调堆
void swap_el(Elemtype *a, Elemtype *b){
	Elemtype i = *a;
	*a = *b;
	*b = i;
}
// 从下标i开始调整
int heap_drop(heap h, int i, int (*prior) (Elemtype, Elemtype)){
	if(!h || i > h->len) return -1;
	// 如果已经满足则不用调整
	if(h->len < 2*i || prior(h->elem[i], h->elem[2*i]) && prior(h->elem[i], h->elem[2*i+1])) return 1;
	// 需要调整
	if(h->len == 2*i || prior(h->elem[2*i], h->elem[2*i+1])){
		swap_el(h->elem+i, h->elem+2*i);
		return heap_drop(h, 2*i, prior);
	}
	else{
		swap_el(h->elem+i, h->elem+2*i+1);
		return heap_drop(h, 2*i+1, prior);
	}
}
// push 入堆
int heap_push(heap h, Elemtype e, int (*prior) (Elemtype, Elemtype)){
	if(!h) return -1;
	// 如果空间不够，扩容
	if(h->len == h->size){
		Elemtype *temp = realloc(h->elem, h->size * 2);
		if(!temp) return -1;
		h->elem = temp;
		h->size *= 2;
	}
	h->elem[h->len+1] = e;
	h->len++; 
	// 向上调整
	int i = h->len;// 指示当前调整节点，也就是e所在的位置
	Elemtype temp = e;
	while(i > 1){
		if(prior(h->elem[i/2], temp)) break;// 不用调整
		else{
			// 交换双亲节点和当前指示节点
			temp = h->elem[i];
			h->elem[i] = h->elem[i/2];
			h->elem[i/2] = temp;
			// 指示双亲节点
			i /= 2;
		}
	}// 调整完毕
	return i;
}
// 出队（删除根节点）
Elemtype heap_pop(heap h, int (*prior)(Elemtype, Elemtype)){
	if(!h || h->len < 1) return NULL;
	if(h->len = 1){
		h->len = 0;
		return h->elem[1];
	}
	Elemtype root = h->elem[1];
	// 尾节点代替root
	h->elem[1] = h->elem[h->len];
	h->len--;
	// 向下调整
	heap_drop(h, 1, prior);
	return root;
}