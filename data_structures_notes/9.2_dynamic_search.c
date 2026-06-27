#include <stdio.h>
#include <stdlib.h>

typedef int Elemtype;

typedef struct bi_search_tree{
	Elemtype data;
	struct bi_search_tree *lchild, *rchild;
}bi_search_tree;
