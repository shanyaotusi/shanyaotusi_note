#ifndef _LIST_H_
#define _LIST_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

#define Elemtype char
#define ERROR '\0'

typedef struct list *sqlist;
sqlist init_sqlist(int, int);
sqlist free_sqlist(sqlist);
void data_move(Elemtype*, Elemtype*, int);
int insert_data_sq(sqlist, int, Elemtype);
Elemtype delete_data_sq(sqlist, int);
int locate_data_sq(sqlist, Elemtype);
sqlist merge_sqlist(sqlist, sqlist);
void print_sqlist(sqlist, const char*);
void test_sqlist();

typedef struct llist_node *llist, llist_node;
llist init_llist();
llist init_llist_by_data(Elemtype);
int get_len_llist(llist);
int insert_node_llist(llist, int, llist_node*);
int delete_node_llist(llist, int);
Elemtype locate_data_llist(llist, int);

/// ----------循环链表:尾部节点next指向头节点------------
typedef llist clist;
clist init_clist();

typedef struct dlist_node *dlist, dlist_node;

typedef struct linkNode *linkNode;

typedef struct linkList *linkList;

#endif