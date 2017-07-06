// Unique Binary Search Trees : Defines the entry point for the console application.
//


/*	question:

Given n, how many structurally unique BST's (binary search trees) that store values 1...n?

For example,
Given n = 3, there are a total of 5 unique BST's.

1         3     3     2      1
\       /     /      / \      \
3     2     1      1   3       2
/     /       \                 \
2     1         2                 3

*/

/* 思路：
	遍历根值，由于左边都小于根，右边都大于根，所以分为两颗子树
*/

#include "stdafx.h"

//递归的方法
int GetNumber( int n)
{
	if (n == 0) return 1;
	if (n == 1) return 1;
	if (n == 2) return 2;
	int count = 0;
	for (int i = 0; i < n; ++i) {
		count += GetNumber(i) * GetNumber(n - i - 1);
	}
	return count;
}

//非递归方法

int GetNumber2(int n)
{
	int N[100];
	N[0] = 1;
	int curN = 1;
	for (int i = 0; i < n; ++i) {
		N[curN] = 0;
		for (int j = 0; j < curN; ++j) {
			N[curN] += N[j] * N[curN - j - 1];
		}
		curN += 1;
	}
	return N[curN - 1];
}

int main()
{
	printf("3:number : %d \n", GetNumber(10));
	printf("3:number : %d \n", GetNumber2(10));

    return 0;
}

