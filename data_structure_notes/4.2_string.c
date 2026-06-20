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
	if(!s || !t || t[0]<=0 || pos<1 || pos > s[0] || s[0] < t[0]) return 0;
	int i = pos, j = 1;
	while(i <= s[0] || j <= t[0]){
		if(s[i] == t[j])
			{++i;++j;}
		else{
			i = i - j +2;
			j = 1;
		}
	}
	if(j > t[0]) return i-j+1;
	return 0;
}

// 2 KMP匹配
/**
 * 2.1 求next数组：
 * 我们考虑两种情况：所求的索引1、不是第一个；2、是第一个；
 * 	如果不是第一个，则正在求的位置前面的next值已经求出，将其next值置为前一个位置的next值
 * 	如果是第一个，置-1以区分其他位置，使用next[]的函数可以通过是不是负值判断是否移动主串的i指针
 * 
 * */

void get_next(sstr t, int *next){

}
// 2.1 next数组改进算法求nextval[]
void get_nextval(sstr t, int *next){}
// 2.2 KMP匹配实现
int KMP_index(sstr s, sstr t, int pos, int *next){
	if(!s || !t || t[0]<=0 || pos<1 || pos > s[0] || s[0] < t[0]) return 0;
	int i = pos, j = 1;
	while(i <= s[0] || j <= t[0]){
		// j<0 说明字串第一位不匹配，移动指针
		if(j < 0 || s[i] == t[j])
			{++i;++j;}
		else{
			// 如果出现不匹配不再回退i指针，j置next[]
			j = next[j];
		}
	}
	if(j > t[0]) return i-j+1;
	return 0;
}