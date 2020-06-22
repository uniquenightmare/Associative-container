#define  _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
template<class T>
class BSTreeNode
{
public:
	BSTreeNode<T>* _left;
	BSTreeNode<T>* _right;
	T _value;

	BSTreeNode(const T&value = T())
		:_left(nullptr)
		, _right(nullptr)
		, _value(value)
	{}
};
template<class T>
class BSTree
{
public:
	typedef BSTreeNode<T> Node;
	typedef Node* pNode;
	pNode find(const T& value)
	{
		pNode cur = root;
		while (cur)
		{
			if (cur->_value == value) return cur;
			else if (value > cur->_value)
			{
				cur = cur->_right;
			}
			else
			{
				cur = cur->_left;
			}
			
		}
		return cur;
	}
	bool insert(const T& value)
	{
		if (!root)
		{
			root = new Node(value);
			return true;
		}
		pNode cur = root;
		pNode parent = nullptr;
		while (cur)
		{
			parent = cur;
			if (cur->_value == value) return false;
			
			else if (value > cur->_value)
			{
				cur = cur->_right;
			}
			else
			{
				cur = cur->_left;
			}
		}
		cur = new Node(value);
		if (value < parent->_value)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		return true;
	}
	void inoder(pNode _root)
	{
		if (_root)
		{
			inoder(_root->_left);
			cout << _root->_value << " ";
			inoder(_root->_right);
		}
	}
	void inOder()
	{
		inoder(root);
		cout << endl;
	}
	bool erase(const T& value)
	{
		
		pNode cur = root;
		pNode parent = nullptr;
		while (cur)
		{
			if (cur->_value == value) break;
			else if (cur->_value > value)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				parent = cur;
				cur = cur->_right;
			}
		}
		if (!cur) return false;
		if (!cur->_left)
		{
			if (cur != root)
			{
				if (parent->_left == cur)
				{
					parent->_left = cur->_right;
				}
				else
				{
					parent->_right = cur->_right;
				}
			}
			else
			{
				root = cur->_right;
			}
			delete cur;
			cur = nullptr;
		}
		else if (!cur->_right)
		{
			if (cur != root)
			{
				if (parent->_left == cur)
				{
					parent->_left = cur->_left;
				}
				else
				{
					parent->_right = cur->_left;
				}
			}
			else
			{
				root = cur->_left;
			}
			delete cur;
			cur = nullptr;
		}
		else
		{
			pNode pnext = cur->_left;
			parent = cur;
			while (pnext->_right)
			{
				parent = pnext;
				pnext = pnext->_right;
			}
			cur->_value = pnext->_value;
			if (parent->_left = pnext)
			{
				parent->_left = pnext->_left;

			}
			else
			{
				parent->_right = pnext->_left;
			}
			delete pnext;
			pnext = nullptr;
		}
		return true;
	}
private:
	pNode root = nullptr;
	
};
void test()
{
	BSTree<int> bst;
	bst.insert(5);
	bst.insert(3);
	bst.insert(7);
	bst.insert(1);
	bst.insert(1);
	bst.insert(2);
	bst.insert(8);
	bst.insert(9);
	bst.insert(6);
	bst.inOder();
	cout<<bst.erase(3)<<endl;
	bst.inOder();

}
int main()
{
	test();
	system("pause");
	return 0;
}