#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 1000
#define Elemtype int
#define ERROR -1
#define OK 1
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2


typedef struct listNode {
	Elemtype e;
	struct listNode *next;
} *listNode;

typedef struct list {
	int len;
	listNode head, tail;
} *list;


list newList();
list deleteList(list);
void pushBack(list, Elemtype);
void popBack(list);
Elemtype getElemAt(list, int);
void setElemAt(list, int, Elemtype);
void deleteElemAt(list, int);
void printList(list);

#endif