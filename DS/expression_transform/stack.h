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

typedef struct stack{
	char *base;
	char *top;
	int size;
} *stack;

stack newStack(int);
stack deleteStack(stack);
int pushStack(stack, char);
char popStack(stack);
int getStackLen(stack);
char getStackTop(stack);
void displayElem(stack);
#endif