#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

typedef char Elemtype;
#define ERROR '\0'

/// ----------顺序表定义----------
typedef struct list{
	char *data;
	int size;	//容量/current capacity
	int length;	//已用长度/used length
	int inc;	//扩容大小/size added each time the capacity full
} *sqlist;
sqlist init_sqlist(int, int);
sqlist free_sqlist(sqlist);
void data_move(Elemtype*, Elemtype*, int);
int insert_data_sq(sqlist, int, Elemtype);
Elemtype delete_data_sq(sqlist, int);
int locate_data_sq(sqlist, Elemtype);
sqlist merge_sqlist(sqlist, sqlist);
void print_sqlist(sqlist, const char*);
void test_sqlist();

/// ----------单链表定义
typedef struct llist_node{
	Elemtype data;
	struct llist_node *next;
} *llist, llist_node;
llist init_llist();
llist init_llist_by_data(Elemtype);
int get_len_llist(llist);
int insert_node_llist(llist, int, llist_node*);
int delete_node_llist(llist, int);
Elemtype locate_data_llist(llist, int);

/// ----------循环链表:尾部节点next指向头节点
typedef llist clist;
clist init_clist();

/// ----------双链表定义
typedef struct dlist_node{
	Elemtype data;
	struct dlist_node *prev, *next;
} *dlist, dlist_node;

