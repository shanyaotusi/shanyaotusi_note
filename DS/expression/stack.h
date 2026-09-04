#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>


#define MAX_LEN 1000
#define ERROR -1
#define OK 1
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
typedef double Elemtype; // 默认元素类型为double

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
void displayOPRD(stack);
void displayOPTR(stack);
#endif