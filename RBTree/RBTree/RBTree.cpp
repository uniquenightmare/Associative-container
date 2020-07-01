#define  _CRT_SECURE_NO_WARNINGS 1
//#include<utility>
//#include<iostream>
//using namespace std;
//enum COLOR
//{
//	BLACK,
//	RED
//};
//template<class K,class V>
//struct RBNode
//{
//	RBNode<K, V>* _left;
//	RBNode<K, V>* _right;
//	RBNode<K, V>* _parent;
//	pair<K,V> _value;
//	COLOR _color;
//	RBNode(const pair<K, V>& value = pair<K,V>())
//		:_left(nullptr)
//		, _right(nullptr)
//		, _parent(nullptr)
//		, _value(value)
//		, _color(RED)
//	{}
//};
//template<class K, class V>
//class RBTree
//{
//public:
//	typedef RBNode<K, V> Node;
//	typedef Node* pNode;
//	RBTree()
//	{
//		_header = new Node();
//		_header->_left = _header;
//		_header->_right = _header;
//	}
//	bool insert(const pair<K, V>&value)
//	{
//		if (!_header->_parent)
//		{
//			pNode root = new Node(value);
//			root->_color = BLACK;
//			root->_parent = _header;
//			_header->_parent = root;
//			_header->_left = root;
//			_header->_right = root;
//			return true;
//		}
//		pNode cur = _header->_parent;
//		pNode parent = nullptr;
//		while (cur)
//		{
//			parent = cur;
//			if (cur->_value.first == value.first)
//			{
//				return false;
//			}
//			else if (cur->_value.first > value.first)
//			{
//				cur = cur->_left;
//			}
//			else
//			{
//				cur = cur->_right;
//			}
//		}
//		cur = new Node(value);
//		if (parent->_value.first > cur->_value.first)
//		{
//			parent->_left = cur;
//		}
//		else
//		{
//			parent->_right = cur;
//		}
//		cur->_parent = parent;
//		while (cur!= _header->_parent&&cur->_parent->_color == RED)
//		{
//			parent = cur->_parent;
//			pNode grandpa = parent->_parent;
//			if (grandpa->_left == parent)
//			{
//				pNode uncle = grandpa->_right;
//				if (uncle&&uncle->_color == RED)
//				{
//					parent->_color = uncle->_color = BLACK;
//					grandpa->_color = RED;
//					cur = grandpa;
//				}
//				else
//				{
//					if (cur == parent->_right)
//					{
//						RotateL(parent);
//						swap(cur, parent);
//					}
//					RotateR(grandpa);
//					parent->_color = BLACK;
//					grandpa->_color = RED;
//					break;
//				}
//			}
//			else
//			{
//				pNode uncle = grandpa->_left;
//				if (uncle&&uncle->_color == RED)
//				{
//					parent->_color = uncle->_color = BLACK;
//					grandpa->_color = RED;
//					cur = grandpa;
//				}
//				else
//				{
//					if (cur == parent->_left)
//					{
//						RotateR(parent);
//						swap(cur, parent);
//					}
//					RotateL(grandpa);
//					parent->_color = BLACK;
//					grandpa->_color = RED;
//					break;
//				}
//			}
//
//		}
//		_header->_parent->_color = BLACK;
//		_header->_left = leftMost();
//		_header->_right = rightMost();
//		return true;
//	}
//	pNode leftMost()
//	{
//		pNode cur = _header->_parent;
//		while (cur&&cur->_left)
//		{
//			cur = cur->_left;
//		}
//		return cur;
//	}
//	pNode rightMost()
//	{
//		pNode cur = _header->_parent;
//		while (cur&&cur->_right)
//		{
//			cur = cur->_right;
//		}
//		return cur;
//	}
//	void RotateR(pNode parent)
//	{
//		pNode subL = parent->_left;
//		pNode subLR = subL->_right;
//		parent->_left = subLR;
//		subL->_right = parent;
//		if (subLR)
//			subLR->_parent = parent;
//		if (parent == _header->_parent)
//		{
//			_header->_parent = subL;
//			subL->_parent = _header;
//		}
//		else
//		{
//			pNode node = parent->_parent;
//			if (parent == node->_left)
//			{
//				node->_left = subL;
//			}
//			else
//			{
//				node->_right = subL;
//			}
//			subL->_parent = node;
//		}
//		parent->_parent = subL;
//	}
//	void RotateL(pNode parent)
//	{
//		pNode subR = parent->_right;
//		pNode subRL = subR->_left;
//		subR->_left = parent;
//		parent->_right = subRL;
//		if (subRL)
//			subRL->_parent = parent;
//		if (parent == _header->_parent)
//		{
//			_header->_parent = subR;
//			subR->_parent = _header;
//		}
//		else
//		{
//			pNode node = parent->_parent;
//			if (node->_left == parent)
//			{
//				node->_left = subR;
//			}
//			else
//			{
//				node->_right = subR;
//			}
//			subR->_parent = node;
//		}
//		parent->_parent = subR;
//		
//	}
//	void inorder()
//	{
//		inOrder(_header->_parent);
//		cout << endl;
//	}
//	void inOrder(pNode root)
//	{
//		if (!root) return;
//		inOrder(root->_left);
//		cout << root->_value.first << "-->" << root->_value.second << endl;;
//		inOrder(root->_right);
//	}
//	bool isRBTree()
//	{
//		pNode root = _header->_parent;
//		if (!root)
//		{
//			return true;
//		}
//		if (root->_color == RED) return false;
//		pNode cur = root;
//		int blacksum = 0;
//		while (cur)
//		{
//			if (cur->_color == BLACK) blacksum++;
//			cur = cur->_right;
//		}
//		int k = 0;
//		return _isRBTree(root, k, blacksum);
//	}
//	bool _isRBTree(pNode root, int k, int blacksum)
//	{
//		if (!root)
//		{
//			if (blacksum != k)
//			{
//				return false;
//			}
//			return true;
//		}
//		if (root->_color == BLACK)
//		{
//			k++;
//		}
//		pNode parent = root->_parent;
//		if (parent&&parent->_color == RED&&root->_color == RED)
//		{
//			return false;
//		}
//		return _isRBTree(root->_left, k, blacksum) && _isRBTree(root->_right, k, blacksum);
//	}
//private:
//	pNode _header;
//
//};
//void test()
//{
//	RBTree<int, int> rbt;
//	rbt.insert(make_pair(1, 1));
//	rbt.insert(make_pair(10, 1));
//	rbt.insert(make_pair(-1, 1));
//	rbt.insert(make_pair(-2, 1));
//	rbt.insert(make_pair(100, 1));
//	rbt.insert(make_pair(19, 1));
//	rbt.insert(make_pair(21, 1));
//	rbt.inorder();
//	cout << rbt.isRBTree();
//}
//int main()
//{
//	test();
//	system("pause");
//	return 0;
//}