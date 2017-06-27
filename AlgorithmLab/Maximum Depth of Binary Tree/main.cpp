//Maximum Depth of Binary Tree: Defines the entry point for the console application.
//


/*	question:

Given a binary tree, find its maximum depth.
The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

*/

/* 思路：
	简单的递归找树高度
*/

#include "stdafx.h"
#include<cstdlib>
#include<time.h>

struct TreeNode
{
	TreeNode() :Lt(nullptr), Rt(nullptr) {}
	TreeNode* Lt;
	TreeNode* Rt;
};

TreeNode* GetTreeNode(int step)
{
	int r = rand() % 20;
	if (r < 10 || step == 100) return nullptr;
	TreeNode* node = new TreeNode();
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

void FreeTree(TreeNode* tree)
{
	if (!tree) return;
	FreeTree(tree->Lt);
	FreeTree(tree->Rt);
	delete tree;
}

int main()
{
	//随机构建树
	srand(time(0));
	TreeNode* tree = GetNewTree();
	int height = GetTreeHeight(tree);
	printf("tree height :%d \n", height);
	FreeTree(tree);
    return 0;
}

