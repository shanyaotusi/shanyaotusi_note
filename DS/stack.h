#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>


#define MAX_LEN 1000
#define Elemtype int // 默认元素类型为int
#define ERROR -1
#define OK 1
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2

typedef struct stack{
	Elemtype *base;
	Elemtype *top;
	int size;
} *stack;

stack newStack(unsigned int);
stack deleteStack(stack);
int pushStack(stack, Elemtype);
Elemtype popStack(stack);
#endif