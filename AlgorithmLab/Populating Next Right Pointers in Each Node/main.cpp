// Populating Next Right Pointers in Each Node.cpp : Defines the entry point for the console application.
//


/*	question:

Given a binary tree

struct TreeLinkNode {
TreeLinkNode *left;
TreeLinkNode *right;
TreeLinkNode *next;
}
Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

You may only use constant extra space.
You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).
For example,
Given the following perfect binary tree,
  1
 /  \
2    3
/ \  / \
4  5  6  7
After calling your function, the tree should look like:
   1 -> NULL
 /  \
2 -> 3 -> NULL
/ \  / \
4->5->6->7 -> NULL

*/

/* 思路：
	
	递归： 访问每颗子树，把右孩子赋值给左

*/

#include "stdafx.h"
#include <queue>

struct TreeLinkNode {
	TreeLinkNode() :left(nullptr), right(nullptr), next(nullptr), iVal(0){}
	TreeLinkNode *left;
	TreeLinkNode *right;
	TreeLinkNode *next;
	int iVal;
};

TreeLinkNode* GenerateTree(int level,int val)
{
	TreeLinkNode* node = new TreeLinkNode();
	node->iVal = val;
	if (level > 0) {
		node->left = GenerateTree(level - 1,2 * val + 1);
		node->right = GenerateTree(level - 1, 2 * val + 2);
	}
	return node;
}

void FreeTree(TreeLinkNode* root)
{
	if (root) {
		FreeTree(root->left);
		FreeTree(root->right);
		delete root;
	}
}

void AssignNext(TreeLinkNode*  root)
{
	std::queue<TreeLinkNode*> linkQueue;
	linkQueue.push(root);
	while (!linkQueue.empty()) {
		int size = linkQueue.size();
		TreeLinkNode* pre = nullptr;
		for (int i = 0; i < size; ++i) {
			TreeLinkNode* node = linkQueue.front();
			if (node->left)linkQueue.push(node->left);
			if (node->right)linkQueue.push(node->right);
			linkQueue.pop();
			if (pre) pre->next = node;
			pre = node;
		}
	}
}

void PrintTree(TreeLinkNode* root)
{
	TreeLinkNode* treeLeftNode = root;
	while (treeLeftNode) {
		TreeLinkNode* iterNode = treeLeftNode;
		while (iterNode) {
			printf("%d ", iterNode->iVal);
			iterNode = iterNode->next;
		}
		printf("\n");
		treeLeftNode = treeLeftNode->left;
	}
}


int main()
{
	TreeLinkNode* root = GenerateTree(10,0);
	AssignNext(root);
	PrintTree(root);
	FreeTree(root);
    return 0;
}

