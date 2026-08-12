#include <stdio.h>
#include <stdlib.h>

#ifndef Keytype
#define Keytype int
#endif
#ifndef Elemtype
#define Elemtype int
#endif

typedef struct {
	Keytype key;
	Elemtype el;
} dataNode, *dataList;

typedef struct searchTable{
	dataList ls;
	int len;
} *searchTable;

int dataCmp(Elemtype a, Elemtype b) {
	return a == b? 1:0;
}

dataList newDataList(int len) {
	dataList ls = (dataList)malloc(len*sizeof(dataNode));
	if(!ls) {puts("newDataList: overflow"); return NULL;}
	int defaultArr[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	puts("initial data list...");
	for(int i = 1;i<=20;++i){
		ls[i].key = defaultArr[i];
		printf("ls[%d]: %d", ls[i].key, ls[i].el);
	}
	return ls;
}

dataList freeDataList(dataList ls) {
	if(ls) free(ls);
	return NULL;
}

searchTable newSearchTable(int len) {
	searchTable tb = (searchTable)malloc(sizeof(*searchTable));
	if(!tb) {puts("newSearchTable: overflow"); return NULL;}
	tb->ls = newDataList(len);
	tb->len = len;
	return tb;
}

searchTable freeSearchTable(searchTable tb) {
	if(tb) {
		freeDataList(tb->ls);
		free(tb);
	}
	return NULL;
}

//=================顺序查找====================
dataNode* sqlSearch(searchTable tb, Keytype id) {
	if(!tb) {puts("sqlSearch: invalid arg!");return NULL;}
	// 设置哨兵
	tb->ls[0].key = id;
	dataNode *ptr = tb->ls + tb->len;
	while(ptr) {
		if(ptr->key == tb->ls->key)
			return ptr;
		--ptr;
	}
	return ls;
} 
//=================折半查找====================
dataNode* hlfSearch(searchTable tb, Keytype id) {
	if(!tb) {puts("hlfSearch: invalid arg!");return NULL;}
	int left = 1, right = len;
	while(left <= right){
		int mid = (left + right)/2;
		if(tb->ls[mid].key == id) 
			return tb->ls+mid;
		if(tb->ls[mid].key > id)
			right = mid;
		else left = mid;
	}
	return NULL;
}
//=================分块查找====================
typedef struct indexList {
	Keytype key;
	int index;
} *indexList;
// 索引表
typedef struct indexTable {
	indexList itb;
	int len;
} *indexTable;
// 复合查找表
typedef struct blockTable {
	indexTable index;
	dataList ls;
	int len;
} *blockTable;
dataNode* blockSearch(blockTable tb, Keytype id) {
	if(!ls) {puts("hlfSearch: arg error!");return NULL;}
	
	return NULL;
}