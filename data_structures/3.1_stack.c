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
	while(p->next != s->top) p = p->next;
	free(s->top);
	s->top = p;
	s->top->next = NULL;
	s->len--;
	return temp;
}

//-----------测试函数：deepseek生成-----------
// 辅助函数：打印顺序栈内容（从栈底到栈顶）
void print_stack(stack s) {
    if (!s) {
        printf("栈指针无效\n");
        return;
    }
    if (s->base == s->top) {
        printf("空栈\n");
        return;
    }
    printf("栈内容（底→顶）：");
    Elemtype *p = s->base;
    while (p < s->top) {
        printf("%c ", *p);
        p++;
    }
    printf("\n");
}

// 辅助函数：打印链栈内容（从栈底到栈顶）
void print_linked_stack(linked_stack s) {
    if (!s) {
        printf("链栈指针无效\n");
        return;
    }
    if (s->base == s->top) {
        printf("空链栈\n");
        return;
    }
    printf("链栈内容（底→顶）：");
    list_node *p = s->base->next;   // 跳过哑元
    while (p != NULL) {
        printf("%c ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 顺序栈测试
void test_seq_stack() {
    printf("\n========== 顺序栈测试 ==========\n");
    stack s = init_stack(5);   // 初始容量5
    if (!s) {
        printf("顺序栈初始化失败\n");
        return;
    }
    printf("初始空栈，容量5\n");

    // 压入元素
    char ch;
    printf("压入 A, B, C, D, E (触发扩容)\n");
    push_stack(s, 'A');
    push_stack(s, 'B');
    push_stack(s, 'C');
    push_stack(s, 'D');
    push_stack(s, 'E');   // 此时容量刚好满
    print_stack(s);

    printf("继续压入 F (触发扩容至10)\n");
    push_stack(s, 'F');
    print_stack(s);

    // 弹出元素
    printf("弹出栈顶：%c\n", pop_stack(s));
    printf("弹出栈顶：%c\n", pop_stack(s));
    print_stack(s);

    printf("再压入 G, H\n");
    push_stack(s, 'G');
    push_stack(s, 'H');
    print_stack(s);

    // 测试空栈弹出
    while (s->base != s->top) {
        printf("弹出：%c\n", pop_stack(s));
    }
    printf("尝试从空栈弹出：");
    Elemtype ret = pop_stack(s);
    if (ret == ERROR) printf("返回 ERROR（%d）\n", ERROR);
    else printf("意外值：%c\n", ret);

    // 释放资源
    free(s->base);
    free(s);
    printf("顺序栈测试结束\n");
}

// 链栈测试
void test_linked_stack() {
    printf("\n========== 链栈测试 ==========\n");
    linked_stack s = init_linked_stack();
    if (!s) {
        printf("链栈初始化失败\n");
        return;
    }
    printf("初始空链栈\n");

    // 压入元素
    push_linked_stack(s, 'A');
    push_linked_stack(s, 'B');
    push_linked_stack(s, 'C');
    print_linked_stack(s);

    push_linked_stack(s, 'D');
    push_linked_stack(s, 'E');
    print_linked_stack(s);

    // 弹出元素
    printf("弹出栈顶：%c\n", pop_linked_stack(s));
    printf("弹出栈顶：%c\n", pop_linked_stack(s));
    print_linked_stack(s);

    push_linked_stack(s, 'F');
    push_linked_stack(s, 'G');
    print_linked_stack(s);

    // 全部弹出
    while (s->base != s->top) {
        printf("弹出：%c\n", pop_linked_stack(s));
    }
    printf("尝试从空链栈弹出：");
    Elemtype ret = pop_linked_stack(s);
    if (ret == ERROR) printf("返回 ERROR（%d）\n", ERROR);
    else printf("意外值：%c\n", ret);

    // 释放资源（需手动释放所有结点，这里简化）
    // 由于 pop 已经释放所有数据结点，只需释放哑元
    free(s->base);
    free(s);
    printf("链栈测试结束\n");
}
