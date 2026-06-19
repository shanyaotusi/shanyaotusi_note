#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// ----------顺序表定义----------
typedef struct list{
	char *data;
	int size;	//容量/current capacity
	int length;	//已用长度/used length
	int inc;	//扩容大小/size added each time the capacity full
} *sqlist;
sqlist init_sqlist(int size, int inc);
sqlist free_sqlist(sqlist l);
void data_move(char *to, char *from, int len);
int insert_data_sq(sqlist l, int pos, char c);
char delete_data_sq(sqlist l, int pos);
int locate_data_sq(sqlist l, char c);
sqlist merge_sqlist(sqlist l1, sqlist l2);
void print_sqlist(sqlist l, const char *title);
void test_sqlist();

/// ----------单链表定义
typedef struct llist_node{
	char data;
	struct llist_node *next;
} *llist, llist_node;


/// ----------循环链表:尾部节点next指向头节点
typedef llist clist;

clist init_clist();

/// ----------双链表定义
typedef struct dlist_node{
	char data;
	struct dlist_node *prev, *next;
} *dlist;

