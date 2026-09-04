// 中缀表达式求值
// 2026.09.04
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// 二目运算函数
Elemtype calculate(Elemtype oprd1, char opt,Elemtype oprd2) {
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
	puts("function calculate: invalid aguments!");
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
// 浮点数转换工具函数
Elemtype tofloat(char *s) {
	char *p = s;
	int point = -1;
	Elemtype re = 0;
	while(*p != '\0') {
		if(*p == '.'){
			point = 1;
		}
		else if(point == -1) {
			re *= 10;
			re += (Elemtype)(*p - '0');
		}
		else {
			point *= 10;
			re += (Elemtype)(*p - '0') / point;
		}
		p++;
	}
	return re;
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
	if(*expression == 0) return 0;
	stack OPTR = newStack(50);
	pushStack(OPTR, (Elemtype)'#');
	stack OPRD = newStack(50);
	char *p = expression;
	char num[100] = {0};
	int i = 0;

	// 只要栈不为空，继续循环
	while(getStackLen(OPTR)) {
		printf("\ncurrent exp: %s\n", p);
		//算数
		if(judge(*p)){
			num[i++] = *p;
			num[i] = '\0';
			// 下一个是算符
			if(judge(*(p+1)) == 0){
				// 解析为浮点数，入栈
				pushStack(OPRD, tofloat(num));
				i = 0;
			}
			++p;
		}
		//算符
		else{
			char optr = (char)popStack(OPTR);
			switch(priorCompair(optr, *p)) {
				case '>': //出栈运算
				pushStack(OPRD, calculate(popStack(OPRD), optr, popStack(OPRD)));
				break;

				case '<': //压栈
				pushStack(OPTR, (Elemtype)optr);
				pushStack(OPTR, (Elemtype)(*p));
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
		displayOPRD(OPRD);
		displayOPTR(OPTR);
	}
	int re = popStack(OPRD);
	deleteStack(OPTR);
	deleteStack(OPRD);
	return re;
}

int main() {
	char expression[5][50] = {
		"42+78-14*((4.5+32)/8.7-2.1)+33#",
		"19.3-3.2*2.35+(19*0.5-5)#", 
		"3*(7-12)#",
		"\0",
		"\0"
	};
	Elemtype re[5] = {0};
	for(int i = 0;i < 5;++i){
		re[i] = optExpression(expression[i]);
	}
	for(int i = 0;i < 5;++i)
		printf("\n{{ %s = %.2f }}\n", expression[i], re[i]);
	return 0;
}

// run output:
// current exp: 14-3*5+(9-5)#
// |OPRD| |OPTR| # 

// current exp: 4-3*5+(9-5)#
// |OPRD| 14.00 |OPTR| # 

// current exp: -3*5+(9-5)#
// |OPRD| 14.00 |OPTR| # - 

// current exp: 3*5+(9-5)#
// |OPRD| 14.00 3.00 |OPTR| # - 

// current exp: *5+(9-5)#
// |OPRD| 14.00 3.00 |OPTR| # - * 

// current exp: 5+(9-5)#
// |OPRD| 14.00 3.00 5.00 |OPTR| # - * 

// current exp: +(9-5)#
// |OPRD| 14.00 15.00 |OPTR| # - 

// current exp: +(9-5)#
// |OPRD| -1.00 |OPTR| # 

// current exp: +(9-5)#
// |OPRD| -1.00 |OPTR| # + 

// current exp: (9-5)#
// |OPRD| -1.00 |OPTR| # + ( 

// current exp: 9-5)#
// |OPRD| -1.00 9.00 |OPTR| # + ( 

// current exp: -5)#
// |OPRD| -1.00 9.00 |OPTR| # + ( - 

// current exp: 5)#
// |OPRD| -1.00 9.00 5.00 |OPTR| # + ( - 

// current exp: )#
// |OPRD| -1.00 4.00 |OPTR| # + ( 

// current exp: )#
// |OPRD| -1.00 4.00 |OPTR| # + 

// current exp: #
// |OPRD| 3.00 |OPTR| # 

// current exp: #
// |OPRD| 3.00 |OPTR| 
// 14-3*5+(9-5)# = 3.00