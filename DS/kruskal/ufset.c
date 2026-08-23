/**
 * 树和森林的应用：
 * 并查集
*/
#include "ufset.h"
// 并查集初始化函数
uf_set uf_init(int n) {
	uf_set set = (uf_set)calloc(1, sizeof(struct union_find_set));
	set->nodelist = (nodelist_p)calloc(n, sizeof(node_p));
	set->len = n;
	for(int i = 0; i < n; i++){
		set->nodelist[i].parent = -1;
	}
	return set;
}
// 并查集销毁函数
uf_set uf_free(uf_set set) {
	if(set){
		if(set->nodelist) free(set->nodelist);
		free(set);
	}
	return NULL;
}
// 并查集查找函数-路径压缩
int uf_find(uf_set set, int pos) {
	if(!set) {puts("wrong args!");return -999;}
	int j = pos;// 保存起点
	while(set->nodelist[pos].parent >= 0) {
		pos = set->nodelist[pos].parent;
	}
	//printf("node[%d].root：%d\n", pos, set->nodelist[pos].parent);
	while(set->nodelist[j].parent != set->nodelist[pos].parent){
		int k = j;
		set->nodelist[k].parent = pos;
		j = set->nodelist[j].parent;
	}
	return pos;
}

// 并查集合并函数-加权合并(节点数)
int uf_union(uf_set set, int i, int j) {
	if(!set) return 0;
	if(i == j) return 1;
	i = uf_find(set, i);
	j = uf_find(set, j);
	// j权值大，合并到j
	if(set->nodelist[i].parent > set->nodelist[j].parent) {
		set->nodelist[j].parent += set->nodelist[i].parent;
		set->nodelist[i].parent = j;
		//printf("union %d to %d, parent: %d\n", i, j, set->nodelist[i].parent);
	}
	// 否则合并到i
	else {
		set->nodelist[i].parent += set->nodelist[j].parent;
		set->nodelist[j].parent = i;
		//printf("union %d to %d, parent %d\n", j, i, set->nodelist[j].parent);
	}
	return 1;
}