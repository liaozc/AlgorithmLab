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

	RBTree() : _Root(0), _nHeight(0){}
	
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
		if (_Root)
			_Root->Red = false;
		return nullptr;
	}
	
	RBTreeNode* find(int key)
	{
		return _find(_Root, key);
	}

	int Height() const
	{
		return _Height(_Root);
		//return height;
	}

	bool IsInvalid() const
	{
		if (!_Root)
			return true;

		if (_Root->Red)
			return false;

		return _IsInvalid(_Root);
	}

	int Size() const
	{
		return _Size(_Root);
	}

protected:

	int _Size(RBTreeNode* node) const
	{
		if (!node)
			return 0;

		return _Size(node->Left) + _Size(node->Right) + 1;
	}

	bool _IsInvalid(RBTreeNode* node) const
	{
		if (!_NotRightRed(node))
			return false;

		if (!_NotRedRed(node))
			return false;

		if (!_BlackBlance(node))
			return false;

		return true;
	
	}

	int _BlackHeight(RBTreeNode* node) const
	{
		if (!node)
			return 0;

		int Height = std::max(_BlackHeight(node->Left), _BlackHeight(node->Right));
		Height += node->Red ? 0 : 1;
		return Height;
	}

	bool _BlackBlance(RBTreeNode* node) const
	{
		if (!node)
			return true;

		if (_BlackBlance(node->Left) && _BlackBlance(node->Right))
		{
			int HeightL = _BlackHeight(node->Left);
			int HeightR = _BlackHeight(node->Right);
			if (HeightL == HeightR)
				return true;
		}
		return false;
	}

	bool _NotRightRed(RBTreeNode* node) const
	{
		if (!node)
			return true;

		if (!node->Right)
			return true;

		if (node->Right->Red)
			return false;
	
		return (_NotRightRed(node->Left) && _NotRightRed(node->Right));
	}

	bool _NotRedRed(RBTreeNode* node) const
	{
		if (!node)
			return true;
		if (!node->Left)
			return true;
		if (node->Red && node->Left->Red)
			return false;

		return (_NotRedRed(node->Left) && _NotRedRed(node->Right));
	}


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
		else if (node->Key < Key)
		{
			node->Right = _Remove(node->Right, Key, bBlance);
			return _BlanceRemove(node, bBlance, false);
		}
		
		if (node->Key == Key)
		{
			if (!node->Right)
			{
				if (node->Left) // left must be red here
				{
					RBTreeNode* left = node->Left;
					left->Red = node->Red;
					delete node;
					bBlance = true; 
					return left;
				}
				else
				{
					bBlance = node->Red;
					delete node;
					return nullptr;
				}
			}
			else
			{
				RBTreeNode* sup = node->Right;
				while (sup->Left)
				{
					sup = sup->Left;
				}
				node->Key = sup->Key;
				sup->Key = Key;
				node->Right = _Remove(node->Right, Key, bBlance);
				return _BlanceRemove(node, bBlance, false);
			}	
		}

		bBlance = true;
		return node;
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
					node = _RotateLeft(node);
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
		else // right
		{
			RBTreeNode* left = node->Left;
			if (left->Red)
			{
				RBTreeNode* leftRight = left->Right;
				RBTreeNode* leftRightLeft = leftRight->Left;
				if (leftRightLeft && leftRightLeft->Red)
				{
					leftRightLeft->Red = false;
					RBTreeNode* temp = _RotateRight(node);
					RBTreeNode* temp2 = _RotateRight(node);
					temp->Right = temp2;
					node = _RotateLeft(temp);
				}
				else
				{
					leftRight->Red = true;
					RBTreeNode* temp = _RotateRight(node);
					temp->Red = false;
					node = temp;
				}
				bBlance = true;
				return node;
			}
			else if (node->Red)// !left->Red && node->Red
			{
				RBTreeNode* leftLeft = left->Left;
				if (leftLeft && leftLeft->Red)
				{
					node->Red = false;
					left->Red = true;
					leftLeft->Red = false;
					node = _RotateRight(node);
				}
				else
				{
					left->Red = true;
					node->Red = false;
				}
				bBlance = true;
				return node;
			}
			else// !left->Red && !node->Red
			{
				RBTreeNode* leftLeft = left->Left;
				if (leftLeft && leftLeft->Red)
				{
					leftLeft->Red = false;
					node = _RotateRight(node);
					bBlance = true;
					return node;
				}
				else
				{
					left->Red = true;
					bBlance = false;
					return node;
				}

			}
		} // right
		
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
	int _nHeight;
};