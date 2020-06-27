#define  _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<math.h>
#include<assert.h>
using namespace std;
template<class T>
struct AVLNode
{
	AVLNode<T>* _left;
	AVLNode<T>* _right;
	AVLNode<T>* _parent;
	T _value;
	int _bf;
	AVLNode(const T& value = T())
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _value(value)
		, _bf(0)
	{}
};
template<class T>
class AVL
{
public:
	typedef AVLNode<T> Node;
	typedef Node* pNode;
	void RotateR(pNode parent)
	{
		pNode subL = parent->_left;
		pNode subLR = subL->_right;
		parent->_left = subLR;
		subL->_right = parent;
		if (subLR)
			subLR->_parent = parent;
		if (parent == _root)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			pNode node = parent->_parent;
			if (parent == node->_left)
			{
				node->_left = subL;
			}
			else
			{
				node->_right = subL;
			}
			subL->_parent = node;
		}
		parent->_parent = subL;
		subL->_bf = parent->_bf = 0;
	}
	void RotateL(pNode parent)
	{
		pNode subR = parent->_right;
		pNode subRL = subR->_left;
		subR->_left = parent;
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;
		if (parent == _root)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			pNode node = parent->_parent;
			if (node->_left == parent)
			{
				node->_left = subR;
			}
			else
			{
				node->_right = subR;
			}
			subR->_parent = node;
		}
		parent->_parent = subR;
		subR->_bf = parent->_bf = 0;
	}
	bool insert(const T& val)
	{
		if (!_root)
		{
			
			_root = new Node(val);
			return true;
		}
		pNode cur = _root;
		pNode parent = nullptr;
		while (cur)
		{
			parent = cur;
			if (cur->_value == val) return false;
			else if (cur->_value > val)
			{
				cur = cur->_left;
			}
			else
			{
				cur = cur->_right;
			}
		}
		cur = new Node(val);
		if (parent->_value > val)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		cur->_parent = parent;
		while (parent)
		{
			if (parent->_left == cur)
			{
				--parent->_bf;
			}
			else
			{
				++parent->_bf;
			}
			if (parent->_bf == 0)
			{
				break;
			}
			else if (abs(parent->_bf) == 1)
			{
				cur = parent;
				parent = parent->_parent;
			}
			else if (abs(parent->_bf) == 2)
			{
				if (parent->_bf == 2 && cur->_bf == 1)
				{
					RotateL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == -1)
				{
					RotateR(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					pNode subL = parent->_left;
					pNode subLR = subL->_right;
					int bf = subLR->_bf;
					RotateL(cur);
					RotateR(parent);
					if (bf == 1)
					{
						parent->_bf = 0;
						subL->_bf = -1;
					}
					else if (bf == -1)
					{
						subL->_bf = 0;
						parent->_bf = 1;
					}
				}
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					pNode subR = parent->_right;
					pNode subRL = subR->_left;
					int bf = subRL->_bf;
					RotateR(cur);
					RotateL(parent);
					if (bf == 1)
					{
						subR->_bf = 0;
						parent->_bf = -1;
					}
					else if (bf == -1)
					{
						parent->_bf = 0;
						subR->_bf = -1;
					}
				}

				break;
			}
			else
			{
				assert(false);
			}
		}
		return true;
	}
	void inorder()
	{
		inOrder(_root);
		cout << endl;
	}
	void inOrder(pNode root)
	{
		if (!root) return;
		inOrder(root->_left);
		cout << root->_value << " ";
		inOrder(root->_right);
	}
	int height(pNode root)
	{
		if (!root) return 0;
		int left = height(root->_left);
		int right = height(root->_right);
		return left > right ? left + 1 : right + 1;
	}
	bool isAVL()
	{
		return _isAVL(_root);
	}
	bool _isAVL(pNode root)
	{
		if (!root) return true;
		int left = height(root->_left);
		int right = height(root->_right);
		if (right - left != root->_bf)
		{
			cout << "节点 " << root->_value << ":平衡因子异常" << endl;
			return false;
		}
		return abs(root->_bf) < 2 && _isAVL(root->_left) && _isAVL(root->_right);
	}
	bool erase(const T&val)
	{

	}
private:
	pNode _root;
};
void test()
{
	AVL<int>* avl = new AVL<int>();
	//int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int arr[] = {4,2,6,1,3,5,15,7,16,14 };
	for (auto &ch : arr)
	{
		avl->insert(ch);
	}
	avl->inorder();
	cout << avl->isAVL() << endl;
}
int main()
{
	test();
	system("pause");
	return 0;

}
