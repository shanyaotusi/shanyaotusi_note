// 字符括号匹配
// 2026.09.04
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// 检测的括号对
const char pair[10][2] = {
	"()","[]","{}","<>","\0"
};

// 工具函数
bool isLeftBracket(char c) {
	for(int i = 0;i<10;++i) {
		if(pair[i][0] == 0) break;
		if(c == pair[i][0])
			return TRUE;
	}
	return FALSE;
}
bool isRightBracket(char c) {
	for(int i = 0;i<10;++i) {
		if(pair[i][0] == 0) break;
		if(c == pair[i][1])
			return TRUE;
	}
	return FALSE;
}
bool isPair(char c1, char c2) {
	int idx = -1;
	for(int i = 0;i<10;++i) {
		if(pair[i][0] == 0) break;
		if(c1 == pair[i][0])
			idx = i;
	}
	if(c2 == pair[idx][1]) return TRUE;
	else return FALSE;
}

// 匹配函数
bool checkBracket(char *string) {
	if(!string) return FALSE;
	if(*string == 0) return TRUE;
	stack BRKT = newStack(100);
	char *p = string;
	while(*p) {
		if(isLeftBracket(*p)) {
			pushStack(BRKT, *p);
		}
		else{
			if(isRightBracket(*p)){
				if(!getStackLen(BRKT))return FALSE;
				else if(isPair(getStackTop(BRKT), *p)) 
					popStack(BRKT);
				else 
					return FALSE;
			}
		}
		++p;
		displayElem(BRKT);
	}
	// 匹配结束仍有左括号未匹配
	if(getStackLen(BRKT)) return FALSE;
	return TRUE;
}

int main() {
	char *string = {
		"(<>,<>,)..{{}}"
	};
	printf("%s : %d\n", string, checkBracket(string));
	
}