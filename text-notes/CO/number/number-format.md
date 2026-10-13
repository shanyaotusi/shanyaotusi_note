# 数制与编码

---

## 进制转换

常见二进制、八进制、十六进制之间的转换

## 编码形式

### 原码

由于 0 占用了两个表示形式，n+1 位能表示的整数范围为`- ((2^n) -1)`~`2^n -1`

### 反码

原码按位取反，n+1 位能表示的整数范围为`- ((2^n) -1)`~`2^n -1`

### 补码

负数是对应的反码加一，正数则与原码相同，n+1 位能表示的整数范围为`- (2^n)`~`2^n -1`
，比原码多一个数的表示范围，原因是0只占用了一个表示位

### 移码

以n+1位移码为例，在二进制真值基础上加`2^n`得到移码表示，与补码相比只有符号位相反，**移码只用于定点整数的表示**

- *在比较大小时可以不考虑符号位，而是将其看作无符号整数来比较大小*
### IEEE754浮点数标准

一般形式如下
```
    | S |  阶码  |  尾数  |
      ^          ^
    符号位      小数点
```

常见的浮点数有两种 float和double

- float
    ```
    |s| 8位阶码 | 23位尾数 |
    ```
- double
    ```
    |s| 11位阶码 | 52位尾数 |
    ```

#### 阶码表示
IEEE754标准中阶码使用移码表示，偏置常数不使用`2^n`，而是`2^n-1`

#### 尾数表示
尾数使用原码表示，也比较特殊，尾数是定点小数，但是小数点左侧并非默认的`0.`而是`1.`，因而使得尾数表示位数多一位，提高了表示精度

## C语言类型转换

对于CPU来说并没有数据类型的概念，数据类型是高级语言才有的，因此类型转换也是由编译器完成的

### 有符号和无符号整型

机器字保持不变，仅按有符号或无符号的表示规格进行重新解释

### 短字长与长字长整型数据转换

- 短字长转为长字长
    - 有符号类型的短字长高位补符号位，低位不变
    - 无符号类型高位补零

- 长字长转短字长
    - 高位截断，低位保留

### 浮点数之间的转换

- 单精度转换双精度
    - 没有误差

- 双精度转单精度
    - 大数可能溢出
    - 精度可能损失

### 浮点数和32位整型数据的转换

- 浮点数转整型
    - 取整数部分，小数部分被截断
    - 由于浮点数表示范围更大，转换可能发生溢出

- 整型转浮点型
    - 由于单精度浮点数尾数字长较短，转换过程可能损失精度
    - 转换为双精度没有误差

## 类型转换C语言代码演示
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// print raw binary format
int printUint8Bits(uint8_t ui)
{
	for (int i = 7; i >= 0; --i)
	{
		uint8_t bit = (ui >> i) & 1;
		if (bit == 1)
			printf("%c", '1');
		else if (bit == 0)
			printf("%c", '0');
		else
			return -1;
	}
	return 1;
}
int printUint16Bits(uint16_t ui)
{
	for (int i = 15; i >= 0; --i)
	{
		uint8_t bit = (ui >> i) & 1;
		if (bit == 1)
			printf("%c", '1');
		else if (bit == 0)
			printf("%c", '0');
		else
			return -1;
	}
	return 1;
}
int printUint32Bits(uint32_t ui)
{
	for (int i = 31; i >= 0; --i)
	{
		uint8_t bit = (ui >> i) & 1;
		if (bit == 1)
			printf("%c", '1');
		else if (bit == 0)
			printf("%c", '0');
		else
			return -1;
	}
	return 1;
}
int printFloatBits(float f)
{
	int *p = (int*)&f;
	for (int i = 31; i >= 0; --i)
	{
		// gap sign
		if (i == 30 || i == 22)
			printf(" ");
		uint8_t bit = (*p >> i) & 1;
		if (bit == 1)
			printf("%c", '1');
		else if (bit == 0)
			printf("%c", '0');
		else
			return -1;
	}
	return 1;
}
int printDoubleBits(double d)
{
	long long *ll = (long long*)&d;
	for (int i = 63; i >= 0; --i)
	{
		// gap sign
		if (i == 62 || i == 51)
			printf(" ");
		uint8_t bit = (*ll >> i) & 1;
		if (bit == 1)
			printf("%c", '1');
		else if (bit == 0)
			printf("%c", '0');
		else
			return -1;
	}
	return 1;
}

int main()
{
    // char c = 129;
    // unsigned char uc = 129;
    // short s = 65535;
    // int i = 65535*32768;
    // unsigned int ui = 65535*32768;
    // printUint8Bits(c);
    // printf("\n");
    // printUint32Bits(i);
    // printf("\n");
    // printUint16Bits((short)ui);
    // printf("\n");
    // printUint16Bits((short)i);
    // printf("\n");
    float f = 123456789;
    double d = f;
    printFloatBits(f);
    printf("\n");
    printDoubleBits(d);
    printf("\n");
    exit(0);
}
```