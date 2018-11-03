#pragma once

struct RBTreeNode
{
	RBTreeNode * Left;
	RBTreeNode * Right;
	bool		 Red;
	int			 Key;
};

class RBTree
{

public:

	RBTree() : _Root(0) {}
	
	RBTreeNode* Insert(int key)
	{
		_Root = _Insert(_Root, key);
		_Root->Red = false;
		return _Root;
	}

	RBTreeNode* Remove(int key)
	{
		bool bBlance = false;
		_Root = _Remove(_Root, key, bBlance);
		return nullptr;
	}
	
	RBTreeNode* find(int key)
	{
		return _find(_Root, key);
	}

	int Height() const
	{
		return _Height(_Root);
	}

protected:

	RBTreeNode* _Remove(RBTreeNode* node, int Key, bool& bBlance)
	{
		if (!node)
		{
			bBlance = true;
			return nullptr;
		}

		if (node->Key > Key)
		{
			node->Left = _Remove(node->Left, Key, bBlance);
			return _BlanceRemove(node, bBlance, true);
			
		}

		if (node->Key == Key)
		{
			if ()
			delete node;
			return nullptr;
		}

	}

	RBTreeNode* _BlanceRemove(RBTreeNode* node, bool& bBlance, bool bLeft)
	{
		if (bBlance) return node;
		if (!node)
		{
			bBlance = true; 
			return node;
		}

		if (bLeft)
		{
			if (node->Red)
			{
				RBTreeNode* right = node->Right;
				RBTreeNode* rightLeft = right->Left;
				if (rightLeft && rightLeft->Red)
				{
					node->Red = false;
					RBTreeNode* tNode = _RotateRight(right);
					node->Right = tNode;
					tNode = _RotateLeft(node);
					node = tNode;
				}
				else
				{
					RBTreeNode* tNode = _RotateLeft(node);
					node = tNode;
				}
				bBlance = true;
				return node;
			}
			else // !node->Red
			{
				RBTreeNode* right = node->Right;
				RBTreeNode* rightLeft = right->Left;
				if (rightLeft && rightLeft->Red)
				{
					rightLeft->Red = false;
					RBTreeNode* tNode = _RotateRight(right);
					node->Right = tNode;
					node = _RotateRight(node);
					bBlance = true;
					return node;
				}
				else
				{
					node->Red = true;
					node = _RotateLeft(node);
					bBlance = false;
					return node;
				}
			}


		}

	}

	int _Height(RBTreeNode* node) const
	{
		if (!node) return 0;

		int left = _Height(node->Left);
		int right = _Height(node->Right);

		return std::max(left, right) + 1;
	}


	RBTreeNode* _find(RBTreeNode* node, int key)
	{
		if (node == nullptr)
			return nullptr;

		if (node->Key == key)
			return node;

		if (node->Key < key)
			return _find(node->Right, key);
		else
			return _find(node->Left, key);

		return nullptr;
	}

	RBTreeNode* _Insert(RBTreeNode* node, int key)
	{
		if (!node)
		{
			node = new RBTreeNode();
			node->Key = key;
			node->Left = node->Right = nullptr;
			node->Red = true;
			return node;
		}

		if (node->Key == key)
			return node;

		if (node->Key < key)
			node->Right = _Insert(node->Right, key);
		else
			node->Left = _Insert(node->Left, key);

		//ÓÒºì
		if (_ISRED(node->Right) && !_ISRED(node->Left))
		{
			bool bRed = node->Red;
			RBTreeNode* h = _RotateLeft(node);
			h->Red = bRed;
			node->Red = true;
			node = h;
		}
		//ºìºì
		if (_ISRED(node->Left) && _ISRED(node->Left->Left))
		{
			bool bRed = node->Red;
			RBTreeNode* h = _RotateRight(node);
			h->Right->Red = true;
			h->Red = bRed;
			node = h;
		}
		//Ë«ºì
		if (_ISRED(node->Left) && _ISRED(node->Right))
		{
			node->Left->Red = false;
			node->Right->Red = false;
			node->Red = true;
		}

		return node;
	}

	bool _ISRED(RBTreeNode* node)
	{
		return node && node->Red;
	}

	RBTreeNode* _RotateLeft(RBTreeNode* node)
	{
		if (!node)
			return nullptr;

		if (!node->Right)
			return node;

		RBTreeNode* right = node->Right;
		node->Right = right->Left;
		right->Left = node;
	
		return right;
	}

	RBTreeNode* _RotateRight(RBTreeNode* node)
	{
		if (!node)
			return nullptr;
		
		if (!node->Left)
			return node;

		RBTreeNode* left = node->Left;
		node->Left = left->Right;
		left->Right = node;

		return left;
	}

protected:
	RBTreeNode* _Root;
};