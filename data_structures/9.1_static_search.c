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

int dataCmp(Elemtype a, Elemtype b) {
	return a == b? 1:0;
}

dataList newDataList(int len) {
	dataList ls = (dataList)malloc(len*sizeof(dataNode));
	int defaultArr[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	if(!ls) return -1;
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

//=================顺序查找====================
dataNode* sqlSearch(dataList ls,int len, Keytype id) {
	// len 数据长度，不包含头节点
	if(!ls) {puts("sqlSearch: arg error!");return NULL;}
	// 设置哨兵
	ls[0].key = id;
	dataNode *ptr = ls+len;
	while(ptr) {
		if(ptr->key == ls->key)
			return ptr;
		--ptr;
	}
	return ls;
} 
//=================折半查找====================
dataNode* hlfSearch(dataList ls, int len, Keytype id) {
	if(!ls) {puts("hlfSearch: arg error!");return NULL;}
	int left = 1, right = len;
	while(left <= right){
		int mid = (left + right)/2;
		if(ls[mid].key == id) 
			return ls+mid;
		if(ls[mid].key > id)
			right = mid;
		else left = mid;
	}
	return NULL;
}
//=================分块查找====================
typedef dataList indexTable;// 索引表