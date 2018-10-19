#pragma once

struct RBTreeNode
{
	RBTreeNode * Parent;
	RBTreeNode * Left;
	RBTreeNode * Right;
	bool		 Black;
	int			 Key;
};

class RBTree
{
protected:
	void LeftRotate(RBTreeNode* _X)
	{
		RBTreeNode* Y = _X->Right;
		if (!Y)
			return;

		RBTreeNode* yL = Y->Left;
		_X->Right = yL;
		yL->Left = _X;
		
	}

	void RightRoate(RBTreeNode* _Y)
	{
		RBTreeNode* X = _Y->Left;
		if (!X)
			return;

		RBTreeNode* xR = X->Right;
		X->Right = _Y;
		_Y->Left->Left = xR;
	}

protected:
	RBTreeNode* _Root;
};