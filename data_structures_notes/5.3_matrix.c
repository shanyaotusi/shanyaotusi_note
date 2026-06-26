#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 100
typedef int Elemtype;
//对称矩阵的存储
typedef struct {
	Elemtype *data;//数据基址
	int n;//行列数
} *sym_matrix;

sym_matrix new_sym_matrix(int n) {
	if(n < 0||n > MAX_LEN) return NULL;
	int total = n*(n+1)/2;
	sym_matrix m;
	if(!(m = (sym_matrix)malloc(sizeof(*m)))) exit(-1);
	if(!(m->data = (Elemtype*)malloc(total * sizeof(Elemtype)))) exit(-1);
	m->n = n;
	return m;
}

sym_matrix free_sym_matrix(sym_matrix m) {
	if(m) {
		free(m->data);
		free(m);
	} 
	return NULL;
}

// i j 为逻辑下标
Elemtype get_sym_matrix_elem(sym_matrix m, int i, int j) {
	if(!m || i > m->n || j > m->n || i < 1 || j < 1) return -1;
	if(i < j)
		return m->data[j * (j-1)/2 + i-1];
	return m->data[i * (i-1)/2 + j-1]; 
}

//下三角矩阵的存储（上三角类似）
typedef struct {
	Elemtype *data;//数据基址
	int n;//行列数
	int constants;//上三角常数
} *tri_matrix;

//稀疏矩阵的存储
//三元组存储
typedef struct {
	Elemtype e;// 数据元素
	int i,j;// 行和列
} triple;
 
typedef struct {
	triple *data;// 数据基址,0下标置空
	int row, col, len;// 行数和列数、数据个数
	int size;// 三元组容量
} *TSMat;

TSMat new_TSMat(int row, int col, int len) {
	TSMat m;
	if(!(m = (TSMat)malloc(sizeof(*m)))) exit(-1);
	m->col = col;
	m->row = row;
	if(!(m->data = (triple*)malloc(len*sizeof(triple)))) exit(-1);
	m->size = m->len = len;
	return m;
}

TSMat free_TSMat(TSMat m) {
	if(m) {
		free(m->data);
		free(m);
	}
	return NULL;
}
//稀疏矩阵中的主序为行序，列序也按小到大顺序排列
//稀疏矩阵的转置（普通算法）
TSMat transpose_TSMat(TSMat m) {
	if(!m) return NULL;
	TSMat t = new_TSMat(m->col, m->row, m->len);
	for(int i = 1, pos = 1;i <= m->col;++i) {
		for(int j = 1;j <= m->len;++j) {
			//如果原数据的列序等于本次扫描的列序i,加入t
			if(m->data[j].j = i){
				t->data[pos].j = m->data[j].i;
				t->data[pos].i = m->data[j].j;
				t->data[pos].e = m->data[j].e;
			}
			++pos;
		}
	}
	return t;
}

//稀疏矩阵转置优化算法
TSMat fast_transpose_TSMat(TSMat m) {
	if(!m) return NULL;
	TSMat t = new_TSMat(m->col, m->row, m->len);
	


	return t;
}

