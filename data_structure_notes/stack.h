#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 100

typedef char Elemtype;
#define ERROR '\0'

///-------------栈的定义-----------
// 顺序表示
typedef struct{
	Elemtype *base;
	Elemtype *top;
	int size;
} *stack;

// 辅助list
typedef struct list_node{
	Elemtype data;
	list_node *next;
} *list, list_node;

// 链式表示
typedef struct{
	list base, top;
	int len;
} *linked_stack;