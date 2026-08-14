#include <cstdio>
#include <cstdlib>

void CalMulMax(int A[], int res[], int n) {
	int i = 0;
	int m = 0, nm = 0;// 用于标记最大正整数和最小负整数
	for(int i = 0;i < n;++i) {// 遍历一次确定m和nm
		if(A[i] > m) {
			m = A[i];
		}
		else if(A[i] < nm) {
			nm = A[i];
		}
	}
	for(int i = 0;i < n;++i) {// 计算res数组
		if(A[i] >= 0) {
			res[i] = m * A[i];
		}
		else {
			res[i] = nm * A[i];
		}
	}
}

int main() {
	int a[8] = {1, 0, 4, -3, 9, 2, -2, 6};
	int res[8] = {0};
	CalMulMax(a, res, 8);
	for(int i = 0;i < 8;++i) {
		printf("%d ", res[i]);
	}
}