// 转后缀表达式
// 20260905
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// 辅助转换工具函数
int transform(char optr) {
	switch (optr) {
	case '+':
		return 0;
		break;
	case '-':
		return 1;
		break;
	case '*':
		return 2;
		break;
	case '/':
		return 3;
		break;
	case '(':
		return 4;
		break;
	case ')':
		return 5;
		break;
	case '#':
		return 6;
		break;
	default:
		puts("function transform: invalid arguments!");
		break;
	}
	return ERROR;
}
//optr1 默认为出栈运算符
const char prior[7][7] = {
	// prior[optr1][optr2]
	//+,  -,  *,  /,  (,  ), #;
	 '>','>','<','<','<','>','>',  // +
	 '>','>','<','<','<','>','>',  // -
	 '>','>','>','>','<','>','>',  // *
	 '>','>','>','>','<','>','>',  // /
	 '<','<','<','<','<','=','>',  // (
	 '*','*','*','*','*','*','*',  // ) 
	 '<','<','<','<','<','<','=',  // #
};
// 优先级比较函数
char priorCompair(char optr1, char optr2) {
	int n1 = transform(optr1),n2 = transform(optr2);
	return prior[n1][n2];
}
// 算符或算数判断函数：算数返回1
int judge(char c) {
	// 算数返回1
	if(c >= '0' && c<= '9'|| c =='.') return 1;
	// 算符返回0
	else if(transform(c) >= 0)
		return 0;
	puts("function judge: invalid arguments!");
	return ERROR;
}
// 转后缀表达式函数
void toSuffix(char* expression) {
	if(*expression == 0) return;
	stack OPTR = newStack(50);
	pushStack(OPTR, (char)'#');
	char *p = expression;
	char num[100] = {0};
	int i = 0;

	// 只要栈不为空，继续循环
	while(getStackLen(OPTR)) {
		//算数
		if(judge(*p)){
			//直接输出
			printf("%c", *p);
			//分隔数字
			if(!judge(*(p+1))) {
				printf(" ");
			}
			++p;
		}
		//算符
		else{
			char stackTop = (char)popStack(OPTR);
			switch(priorCompair(stackTop, *p)) {
				case '>': //优先级大，输出算符
				printf("%c ", stackTop);
				break;

				case '<': //优先级小，压栈
				pushStack(OPTR, stackTop);
				pushStack(OPTR, *p);
				++p;
				break;

				case '=': //当前括号内运算结束
				++p;
				break;

				case '*': //不应出现
				puts("error occur! unexpacted oprator"); 
				break;

				default: 
				puts("unkown error occur!"); 
				break;
			}
		}
		//displayOPTR(OPTR);
	}
	deleteStack(OPTR);
}

int main() {
	char expression[5][50] = {
		"42+78-14*((45+32)/7-21)+33#", 
		"\0",//"19.3-3.2*2.35+(19*0.5-5)#",
		"\0",//"3*(7-12)#",
		"\0",
		"\0"
	};
	for(int i = 0;i < 5;++i){
		toSuffix(expression[i]);
	}
	return 0;
}