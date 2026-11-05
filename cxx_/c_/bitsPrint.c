#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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