#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
///-------------栈的定义-----------
// 顺序表示
typedef struct stack{
	Elemtype *base;
	Elemtype *top;
	int size;
} *stack;

stack init_stack(unsigned int len){
	if(len > MAX_LEN) return NULL;
	stack s;
	if(!(s = (stack)malloc(sizeof(*s)))) exit(-1);
	if(!(s->base = (Elemtype*)malloc(len*sizeof(Elemtype)))) exit(-1);
	s->top = s->base;
	s->size = len;
	return s;
}

int push_stack(stack s, Elemtype data){
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
	*s->top++ = data;
	return 1;
}

Elemtype pop_stack(stack s){
	if(!s || s->base==s->top) return ERROR;
	s->top--;
	return*s->top;
}

// 辅助list
typedef struct list_node{
	Elemtype data;
	list_node *next;
} *list, list_node;

// 链式表示
typedef struct linked_stack{
	list base, top;
	int len;
} *linked_stack;

// 辅助list的相关操作
list_node* new_list_node(){
	list l;
	if(!(l = (list)calloc(1,sizeof(*l)))) exit(-1);
	return l;
}
// 链栈的相关操作
linked_stack init_linked_stack(){
	linked_stack s;
	if(!(s = (linked_stack)calloc(1, sizeof(*s)))) exit(-1);
	s->top = s->base = new_list_node();
	return s;
}

int push_linked_stack(linked_stack s, Elemtype data){
	if(!s) return 0;
	list_node *temp = new_list_node();
	temp->data = data;
	s->top->next = temp;
	s->top = temp;
	s->len++;
	return 1;
}	

Elemtype pop_linked_stack(linked_stack s){
	if(!s || s->base==s->top) return ERROR;
	Elemtype temp = s->top->data;
	list_node* p = s->base;
	for(int i = 0;i < s->len;++i) p++;
	free(s->top);
	s->top = p;
	s->top->next == NULL;
	s->len--;
	return temp;
}