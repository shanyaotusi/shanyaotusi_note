#include <stdio.h>
#include <stdlib.h>

typedef char* sstr;

sstr new_sstr(int len){
	if(len < 0) return NULL; 
	if(len > 254) len = 254;
	sstr s;
	if(!(s = (sstr)calloc(len+2, sizeof(char)))) return NULL;
	*s = (char)len;
}

sstr free_sstr(sstr s){
	if(s)
		free(s);
	return NULL;
}

sstr init_sstr(char *cs){
	char *temp = cs;
	int len = 0;
	for(;*temp++;len++);
	sstr s = new_sstr(len);
	if(!s) return NULL;
	for(int i = 0;i < (int)s[0];++i){
		s[i+1] = cs[i];
	}
	s[s[0]+1] = '\0';
	return s;
}

/// 模式匹配算法: 寻找从第pos个元素起的匹配的串，返回第一个匹配的位置的第一个开始下标

// 1 普通遍历匹配
int index(sstr s, sstr t, int pos){
	int i = pos;
	int j = 1;
}

// 2 KMP匹配
// 2.1 求next数组
void get_next(sstr t, int *next){}
// 2.1 next数组改进算法求nextval[]
void get_nextval(sstr t, int *next){}

int KMP_index(sstr s, sstr t, int pos){

}