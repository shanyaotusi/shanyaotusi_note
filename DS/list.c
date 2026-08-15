#include "list.h"

list newList() {
	list l = (list)malloc(sizeof(struct list));
	if(!l) exit(OVERFLOW);
	l->len = 0;
	l->head = NULL;
	l->tail = NULL;
	return l;
}

list deleteList(list l) {
	if(l) {
		listNode p = l->head;
		while(p) {
			listNode tmp = p;
			p = p->next;
			free(tmp);
		}
		free(l);
	}
	return NULL;
}

void pushBack(list l, Elemtype e) {
	if(!l) return;
	listNode node = (listNode)malloc(sizeof(struct listNode));
	if(!node) exit(OVERFLOW);
	node->e = e;
	node->next = NULL;
	if(l->len == 0) {
		l->head = node;
		l->tail = node;
	} else {
		l->tail->next = node;
		l->tail = node;
	}
	l->len++;
}

void popBack(list l) {
	if(!l || l->len == 0) return;
	if(l->len == 1) {
		free(l->head);
		l->head = NULL;
		l->tail = NULL;
	} else {
		listNode p = l->head;
		while(p->next != l->tail) {
			p = p->next;
		}
		free(l->tail);
		p->next = NULL;
		l->tail = p;
	}
	l->len--;
}

Elemtype getElemAt(list l, int index) {
	if(!l || index < 0 || index >= l->len) return ERROR;
	listNode p = l->head;
	for(int i = 0; i < index; ++i) {
		p = p->next;
	}
	return p->e;
}

void setElemAt(list l, int index, Elemtype e) {
	if(!l || index < 0 || index >= l->len) return;
	listNode p = l->head;
	for(int i = 0; i < index; ++i) {
		p = p->next;
	}
	p->e = e;
}

void deleteElemAt(list l, int index) {
	if(!l || index < 0 || index >= l->len) return;
	if(index == 0) {
		listNode tmp = l->head;
		l->head = l->head->next;
		free(tmp);
		if(l->len == 1) {
			l->tail = NULL;
		}
	} else {
		listNode p = l->head;
		for(int i = 0; i < index - 1; ++i) {
			p = p->next;
		}
		listNode tmp = p->next;
		p->next = tmp->next;
		if(tmp == l->tail) {
			l->tail = p;
		}
		free(tmp);
	}
	l->len--;
}

void printList(list l) {
	if(!l) return;
	listNode p = l->head;
	while(p) {
		printf("%d -> ", p->e);
		p = p->next;
	}
	printf("NULL\n");
}