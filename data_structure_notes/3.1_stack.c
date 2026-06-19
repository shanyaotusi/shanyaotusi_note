#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

stack init_stack(unsigned int len){
	if(len > MAX_LEN) return NULL;
	stack s;
	if(!(s = (stack)malloc(sizeof(*s)))) exit(-1);
	if(!(s->base = (Elemtype*)malloc(len*sizeof(Elemtype)))) exit(-1);
	s->top = s->base;
	s->size = len;
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

// 辅助list的相关操作
list_node* new_list_node(){
	list l;
	if(!(l = (list)calloc(1,sizeof(*l)))) exit(-1);
	return l;
}
list_node* get_node(list l,int pos){
	if(!l) return NULL;
	list_node* temp = l;
	for(int i=1; i < pos-1;l= l->next){
		if(!l->next) return NULL;
	}
	return temp;
}

// 链栈的相关操作: 以top指针为list尾
linked_stack init_linked_stack(){
	linked_stack s;
	if(!(s = (linked_stack)malloc(sizeof(*s)))) exit(-1);
	s->top = s->base = new_list_node();
	return s;
}

int push_linked_stack(linked_stack s, Elemtype data){
	if(!s) return 0;
	s->top->data = data;
	s->len++;
	list_node* temp = s->top;
	s->top = new_list_node();
	temp->next = s->top;
	return 1;
}	

Elemtype pop_linked_stack(linked_stack s){
	if(!s || s->top==s->base) return ERROR;
	list_node *temp = get_node(s->base, s->len);
	if(!temp) return ERROR;
	s->top = temp;
	return s->top->data;
}