// Reverse digits.cpp : Defines the entry point for the console application.
//

/*	question:

Reverse digits of an integer.
Example1: x = 123, return 321
Example2: x = -123, return -321

*/

/* 思路：
	先保留并去掉符号，逐位取值并生成逆转数
*/

#include "stdafx.h"

int ReverseDigits(int orign)
{
	if (orign == 0) return 0;
	bool neg = orign < 0;
	if (neg) orign = -orign;
	int rd = 0;
	while (orign > 0) {
		int bit = orign % 10;
		rd = rd * 10 + bit;
		orign = orign / 10;
	}
	if (neg) rd = -rd;
	return rd;
}

int main()
{   
	printf("12345 reverse to %d\n", ReverseDigits(12345));
	printf("5 reverse to %d\n", ReverseDigits(5));
	printf("-5 reverse to %d\n", ReverseDigits(-5));
	printf("0 reverse to %d\n", ReverseDigits(0));
	printf("145775588 reverse to %d\n", ReverseDigits(145775588));
	printf("-12235 reverse to %d\n", ReverseDigits(-12235));
	return 0;
}

