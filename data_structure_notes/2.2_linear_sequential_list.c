/* 线性表
* 1 顺序表示实现
* 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100
/// ----------顺序表定义----------
typedef struct list{
	char *data;
	int size;	//容量/current capacity
	int length;	//已用长度/used length
	int inc;	//扩容大小/size added each time the capacity full
} *sqlist;

// 初始化顺序表，接收初始容量size和扩容大小inc，返回顺序表指针类型
sqlist init_sqlist(int size, int inc){
	if(size <= 0 || size > MAX_LEN || inc <= 0) return NULL;
	// 初始化顺序表指针并分配内存
	sqlist l;
	if(!(l = (sqlist)malloc(sizeof(*l)))) exit(-1);
	if(!(l->data = (char*)malloc(size*sizeof(char)))) exit(-1);
	// 初始化参数
	l->inc = inc;
	l->size = size;
	l->length = 0;
	return l;
}

// 释放顺序表资源
sqlist free_sqlist(sqlist l){
	if(!l) return NULL;
	free(l->data);
	free(l);
	return NULL;
}

// (辅助工具函数)移动连续的数据块
void data_move(char *to, char *from, int len){
	if(len <=0 || to == from) return;
	char* end = from+len-1;
	if(to > from){
		to += len-1;
		while(end >= from) *to-- = *end--;
	}
	else{
		while(from <= end) *to++ = *from++;
	}
}
// 插入函数:pos为逻辑下标，从1开始
int insert_data_sq(sqlist l, int pos, char c){
	if(!l || pos <= 0 || pos > l->length+1) return 0;
	// 如果不够则重新分配内存
	if(l->length >= l->size){
		char *temp;
		int len;
		// 长度检查
		if(l->size + l->inc < MAX_LEN) len = l->size + l->inc;
		else if(l->size < MAX_LEN) len = MAX_LEN;
		else return 0;
		if(!(temp = (char*)realloc(l->data, len * sizeof(char)))) exit(-1);
		l->data = temp;
		l->size = len;
	}
	// 移动数据块，插入新元素
	data_move(l->data+pos, l->data+pos-1, l->length - pos +1);
	*(l->data+pos-1) = c;
	// 更新sqlist
	l->length++;
	return 1;
}
// 删除函数:pos为逻辑下标
char delete_data_sq(sqlist l, int pos){
	if(!l || pos > l->length || pos < 1) return '\0';
	char c = *(l->data+pos-1);
	// 移动数据块
	data_move(l->data+pos-1, l->data+pos, l->length - pos);
	// 更新sqlist
	l->length--;
	return c;
}

// 查找函数
int locate_data_sq(sqlist l, char c){
	if(!l) return 0;
	int index = 0;
	while(index < l->length && *(l->data + index) != c) index++;
	return (index == l->length)? 0 : index+1;
}

// 合并函数：输入的顺序表默认已排序(从小到大)
sqlist merge_sqlist(sqlist l1, sqlist l2){
	if(!l1 || !l2 || l1->length+l2->length > MAX_LEN) return NULL;
	// 初始化返回的顺序表
	sqlist l3 = init_sqlist(l1->length+l2->length, l1->inc);
	if (!l3) return NULL;
	l3->length = l3->size;
	char *p1 = l1->data, *p2 = l2->data;
	int index = 0;//当前操作的l3->data的物理索引
	while(p1 < l1->data+l1->length && p2< l2->data+l2->length){
		if(*p1 <= *p2){
 			*(l3->data+index) = *p1++;
		}
		else{
			*(l3->data+index) = *p2++;
		}
		index++;
	}
	if(p1 < l1->data+l1->length) memcpy(l3->data+index, p1, (l1->data+l1->length-p1)*sizeof(char));
	if(p2 < l2->data+l2->length) memcpy(l3->data+index, p2, (l2->data+l2->length-p2)*sizeof(char));
	return l3;
}


/*********************测试部分(deepseek生成)********************/
// 打印顺序表（字符形式）
void print_sqlist(sqlist l, const char *title) {
    if (!l) {
        printf("%s: 空表（NULL）\n", title);
        return;
    }
    printf("%s (容量=%d, 长度=%d): ", title, l->size, l->length);
    if (l->length == 0) {
        printf("空\n");
        return;
    }
    for (int i = 0; i < l->length; i++)
        printf("%c ", l->data[i]);
    printf("\n");
}

