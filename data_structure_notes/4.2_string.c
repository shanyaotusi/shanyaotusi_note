#include <stdio.h>
#include <stdlib.h>

typedef char* sstr;

// 分配空间
sstr new_sstr(int len){
	if(len < 0) return NULL; 
	if(len > 254) len = 254;
	sstr s;
	if(!(s = (sstr)calloc(len+2, sizeof(char)))) return NULL;
	*s = (char)len;
}
// 释放空间
sstr free_sstr(sstr s){
	if(s)
		free(s);
	return NULL;
}
// 初始化
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
 * 2.1 求next[j]数组（0位置为空，不使用）：
 * 我们考虑两种情况：所求的索引1、前两个；2、其他；
 * 	如果是第前两个，next[1]固定为0，next[2]为1
 * 	如果是第三个起，所求的next值的问题 转换为 求j索引之前的串的头尾匹配的位置：
 * 		假设标记的n个单位头尾部分相等，则next[j] = n+1, 比如下图next[j] = 3+1 =4;
 * 		p1 p2 p3 p4 p5 p6 p7 p8 p9 ... p(j-3) p(j-2) p(j-1) pj
 * 		^^ ^^ ^^                       ^^^^^^ ^^^^^^ ^^^^^^
 *  具体步骤为：判断当前j的前一位p( next[j-1] )与p(j-1)是否相等
 * 		若相等，则说明 next[j] + 1 == next[j-1]，执行 next[j] = next[j-1] +1 即可；
 * 		若不等，则比较 next[j-1]的next，即 p( next[ next[j-1] ] ) 与 p(j-1)，
 * 			若相等则同样说明 next[j] + 1 == next[ next[j-1] ],
 * 			若不等，继续寻找 next[ next[j-1] ] 的next，与p(j-1)比较，递归直到找到相等的next，否则如果一直找到头部next[1]，则next[j] = 1.
 * */

 // 分配存储空间与合法性检查由调用的函数完成
void get_next(sstr t, int *next){
	// p指示当前判断的 next 下标,i指示 j-1 下标
	// 初始为 next[1] = 0
	//			  ^^   ^^
	//			  i    p
	int p = 0;
	int i = 1;
	while(i <= (int)t[0]){
		// next回溯到头部或next匹配
		if(p == 0||t[i] == t[p]){
			i++;
			p++;
			next[i] = p;
		}
		
		// 如果当前next不匹配
		else
			p = next[p];
	}
}
// 2.1 next数组改进算法求nextval[]
void get_nextval(sstr t, int *next){
	int p = 0;
	int i = 1;
	while(i <= (int)t[0]){
		if(p == 0||t[i] == t[p]){
			i++;
			p++;
			//next[i] = p;	不再直接赋值，多判断一次该位字符与p是否相等,如果相等则不必赋p
			if(t[i] == t[p]) next[i] = next[p];
			else next[i] = p;
		}
		else
			p = next[p];
	}
}
// 2.2 KMP匹配实现
int KMP_index(sstr s, sstr t, int pos, int *next){
	if(!s || !t || t[0]<=0 || pos<1 || pos > s[0] || s[0] < t[0]) return 0;
	int i = pos, j = 1;
	while(i <= s[0] || j <= t[0]){
		// j<1 根据next[]只有next[1]为0，说明字串第一位不匹配，移动指针
		if(j < 1 || s[i] == t[j])
			{++i;++j;}
		else{
			// 如果出现不匹配不再回退i指针，根据next[]修改j的值
			j = next[j];
		}
	}
	if(j > t[0]) return i-j+1;
	return 0;
}