/* 线性表
* 2 链式表示实现
* 2.1 linear linked list 
* 2.2 circular linked list
* 2.3 double linked list
* 链表的头节点一般不存储数据，数据元素从头节点的下一个节点开始计算
* 为了方便在链表尾部插入，可以多设置一个尾节点指针
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100
#define Elemtype char
#define ERROR '\0'
/// ----------单链表定义----------
typedef struct llist_node{
	Elemtype data;
	struct llist_node *next;
} *llist, llist_node;

llist init_llist(){
	llist l;
	if(!(l = (llist)calloc(1, sizeof(*l)))) exit(-1);
	return l;
}

// 获取链表长度，不包含头节点，如果不存在返回0
int get_len_llist(llist l){
	if(!l) return 0;
	llist_node *p = l;
	int len = 0;
	while(p->next){
		p = p->next;
		len++;
	}
	return len;
}

// 插入数据,pos为逻辑下标: 失败返回0，成功返回1.
int insert_node_llist(llist l, int pos, Elemtype e){
	if(!l || pos<1) return 0;
	// 初始化插入节点
	llist_node *node = (llist_node*)malloc(sizeof(llist_node));
	if(!node) return 0;
	node->data = e;
	llist_node *p = l;
	for(int i = 0;i < pos-1;++i){
		if(p->next) p = p->next;
		else return 0;
	}
	node->next = p->next;
	p->next = node;
	return 1;
}

// 删除节点
int delete_node_llist(llist l, int pos){
	if(!l || pos <1) return 0;
	llist_node *p = l;
	for(int i = 0;i < pos-1;++i){
		if(p->next) p = p->next;
		else return 0;
	}
	if(p->next){
		llist_node *del = p->next;
		p->next = p->next->next;
		free(del);
	}
	return 1;
}

// 查询节点
Elemtype locate_data_llist(llist l, int pos){
	if(!l || pos<1) return ERROR;
	llist_node *p = l;
	// 移动pos-1次，循环结束p指向第pos个节点
	for(int i = 0;i < pos-1; ++i){
		if(p->next) p = p->next;
		else return ERROR;
	}
	return p->data;
}

typedef llist clist;
// 循环链表初始化
clist init_clist(){
	clist l;
	if(!(l = (clist)calloc(1, sizeof(*l)))) exit(-1);
	l->next = l;
	return l;
}

/// ----------双链表定义---------
typedef struct dlist_node{
	Elemtype data;
	struct dlist_node *prev, *next;
} *dlist, dlist_node;

// 双链表初始化
dlist init_dlist(){
	dlist l;
	if(!(l = (dlist)calloc(1, sizeof(*l)))) exit(-1);
	return l;
}

// 插入,与单链表几乎相同
int insert_node_dlist(dlist l, int pos, dlist node){
	if(!l || !node || pos<1) return 0;
	dlist_node *p = l;
	for(int i = 0;i < pos-1;++i){
		if(p->next) p = p->next;
		else return 0;
	}
	node->next = p->next;
	// 多修改pre域
	if(p->next) p->next->prev = node;
	node->prev = p;
	p->next = node;
	return 1;
}
//其他操作相似。。。

// 链表的新实现（贴近实际）
typedef struct linkNode {
	Elemtype data;
	struct linkNode *next;
} *linkNode;

typedef struct linkList {
	int len;
	linkNode head;
	linkNode tail;
} *linkList;