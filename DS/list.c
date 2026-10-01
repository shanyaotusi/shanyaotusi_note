#include "list.h"

list newList() 
{
	list l = (list) malloc(sizeof(struct list));
	if (!l) exit(OVERFLOW);
	listNode head = (listNode) malloc(sizeof(struct listNode));
	if (!head) exit(OVERFLOW);
	head->next = NULL;
	l->len = 0;
	l->head = head;
	l->tail = head;
	return l;
}

list deleteList(list l) 
{
	if (l) {
		listNode p = l->head->next;
		while (p) {
			listNode tmp = p;
			p = p->next;
			free(tmp);
		}
		free(l->head);
		free(l);
	}
	return NULL;
}

void pushBack(list l, Elemtype e) 
{
	if (!l) return;
	listNode node = (listNode)malloc(sizeof(struct listNode));
	if (!node) exit(OVERFLOW);
	node->e = e;
	node->next = NULL;
	if (l->len == 0) {
		l->head->next = node;
		l->tail = node;
	} 
	else {
		l->tail->next = node;
		l->tail = node;
	}
	l->len++;
}

void popBack(list l) 
{
	if (!l || l->len == 0) return;
	listNode p = l->head;
	while(p->next != l->tail) {
		p = p->next;
	}
	free(l->tail);
	p->next = NULL;
	l->tail = p;
	l->len--;
}
// 0 return head node
Elemtype getElemAt(list l, int index) 
{
	if (!l || index < 0 || index >= l->len) return ERROR;
	listNode p = l->head;
	for (int i = 0; i <= index; ++i) {
		p = p->next;
	}
	return p->e;
}

void setElemAt(list l, int index, Elemtype e) 
{
	if (!l || index <= 0 || index > l->len) return;
	listNode p = l->head;
	for (int i = 0; i <= index; ++i) {
		p = p->next;
	}
	p->e = e;
}

void deleteElemAt(list l, int index) 
{
	if (!l || index <= 0 || index > l->len) return;
	listNode p = l->head;
	for(int i = 0; i < index; ++i) {
		p = p->next;
	}
	listNode tmp = p->next;
	p->next = tmp->next;
	if(tmp == l->tail) {
		l->tail = p;
	}
	free(tmp);
	l->len--;
}

// merge two sorted lists increased, success return 1, error return -1
int mergeList(list ls1, list ls2) 
{
	if (!ls1 || !ls2) 
		return -1;
	listNode sorted = ls1->head,
		ptr1 = ls1->head->next, 
		ptr2 = ls2->head->next;
	while (ptr1 != NULL && ptr2 != NULL) {
		if (ptr1->e < ptr2->e) {
			sorted->next = ptr1;
			ptr1 = ptr1->next;
		}
		else {
			sorted->next = ptr2;
			ptr2 = ptr2->next;
		}
		sorted = sorted->next;
	}
	// check remanent part
	if (ptr1 != NULL && ptr1 != ls1->tail) {
		sorted->next = ptr1;
	}
	else if (ptr2 != NULL && ptr2 != ls2->tail) {
		sorted->next = ptr2;
		ls1->tail = ls2->tail;
	}
	else {
		if (ls1->tail->e < ls2->tail->e) {
			ls1->tail = ls2->tail;
		}
	}
	ls1->len = ls1->len + ls2->len;
	ls2->tail = ls2->head;
	ls2->head->next = NULL;
	return 1;
}

void printList(list l) 
{
	if (!l) return;
	listNode p = l->head->next;
	while(p) {
		printf("%d -> ", p->e);
		p = p->next;
	}
	printf("NULL\n");
}