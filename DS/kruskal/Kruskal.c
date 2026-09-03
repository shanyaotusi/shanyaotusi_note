#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXLEN 100
#include "ufset.h"
// 无向图
typedef struct Vertexs {
	int len;
	int vertex[MAXLEN][MAXLEN];
} *Vertexs;
void printVertexs(Vertexs v);
Vertexs initVertexs() {
	puts("init Vertexs...");
	Vertexs v = (Vertexs)calloc(1, sizeof(struct Vertexs));
	v->len = 0;
	puts("done.");
	return v;
}

Vertexs freeVertexs(Vertexs v) {
	puts("free Vertexs...");
	if (v) {
		free(v);
		puts("done.");
	}
	return NULL;
}

void printVertexs(Vertexs v) {
	puts("print Vertexs:\n=====================");
	if (v) {
		for (int i = 0; i < v->len; i++) {
			for (int j = 0; j < v->len; j++) {
				printf("%d ", v->vertex[i][j]);
			}
			printf("\n");
		}
		printf("\n====================\n");
	}
}

Vertexs kruskal(Vertexs v) {
	puts("kruskal...");
	Vertexs mst = initVertexs();
	mst->len = v->len;
	int count = 0;// 记录边的数量
	int edges[MAXLEN][3];
	puts("init edges...");
	// 将所有边存入edges数组
	for (int i = 0; i < v->len; i++) {
		for (int j = i + 1; j < v->len; j++) {
			if (v->vertex[i][j] > 0) {
				edges[count][0] = i;
				edges[count][1] = j;
				edges[count][2] = v->vertex[i][j];
				count++;
			}
		}
	}
	puts("sort edges...");
	// 按权值降序排列
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count - 1 - i; j++) {
			if (edges[j][2] > edges[j + 1][2]) {
				int temp[3];
				temp[0] = edges[j][0];
				temp[1] = edges[j][1];
				temp[2] = edges[j][2];
				edges[j][0] = edges[j + 1][0];
				edges[j][1] = edges[j + 1][1];
				edges[j][2] = edges[j + 1][2];
				edges[j + 1][0] = temp[0];
				edges[j + 1][1] = temp[1];
				edges[j + 1][2] = temp[2];
			}
		}
	}
	puts("done.");
	// 初始化并查集
	uf_set set = uf_init(v->len);
	puts("generating...");
	// 遍历所有边，选择最小的边加入mst
	for(int i = 0; i < count; i++) {
		int u = edges[i][0];
		int v = edges[i][1];
		int w = edges[i][2];
		// 如果u和v不在同一个集合中，则将边(u,v)加入mst，并将u和v合并
		if (uf_find(set, u) != uf_find(set, v)) {
			mst->vertex[u][v] = w;
			mst->vertex[v][u] = w;
			if(!uf_union(set, u, v)) {
				puts("error");
				return NULL;
			}
		}
	}
	puts("done.");
	puts("delete temp source.");
	uf_free(set);
	puts("done.");
	puts("kruskal tree finished.");
	return mst;
}

int main() {
	Vertexs v = initVertexs();
	v->len = 10;
	for(int i = 0; i < v->len; i++) {
		for(int j = 0; j <= i; j++) {
			if(i == j) {
				v->vertex[i][j] = 0;
			} else {
				v->vertex[i][j] = v->vertex[j][i] = rand() % 7 + 3;
			}
		}
	}
	printVertexs(v);
	Vertexs mst = kruskal(v);
	printVertexs(mst);
	v = freeVertexs(v);
	mst = freeVertexs(mst);
	return 0;

}