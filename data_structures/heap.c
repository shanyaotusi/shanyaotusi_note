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
	h->size = size;
	h->elem = (Elemtype*)malloc(h->size * sizeof(Elemtype));
	if(!h->elem){
		free(h);
		return NULL;
	}
	h->len = 0;
	return h;
}
// 释放堆
heap free_heap(heap h){
	if(h){
		free(h->elem);
		free(h);
	}
	return NULL;
}
// 调堆
void swap_el(Elemtype *a, Elemtype *b){
	Elemtype i = *a;
	*a = *b;
	*b = i;
}
int heap_drop(heap h, int i, int (*prior)(Elemtype, Elemtype)){
    if(!h || i > h->len || i < 1) return -1;
    
    int left = 2 * i;
    int right = 2 * i + 1;
    int smallest = i;
    
    if(left <= h->len && !prior(h->elem[i], h->elem[left]))
        smallest = left;
    if(right <= h->len && !prior(h->elem[smallest], h->elem[right]))
        smallest = right;
    
    if(smallest != i){
        swap_el(&h->elem[i], &h->elem[smallest]);
        return heap_drop(h, smallest, prior);
    }
    return 1;
}
// push 入堆
int heap_push(heap h, Elemtype e, int (*prior) (Elemtype, Elemtype)){
	if(!h) return -1;
	// 如果空间不够，扩容
	if(h->len == h->size){
		Elemtype *temp = realloc(h->elem, h->size * 2 *sizeof(Elemtype));
		if(!temp) return -1;
		h->elem = temp;
		h->size *= 2;
	}
	h->len++; 
	h->elem[h->len] = e;
	// 向上调整
	int i = h->len;// 指示当前调整节点，也就是e所在的位置
	while(i > 1 && !prior(h->elem[i/2], h->elem[h->len])){
		// 交换双亲节点和当前指示节点
		swap_el(&h->elem[i], &h->elem[i/2]);
		// 指示双亲节点
		i /= 2;
		
	}// 调整完毕
	return i;
}
// 出队（删除根节点）
Elemtype heap_pop(heap h, int (*prior)(Elemtype, Elemtype)){
	if(!h || h->len < 1) return NULL;
	if(h->len == 1){
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