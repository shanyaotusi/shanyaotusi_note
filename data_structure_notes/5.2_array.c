#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>// 该头文件给出了可变长参数表类型va_list,以及获取参数的三个宏va_start,va_arg和va_end

#define MAX_ARRAY_DIM 8

typedef char Elemtype;

typedef struct{
	Elemtype *base;//数组基址
	int dim;//维数
	int *bound;//数组维界基址，即维长数组
	int *constants;//映像函数的常量基址
} *array;

array new_arr(int dim, ...){
	if(dim < 0||dim > MAX_ARRAY_DIM) return NULL;
	array arr;
	if(!(arr = (array)malloc(sizeof(*arr)))) exit(-1);
	arr->dim = dim;
	if(!(arr->bound = (int*)malloc(dim * sizeof(int)))) exit(-1);
	int elemtotal = 1;//元素个数
	va_list ap;
	va_start(ap, dim);//初始化参数表
	for(int i = 0;i < dim;++i){
		arr->bound[i] = va_arg(ap, int);
		if(arr->bound[i] < 0) {
			free(arr->bound);free(arr);
			return NULL;
		}
		elemtotal *= arr->bound[i];
	}
	va_end(ap);//释放资源

}