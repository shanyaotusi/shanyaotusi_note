#include <stdio.h>
#include <stdlib.h>

typedef char* sstr;

// 分配空间
sstr new_sstr(int len) {
	if(len < 0) return NULL; 
	if(len > 254) len = 254;
	sstr s;
	if(!(s = (sstr)calloc(len+2, sizeof(char)))) return NULL;
	*s = (char)len;
}
// 释放空间
sstr free_sstr(sstr s) {
	if(s)
		free(s);
	return NULL;
}
// 初始化
sstr init_sstr(char *cs) {
	char *temp = cs;
	int len = 0;
	for(;*temp++;len++);
	sstr s = new_sstr(len);
	if(!s) return NULL;
	for(int i = 0;i < (int)s[0];++i) {
		s[i+1] = cs[i];
	}
	s[s[0]+1] = '\0';
	return s;
}

 // 分配存储空间与合法性检查由调用的函数完成
void get_next(sstr t, int *next) {
	// p指示当前判断的 next 下标,i指示 j-1 下标
	// 初始为 next[1] = 0
	//			  ^^   ^^
	//			  i    p
	int p = next[1] = 0;
	int i = 1;
	while(i < (int)t[0]){
		// next回溯到头部或next匹配
		if(p == 0||t[i] == t[p]) {
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
void get_nextval(sstr t, int *next) {
	int p = 0;
	int i = 1;
	while(i <= (int)t[0]) {
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
int KMP_index(sstr s, sstr t, int pos, int *next) {
	if(!s || !t || t[0]<=0 || pos<1 || pos > s[0] || s[0] < t[0]) return 0;
	int i = pos, j = 1;
	while(i <= (int)s[0] && j <= (int)t[0]) {
		// j<1 根据next[]只有next[1]为0，说明字串第一位不匹配，移动指针
		if(j < 1 || s[i] == t[j]){
			++i;
			++j;
		}
		else{
			// 如果出现不匹配不再回退i指针，根据next[]修改j的值
			j = next[j];
		}
	}
	if(j > (int)t[0]) return i-j+1;
	return 0;
}

int main() {
	sstr main = init_sstr("simplesignal");
	sstr s = init_sstr("sign");
	int next[8];
	get_next(s, next);
	for(int i = 1;i < 8;++i) printf("%d ", next[i]);
	puts("\n");
	int pos = KMP_index(main, s, 1, next);
	printf("%s\n", main+pos);
	free_sstr(main);
	free_sstr(s);
	return 0;
}