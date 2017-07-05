// Single Number.cpp : Defines the entry point for the console application.
//


/*	question:

Given a linked list, determine if it has a cycle in it.
Follow up:
Can you solve it without using extra space?

*/

/* ˼·��
	����Ҫ�����ö���ı�־λ����־�ڵ㡣������ԣ�ÿ����־λ�и����ʴ�����־������һ�飬���ֱ�־λΪ2�ļ��л��ˡ�
	*->*->*->*->*->o->*->*->*
				   |		|
				   *		*
				   |		|
				   *-*-*-*-* 
	��ͼ��ʾ��o��Ϊ������ڵ㣬���������һ��һ����ָ�룬������ָ�뵽��o��ʱ����ָ����Ȧ��ĳλ�ã���������֮��ľ���ΪN
	ָ��ÿ�ο���1�����������Ϊ2������Ϊ1�� ����N��֮����׷�����ģ�����ָ�����
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
ListNode* tail = nullptr; //ֻ��Ϊ��ɾ��

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

