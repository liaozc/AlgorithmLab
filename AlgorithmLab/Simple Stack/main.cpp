// Stack Stack.cpp : Defines the entry point for the console application.
//


/*
做一个简单的stack 类并测试
*/

#include "stdafx.h"
#include "simple_stack.h"

struct Node 
{
	Node() :value(0) {}
	Node(int i) :value(i) {}
	int value;
};

int main()
{
	stack<Node> stackNodes(100);
	for (int i = 0; i < 100; ++i)
		stackNodes.push(Node(i));
	while (!stackNodes.empty()) {
		printf(" %d ", stackNodes.top().value);
		stackNodes.pop();
	}
	printf(" \n ");
    return 0;
}