// 测试顺序表全部功能
void test_sqlist() {
    printf("\n========== 顺序表功能测试 ==========\n");

    // 1. 初始化
    sqlist L = init_sqlist(5, 3);   // 初始容量5，每次扩容+3
    if (!L) {
        printf("初始化失败\n");
        return;
    }
    print_sqlist(L, "初始空表");

    // 2. 插入测试（头部、中间、尾部）
    printf("\n--- 插入测试 ---\n");
    insert_data_sq(L, 1, 'A');           // 头部插入 'A'
    insert_data_sq(L, 2, 'C');           // 尾部插入 'C'
    insert_data_sq(L, 2, 'B');           // 中间插入 'B'
    print_sqlist(L, "插入 A, C, B 后");
    printf("在位置 4 插入 'D' (应成功, 当前长度4): %s\n",
           insert_data_sq(L, 4, 'D') ? "成功" : "失败（位置越界）");

    // 3. 扩容测试（插入超过初始容量5）
    printf("\n--- 扩容测试 ---\n");
    insert_data_sq(L, 4, 'D');           // 现在长度4，插入到位置4 → 长度5
    insert_data_sq(L, 5, 'E');           // 长度5 → 6
    insert_data_sq(L, 6, 'F');           // 长度6 → 7
    print_sqlist(L, "连续插入 D, E, F 后");

    // 4. 删除测试（头部、中间、尾部）
    printf("\n--- 删除测试 ---\n");
    char del;
    del = delete_data_sq(L, 1);          // 删除头部
    printf("删除位置1: '%c' → ", del);
    print_sqlist(L, "");
    del = delete_data_sq(L, 3);          // 删除中间（此时表为 B C D E F D）
    printf("删除位置3: '%c' → ", del);
    print_sqlist(L, "");
    del = delete_data_sq(L, L->length);  // 删除尾部
    printf("删除尾部: '%c' → ", del);
    print_sqlist(L, "");
    printf("尝试删除无效位置(0): %c\n", delete_data_sq(L, 0));

    // 5. 查找测试
    printf("\n--- 查找测试 ---\n");
    print_sqlist(L, "当前表");
    printf("查找 'C': 位置 %d\n", locate_data_sq(L, 'C'));
    printf("查找 'Z': 位置 %d\n", locate_data_sq(L, 'Z'));

    // 6. 边界测试：空表删除/查找/插入
    printf("\n--- 边界测试（空表操作） ---\n");
    sqlist empty = init_sqlist(3, 1);
    print_sqlist(empty, "新空表");
    printf("在空表位置1插入 'X': %s\n", insert_data_sq(empty, 1, 'X') ? "成功" : "失败");
    print_sqlist(empty, "插入后");
    printf("删除空表位置1: '%c'\n", delete_data_sq(empty, 1));
    printf("查找空表 'A': 位置 %d\n", locate_data_sq(empty, 'A'));
    free_sqlist(empty);

    // 7. 合并两个有序顺序表
    printf("\n--- 合并有序顺序表 ---\n");
    sqlist l1 = init_sqlist(5, 2);
    sqlist l2 = init_sqlist(5, 2);
    // 构建有序表1: 'a','c','e'
    insert_data_sq(l1, 1, 'a');
    insert_data_sq(l1, 2, 'c');
    insert_data_sq(l1, 3, 'e');
    // 构建有序表2: 'b','d','f','g'
    insert_data_sq(l2, 1, 'b');
    insert_data_sq(l2, 2, 'd');
    insert_data_sq(l2, 3, 'f');
    insert_data_sq(l2, 4, 'g');

    print_sqlist(l1, "有序表1");
    print_sqlist(l2, "有序表2");

    sqlist l3 = merge_sqlist(l1, l2);
    if (l3)
        print_sqlist(l3, "合并结果（有序）");
    else
        printf("合并失败（可能超出MAX_LEN）\n");

    // 8. 合并超限测试（故意构造超过MAX_LEN的长度）
    printf("\n--- 合并超限测试 ---\n");
    sqlist big1 = init_sqlist(MAX_LEN, 10);
    sqlist big2 = init_sqlist(MAX_LEN, 10);
    // 直接将 length 设置为 MAX_LEN 的 80% 和 30%，使总和 > MAX_LEN
    big1->length = MAX_LEN * 0.8;
    big2->length = MAX_LEN * 0.3;
    sqlist failMerge = merge_sqlist(big1, big2);
    printf("合并两个总长度超过MAX_LEN的表: %s\n",
           failMerge == NULL ? "正确返回NULL" : "错误（不应成功）");
    free_sqlist(big1);
    free_sqlist(big2);
    free_sqlist(l1);
    free_sqlist(l2);
    free_sqlist(l3);

    // 9. 释放原表
    printf("\n--- 释放资源 ---\n");
    L = free_sqlist(L);
    printf("原表已释放\n");
}

int main() {
    test_sqlist();
    return 0;
}