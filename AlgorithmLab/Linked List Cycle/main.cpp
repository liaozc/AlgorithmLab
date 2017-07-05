// Single Number.cpp : Defines the entry point for the console application.
//


/*	question:

Given a linked list, determine if it has a cycle in it.
Follow up:
Can you solve it without using extra space?

*/

/* 思路：
	题中要求不能用多余的标志位来标志节点。如果可以，每个标志位有个访问次数标志，遍历一遍，出现标志位为2的即有环了。
	*->*->*->*->*->o->*->*->*
				   |		|
				   *		*
				   |		|
				   *-*-*-*-* 
	如图所示，o点为环形入口点，如果有两个一快一慢的指针，当慢的指针到达o点时，快指针在圈内某位置，假如他们之间的距离为N
	指针每次靠近1，（例如快速为2，低速为1） 这样N步之后快的追上慢的，两个指针相等
*/

#include "stdafx.h"
#include<cstdlib>
#include<time.h>
struct ListNode
{
	ListNode() : next(nullptr) {}
	ListNode* next;
};


int listCount = 0;
ListNode* head = nullptr;
ListNode* tail = nullptr; //只是为了删除

ListNode* GetNextNode()
{
	ListNode* node = new ListNode();
	listCount++;
	if (listCount < 100)
		node->next = GetNextNode();
	else
		tail = node;
	return node;
}

void RingList()
{
	int t = rand() % 200;
	t += rand() % 200;
	t += rand() % 200;
	t += rand() % 200;
	t = t >> 2;
	if (t < listCount) {
		ListNode* node = head;
		for (int i = 0; i < t; ++i)
			node = node->next;
		tail->next = node;
	}
}

void GenerateList()
{
	listCount = 0;
	head = GetNextNode();
	RingList();
}

int IsRingList()
{
	ListNode* pSlow = head;
	ListNode* pQuick = head;
	bool ring = false;
	while (pQuick) {
		pSlow = pSlow->next;
		pQuick = pQuick->next;
		if (!pQuick) break;
		pQuick = pQuick->next;
		if (pSlow == pQuick) {
			ring = true;
			break;
		}
	}
	if (ring) {
		ListNode* node = head;
		for (int i = 0; i < listCount; ++i) {
			if (pSlow == node)
				return i;
			node = node->next;
		}
	}
	return -1;
}


void FreeList()
{
	ListNode* node = head;
	while (node) {
		ListNode* tempNode = node;
		bool exit = node == tail;
		node = node->next;
		delete tempNode;
		if (exit) break;

	}
	head = tail = nullptr;
}

int main()
{
	srand(time(0));
	GenerateList();
	printf("is ring ? %d \n", IsRingList());
	FreeList();
    return 0;
}

