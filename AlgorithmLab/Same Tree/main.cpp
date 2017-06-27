// Same Tree.cpp : Defines the entry point for the console application.
//


/*	question:

Given two binary trees, write a function to check if they are equal or not.
Two binary trees are considered equal if they are structurally identical and the nodes have the same value.

*/

/* 思路：
	递归检测两颗树即可
*/
#include "stdafx.h"

#include<cstdlib>
#include<time.h>

struct TreeNode
{
	TreeNode() :Lt(nullptr), Rt(nullptr) , value(0){}
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
	TreeNode* tree0 = GetNewTree();
	TreeNode* tree1 = GetNewTree();
	printf("Tree0 and Tree1 are : %s \n", EqualTree(tree0, tree1) ? "same" : "not the same");
	printf("Tree0 and Tree0 are : %s \n", EqualTree(tree0, tree0) ? "same" : "not the same");
	printf("Tree1 and Tree1 are : %s \n", EqualTree(tree1, tree1) ? "same" : "not the same");
	return 0;
}

