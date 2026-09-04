#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>


#define MAX_LEN 1000
#define ERROR -1
#define OK 1
typedef int bool;
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
typedef char Elemtype; // 默认元素类型为double

typedef struct stack{
	Elemtype *base;
	Elemtype *top;
	int size;
} *stack;

stack newStack(int);
stack deleteStack(stack);
int pushStack(stack, Elemtype);
Elemtype popStack(stack);
int getStackLen(stack);
Elemtype getStackTop(stack);
void displayElem(stack);
#endif