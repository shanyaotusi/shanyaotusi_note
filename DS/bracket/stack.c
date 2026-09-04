#include "stack.h"

stack newStack(int len) {
	if(len > MAX_LEN) len = MAX_LEN;
	stack s;
	if(!(s = (stack)malloc(sizeof(*s)))) exit(-1);
	if(!(s->base = (Elemtype*)malloc(len*sizeof(Elemtype)))) exit(-1);
	s->top = s->base;
	s->size = len;
	return s;
}

stack deleteStack(stack s) {
	if(!s) return NULL;
	free(s->base);
	free(s);
	return NULL;
}

int pushStack(stack s, Elemtype data) {
	if(!s) return 0;
	// 先判断容量
	if((s->top - s->base) == s->size){
		Elemtype *temp = (Elemtype*)realloc(s->base, 2*s->size*sizeof(Elemtype));
		if(!temp) return 0;
		s->base = temp;
		s->top = s->base + s->size;
		s->size *= 2;
	}
	// 入栈
	*(s->top) = data;
	s->top++;
	return 1;
}

Elemtype popStack(stack s) {
	if(!s || s->base==s->top) return ERROR;
	s->top--;
	return *s->top;
}

int getStackLen(stack s) {
	if(!s) return ERROR;
	return s->top - s->base;
}
Elemtype getStackTop(stack s) {
	if(!s) return ERROR;
	return *(s->top-1);
}

void displayElem(stack s) {
	Elemtype *p = s->base;
	printf("|Stack| ");
	while(p != s->top) {
		printf("%c ", (char)*p);
		++p;
	}
	printf("\n");
}