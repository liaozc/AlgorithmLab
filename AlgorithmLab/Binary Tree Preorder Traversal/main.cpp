// Binary Tree Preorder Traversal : Defines the entry point for the console application.
//


/*	question:

Given a binary tree, return the preorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
	1
	 \
	  2
	 /
    3
return [1,2,3].
Note: Recursive solution is trivial, could you do it iteratively?
*/

/* 思路：
	要用非递归的方式 ，其实也就是将要遍历的节点入栈，这个和递归调用时系统本身的处理是一样的
*/

#include "stdafx.h"

#include<cstdlib>
#include<time.h>
#include<stack>

struct TreeNode
{
	TreeNode() :Lt(nullptr), Rt(nullptr), value(0) {}
	TreeNode* Lt;
	TreeNode* Rt;
	int value;
};

TreeNode* GetTreeNode(int step)
{
	int r = rand() % 20;
	if (r < 10 || step == 100) return nullptr;
	TreeNode* node = new TreeNode();
	node->value = r;
	node->Lt = GetTreeNode(step + 1);
	node->Rt = GetTreeNode(step + 1);
	return node;
}

TreeNode* GetNewTree()
{
	TreeNode* root = new TreeNode();
	root->Lt = GetTreeNode(0);
	root->Rt = GetTreeNode(0);
	return root;
}

int GetTreeHeight(TreeNode* tree)
{
	if (tree == nullptr) return 0;
	int left = GetTreeHeight(tree->Lt);
	int right = GetTreeHeight(tree->Rt);
	return (left > right ? left : right) + 1;
}

bool EqualTree(TreeNode* tree0, TreeNode* tree1)
{
	if (!tree0 && !tree1) return true; //空树相等
	if ((!tree0 && tree1) || (tree0 && !tree1)) return false;
	if (tree0->value != tree1->value) return false;
	bool leftEqual = EqualTree(tree0->Lt, tree1->Lt);
	if (!leftEqual) return false;
	bool rightEqual = EqualTree(tree0->Rt, tree1->Rt);
	if (!rightEqual) return false;
	return true;
}

void Preorder_Recursive(TreeNode* tree) //递归版本
{
	if (!tree) return;
	printf("%d,",tree->value);
	Preorder_Recursive(tree->Lt);
	Preorder_Recursive(tree->Rt);
}

void Preorder_NotRecursive(TreeNode* tree) //非递归版本
{
	if (!tree) return;
	std::stack<TreeNode*> travelStack;
	travelStack.push(tree);
	while (!travelStack.empty()){
		TreeNode* node = travelStack.top();
		travelStack.pop();
		printf("%d,", node->value);
		if (node->Rt) travelStack.push(node->Rt);
		if (node->Lt) travelStack.push(node->Lt);
	}
}

void FreeTree(TreeNode* tree)
{
	if (!tree) return;
	FreeTree(tree->Lt);
	FreeTree(tree->Rt);
	delete tree;
}

int main()
{
	srand(time(0));
	TreeNode* tree = GetNewTree();
	printf("Recursive:[ "); 
		Preorder_Recursive(tree);
	printf(" ]\n");
	printf("Not Recursive:[ ");
		Preorder_NotRecursive(tree);
	printf(" ]\n");
	FreeTree(tree);
    return 0;
}

