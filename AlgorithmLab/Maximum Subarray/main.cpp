// Maximum Subarray.cpp : Defines the entry point for the console application.
//


/*	question:

Find the contiguous subarray within an array (containing at least one number) which has the largest sum.
For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
the contiguous subarray [4,−1,2,1] has the largest sum = 6.

print the index array

*/

/* 思路：
	动态规划填表法
	0   1   2   3   4  
	-2  -   -   -   -
	-1  1   -   -   -
	-4  -2  -3  -   -
	0   2   1   4   -
	-1  1   0   3   -1

	这种时间和的空间效率均为 O(N^2) 跟穷举差不多 抛弃

	另外，建一个一样的数组，数组每个数存包含该项的点的当前最大的值，如例处理过程：
	-2 1 -2 4 3 5 6 1 5
	则 6 为所求


*/

#include "stdafx.h"
#include <cstdlib>
#include<time.h>

int ary[20];
int sum[20];
bool index[20];

void FillArray()
{
	srand(time(0));
	for (int i = 0; i < 20; ++i) {
		ary[i] = (rand() % 200) - 100;
	}
}

void PrintArray()
{
	for (int i = 0; i < 20; ++i) {
		printf("%d ", ary[i]);
	}
	printf("\n");
}

void PrintIndex(int endIndex)
{
	int firstIndex = 0;
	for (int i = endIndex; i > 0; --i)
	{
		if (index[i]) firstIndex = i - 1;
	}
	printf("frist:%d -> end:%d \n", firstIndex, endIndex);
}

int GetLargestSum(int& endIndex)
{
	for (int i = 0; i < 20; ++i) {
		sum[i] = -200;
		index[i] = false;
	}
	int maxSum = -2000;
	for (int i = 0; i < 20; ++i) {
		if (i > 0) {
			if (sum[i - 1] > 0) {
				sum[i] = sum[i - 1] + ary[i];
				index[i] = true;
			}
			else
				sum[i] = ary[i];
		}
		else {
			sum[i] = ary[i];
		}
		if (maxSum < sum[i]) {
			maxSum = sum[i];
			endIndex = i;
		}
	}
	return maxSum;
}

int main()
{
	FillArray();
	PrintArray();
	int endIndex = 0;
	printf("max sum %d \n", GetLargestSum(endIndex));
	PrintIndex(endIndex);
    return 0;
}

