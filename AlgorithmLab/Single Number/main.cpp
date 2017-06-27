// Single Number.cpp : Defines the entry point for the console application.
//


/*	question:

Given an array of integers, every element appears twice except for one. Find that single one.
Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

*/

/* ˼·��

	 5 ^ 5 = 0;
	 0 ^ 7 = 7;
	 a ^ b ^ c = a ^ (b ^ c)
	 ֻҪ�����е�ֵ�����һ�飬ʣ�µ�ֵ���ǵ�ֵ��
*/

#include "stdafx.h"

int main()
{
	int array[] =
	{
		5,5,
		110,110,
		4,
		7,7,
		1289,1289,
	};

	printf("input:  ");
	for (int i = 0; i < sizeof(array)/sizeof(int); ++i)
		printf("%d, ", array[i]);
	printf("\n");
	printf("output:  ");
	int singleNum = 0;
	for (int i = 0; i < sizeof(array) / sizeof(int); ++i)
		singleNum ^= array[i];
	printf("%d\n", singleNum);
    return 0;
}

