// Best Time to Buy and Sell Stock.cpp : Defines the entry point for the console application.
//


/*	question:

Say you have an array for which the ith element is the price of a given stock on day i.
If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.
	
	extend 2:
		show which day to buy and which day to sell.

	extend 3:
	 if you can buy and sell any times as you want, how many profits can you make?

	extend 4：
		with the condition same as extend 1， but every transaction cost a litter charge， make yourself most profit.

	extend 5:
		printf the extend 2 's days.



*/

/* 思路
	1. 保存当前最大利益值和 最低价格
	2. 保存最低价格的天序，和当前最大利益值时的交易天序
	3. 只要第二天比第一天多钱，都能买
	4. 只在波底买，在波峰卖，交易次数最少
*/

#include "stdafx.h"
#include <cstdlib>
#include <time.h>
#include <vector>

int* stockArray = nullptr;
int stockSize = 0;

void initArray()
{
	stockSize = 100;
	stockArray = new int[stockSize];
	for (int i = 0; i < stockSize; ++i) 
	{
		stockArray[i] = rand() % 1000;
	}
}

void printArray()
{
	int index = 0;
	for (int i = 0; i < stockSize; ++ i) {
		if (index % 10 == 0 && index != 0)
			printf("\n");
		printf("%d  ", stockArray[i]);
	}
	printf("\n");
}

void freeArray()
{
	if (stockArray)
		delete[] stockArray;
	stockArray = nullptr;
	stockSize = 0;
}

int main()
{
	srand(time(0));
	initArray();
//	printArray();
	{// 1. 2.
		int minVal = 1E3; int maxPro = 0;
		int dayBuy = 0; int daySell = 0;
		int minDay = 0;
		for (int i = 0; i < stockSize; ++i)
		{
			if (stockArray[i] - minVal > maxPro) {
				maxPro = stockArray[i] - minVal;
				dayBuy = minDay;
				daySell = i;
			}
			if (stockArray[i] < minVal) {
				minVal = stockArray[i];
				minDay = i;
			}
		}
		printf("1.make most profit :%d \n", maxPro);
		printf("2.buy on day %d (%d) and sell on day %d (%d) \n", dayBuy, stockArray[dayBuy], daySell, stockArray[daySell]);
	}
	{//3.
		int maxPro = 0;
		int transactionCount = 0;
		for (int i = 1; i < stockSize; ++i)
		{
			if (stockArray[i] - stockArray[i - 1] > 0) {
				maxPro += stockArray[i] - stockArray[i - 1];
				transactionCount++;
			}
		}
		printf("3.make most profit :%d  transaction count %d \n", maxPro,transactionCount);
	}

	{//4. 5.
		int maxPro = 0;
		int transactionCount = 0;
		int curMinDay = -1; 
		int curMaxDay = -1;
		std::vector<int> days;
		for (int i = 1; i < stockSize; ++i)
		{
			if (stockArray[i] - stockArray[i - 1] >= 0) {
				curMaxDay = i;
				if (curMinDay == -1)
					curMinDay = i - 1;
			}
			else {
				if (curMinDay != -1) {
					maxPro += stockArray[curMaxDay] - stockArray[curMinDay];
					days.push_back(curMinDay);
					days.push_back(curMaxDay);
					curMaxDay = 0;
					curMinDay = -1;
					transactionCount++;
				}
			}
			if (i == stockSize - 1) {
				if (curMinDay != -1) {
					maxPro += stockArray[curMaxDay] - stockArray[curMinDay];
					days.push_back(curMinDay);
					days.push_back(curMaxDay);
					curMaxDay = 0;
					curMinDay = -1;
					transactionCount++;
				}
			}
		}
		printf("4.make most profit :%d  transaction count %d \n", maxPro, transactionCount);
		printf("5.\n");
		for (size_t i = 0; i < days.size(); i = i + 2) {
			printf("(%d,%d)  ", days[i], days[i + 1]);
		}
		printf("\n");
	}


	freeArray();
	return 0;
}

