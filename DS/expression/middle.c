// 中缀表达式求值
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// 二目运算函数
Elemtype operate(Elemtype oprd1, char opt,Elemtype oprd2) {
	switch(opt) {
		case '+':
			return oprd1 + oprd2;
			break;
		case '-':
			return oprd1 - oprd2;
			break;
		case '*':
			return oprd1 * oprd2;
			break;
		case '/':
			return oprd1 / oprd2;
			break;
		default:
			break;
	}
	puts("function oprate: invalid aguments!");
	return ERROR;
}
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
	default:
		puts("function transforrm: invalid arguments!");
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
// 算符或算数判断函数
int judge(char c) {
	// 算数返回1
	if(c >= '0' && c<= '9'|| c =='.') return 1;
	// 算符返回0
	else if(transform(c) >= 0)
		return 0;
	puts("function judge: invalid arguments!");
	return ERROR;
}
// 表达式求值函数
Elemtype optExpression(char* expression) {

	stack OPTR = newStack(50);
	pushStack(OPTR, (Elemtype)'#');
	stack OPRD = newStack(50);
	char *p = expression;
	char num[50];
	int i = 0;

	// 只要不是结束符或栈顶不为结束符，继续循环
	while(*p!='#'||getStackTop(OPTR) == '#') {
		//算数
		if(judge(*p)){
			num[i++] = *p;
			num[i] = '\0';
			// 下一个是算符
			if(judge(*(p+1)) == 0){
				// 解析为浮点数，入栈
				pushStack(OPRD, tofloat(num));
			}
		}
		//算符
		else{

		}
		++p;
	}
}

int main() {
	char *expression = "14-3*5+(9-5)#";
	Elemtype re = optExpression(expression);
	printf("%s = %d\n", expression, re);
	return 0;
}