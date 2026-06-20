#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 100

typedef char Elemtype;
#define ERROR '\0'

typedef struct stack stack;
typedef struct list_node *list, list_node;
typedef struct linked_stack *linked_stack;

stack init_stack(unsigned int);
int push_stack(stack, Elemtype);
Elemtype pop_stack(stack);

list_node* new_list_node();
list_node* get_node(list, int);
linked_stack init_linked_stack();
int push_linked_stack(linked_stack, Elemtype);
Elemtype pop_linked_stack(linked_stack);

