#include <stdio.h>
#include <stdlib.h>

typedef int Elemtype;

//顺序存储：完全二叉树结构
//左孩子等于自身索引乘以二，右孩子乘以二加一
typedef struct sq_bi_tree{
	Elemtype *data;
	int len;
	int size;
} *sq_bi_tree;

int get_parent(sq_bi_tree t, int index){
	if(!t || index < 1 ) return -1;
	if(index = 1) return 1;
	else return index/2;
}

int get_lchild(sq_bi_tree t, int index){
	if(!t || index < 1) return -1;
	if(t->len >= index*2) return index*2;
	return -1;
}
int get_rchild(sq_bi_tree t, int index){
	if(!t || index < 1) return -1;
	if(t->len >= index*2+1) return index*2+1;
	return -1;
}

/**
 * 堆（大顶堆）/ 优先队列
 *  关键操作：调堆，入堆，删除
 */
typedef sq_bi_tree heap;

// 创建堆
heap new_heap(int size){
	if(size < 1) return NULL;
	heap h = (heap)malloc(sizeof(*h));
	if(!h) return NULL;
	h->data = (Elemtype*)malloc(h->size * sizeof(Elemtype));
	if(!h->data){
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
int heap_drop(heap h, int i){
	if(!h || i > h->len) return -1;
	// 如果已经最大则不用调整
	if(h->len < 2*i || h->data[i] >= h->data[2*i] && h->data[i] >= h->data[2*i+1]) return 1;
	// 需要调整
	if(h->len == 2*i || h->data[2*i] > h->data[2*i+1]){
		swap_el(h->data+i, h->data+2*i);
		return heap_drop(h, 2*i);
	}
	else{
		swap_el(h->data+i, h->data+2*i+1);
		return heap_drop(h, 2*i+1);
	}
}
// push 入堆
int heap_push(heap h, Elemtype e){
	if(!h) return -1;
	// 如果空间不够，扩容
	if(h->len == h->size){
		Elemtype *temp = realloc(h->data, h->size * 2);
		if(!temp) return -1;
		h->data = temp;
		h->size *= 2;
	}
	h->data[h->len+1] = e;
	h->len++; 
	// 向上调整
	int i = h->len;// 指示当前调整节点，也就是e所在的位置
	Elemtype temp = e;
	while(i > 1){
		if(h->data[i/2] >= temp) break;// 不用调整
		else{
			// 交换双亲节点和当前指示节点
			temp = h->data[i];
			h->data[i] = h->data[i/2];
			h->data[i/2] = temp;
			// 指示双亲节点
			i /= 2;
		}
	}// 调整完毕
	return i;
}
// 出队（删除根节点）
Elemtype heap_pop(heap h){
	if(!h || h->len < 1) return -1;
	if(h->len = 1){
		h->len = 0;
		return h->data[1];
	}
	Elemtype root = h->data[1];
	// 尾节点代替root
	h->data[1] = h->data[h->len];
	h->len--;
	heap_drop(h, 1);
	return root;
}


//链式存储：二叉链表
typedef struct bi_tree{
	Elemtype data;
	struct bi_tree *lchild, *rchild;
} *bi_tree;



