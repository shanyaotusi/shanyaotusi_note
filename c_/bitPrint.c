#include <stdio.h>
#include <stdint.h>

int printUintBits(uint8_t uint)
{
	for (int i = 7; i >= 0; --i)
	{
		uint8_t bit = (uint >> i) & 1;
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
	char flag = '1';
	printUintBits(flag);
}