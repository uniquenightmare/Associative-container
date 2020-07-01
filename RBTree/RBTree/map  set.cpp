#define  _CRT_SECURE_NO_WARNINGS 1
#include<utility>
#include<iostream>
using namespace std;
enum COLOR
{
	BLACK,
	RED
};
template< class V>
struct RBNode
{
	RBNode< V>* _left;
	RBNode< V>* _right;
	RBNode< V>* _parent;
	V _value;
	COLOR _color;
	RBNode(const V& value = V())
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _value(value)
		, _color(RED)
	{}
};
template<class V>
struct RBIterator
{
	typedef RBNode<V> Node;
	typedef Node* pNode;
	typedef RBIterator<V> Self;
	pNode _node;
	RBIterator(pNode node)
		:_node(node)
	{}
	V& operator *()
	{
		return _node->_value;
	}
	V* operator ->()
	{
		return &_node->_value;
	}
	bool operator != (const Self& it)
	{
		return _node != it._node;
	}
	Self& operator ++()
	{
		if (_node->_right)
		{
			_node = _node->_right;
			while (_node->_left)
			{
				_node = _node->_left;
			}
		}
		else
		{
			
			pNode parent = _node->_parent;
			
			while (_node == parent->_right)
			{
				_node = parent;
				parent = parent->_parent;
			}
			if (_node->_right != parent)
			_node = parent;
		}
		return *this;
	}
	Self& operator --()
	{
		if (_node->_left)
		{
			_node = _node->_left;
			while (_node->_right)
			{
				_node = _node->_right;
			}
		}
		else
		{

			pNode parent = _node->_parent;

			while (_node == parent->_left)
			{
				_node = parent;
				parent = parent->_parent;
			}
			if (_node->_left != parent)
				_node = parent;
		}
		return *this;
	}
};
template<class K, class V,class KeyofValue>
class RBTree
{
public:
	typedef RBNode<V> Node;
	typedef Node* pNode;
	typedef RBIterator<V> iterator;
	iterator begin()
	{
		return iterator(_header->_left);
	}
	iterator end()
	{
		return iterator(_header);
	}

	iterator rbegin()
	{
		return iterator(_header->_right);
	}
	RBTree()
	{
		_header = new Node();
		_header->_left = _header;
		_header->_right = _header;
	}
	pair<iterator,bool> insert(const V&value)
	{
		if (!_header->_parent)
		{
			pNode root = new Node(value);
			root->_color = BLACK;
			root->_parent = _header;
			_header->_parent = root;
			_header->_left = root;
			_header->_right = root;
			return make_pair(iterator(root),true);
		}
		pNode cur = _header->_parent;
		pNode parent = nullptr;
		KeyofValue kov;
		while (cur)
		{
			parent = cur;
			if (kov(cur->_value) == kov(value))
			{
				return make_pair(iterator(cur), false);
			}
			else if (kov(cur->_value) > kov(value))
			{
				cur = cur->_left;
			}
			else
			{
				cur = cur->_right;
			}
		}
		cur = new Node(value);
		pNode newnode = cur;
		if (kov(parent->_value) > kov(cur->_value))
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		cur->_parent = parent;
		while (cur != _header->_parent&&cur->_parent->_color == RED)
		{
			parent = cur->_parent;
			pNode grandpa = parent->_parent;
			if (grandpa->_left == parent)
			{
				pNode uncle = grandpa->_right;
				if (uncle&&uncle->_color == RED)
				{
					parent->_color = uncle->_color = BLACK;
					grandpa->_color = RED;
					cur = grandpa;
				}
				else
				{
					if (cur == parent->_right)
					{
						RotateL(parent);
						swap(cur, parent);
					}
					RotateR(grandpa);
					parent->_color = BLACK;
					grandpa->_color = RED;
					break;
				}
			}
			else
			{
				pNode uncle = grandpa->_left;
				if (uncle&&uncle->_color == RED)
				{
					parent->_color = uncle->_color = BLACK;
					grandpa->_color = RED;
					cur = grandpa;
				}
				else
				{
					if (cur == parent->_left)
					{
						RotateR(parent);
						swap(cur, parent);
					}
					RotateL(grandpa);
					parent->_color = BLACK;
					grandpa->_color = RED;
					break;
				}
			}

		}
		_header->_parent->_color = BLACK;
		_header->_left = leftMost();
		_header->_right = rightMost();
		return make_pair(iterator(newnode), true);
	}
	pNode leftMost()
	{
		pNode cur = _header->_parent;
		while (cur&&cur->_left)
		{
			cur = cur->_left;
		}
		return cur;
	}
	pNode rightMost()
	{
		pNode cur = _header->_parent;
		while (cur&&cur->_right)
		{
			cur = cur->_right;
		}
		return cur;
	}
	void RotateR(pNode parent)
	{
		pNode subL = parent->_left;
		pNode subLR = subL->_right;
		parent->_left = subLR;
		subL->_right = parent;
		if (subLR)
			subLR->_parent = parent;
		if (parent == _header->_parent)
		{
			_header->_parent = subL;
			subL->_parent = _header;
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
	}
	void RotateL(pNode parent)
	{
		pNode subR = parent->_right;
		pNode subRL = subR->_left;
		subR->_left = parent;
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;
		if (parent == _header->_parent)
		{
			_header->_parent = subR;
			subR->_parent = _header;
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

	}
	void inorder()
	{
		inOrder(_header->_parent);
		cout << endl;
	}
	void inOrder(pNode root)
	{
		if (!root) return;
		inOrder(root->_left);
		cout << root->_value.first << "-->" << root->_value.second << endl;;
		inOrder(root->_right);
	}
	bool isRBTree()
	{
		pNode root = _header->_parent;
		if (!root)
		{
			return true;
		}
		if (root->_color == RED) return false;
		pNode cur = root;
		int blacksum = 0;
		while (cur)
		{
			if (cur->_color == BLACK) blacksum++;
			cur = cur->_right;
		}
		int k = 0;
		return _isRBTree(root, k, blacksum);
	}
	bool _isRBTree(pNode root, int k, int blacksum)
	{
		if (!root)
		{
			if (blacksum != k)
			{
				return false;
			}
			return true;
		}
		if (root->_color == BLACK)
		{
			k++;
		}
		pNode parent = root->_parent;
		if (parent&&parent->_color == RED&&root->_color == RED)
		{
			return false;
		}
		return _isRBTree(root->_left, k, blacksum) && _isRBTree(root->_right, k, blacksum);
	}

private:
	pNode _header;

};
template<class K,class V>
class MyMap
{
	
	struct MapKeyofValue
	{
		const K& operator()(const pair<K, V>& data)
		{
			return data.first;
		}
	};
public:
	typedef typename RBTree<K, pair<K, V>, MapKeyofValue>::iterator iterator;
	iterator begin()
	{
		return _rbt.begin();
	}
	iterator end()
	{
		return _rbt.end();
	}
	iterator rbegin()
	{
		return _rbt.rbegin();
	}
	bool insert(const pair<K, V>& data)
	{
		return _rbt.insert(data).second;
	}
	V& operator[](const K& key)
	{
		return (*(_rbt.insert(make_pair(key, V())).first)).second;
	}
private:
	RBTree<K, pair<K, V>, MapKeyofValue> _rbt;
};
template<class K>
class MySet
{
	struct SetKeyofValue
	{
		const K& operator()(const K&data)
		{
			return data;
		}
	};
public:
	bool insert(const K& key)
	{
		return _rbt.insert(key);
	}
private:
	RBTree<K, K, SetKeyofValue> _rbt;
};
void test()
{
	MyMap<int, int>mp;
	mp.insert(make_pair(2, 2));
	mp.insert(make_pair(1, 1));
	mp.insert(make_pair(3, 3));
	mp.insert(make_pair(4, 4));
	MyMap<int,int>::iterator it = mp.begin();
	cout << mp[1] << endl;
	while (it != mp.end())
	{
		cout << it->first << "-->" << it->second << endl;
		++it;
	}
	cout << endl;
	cout << mp[5] << endl;
	it = mp.rbegin();
	while (it != mp.end())
	{
		cout << it->first << "-->" << it->second << endl;
		--it;
	}
}
int main()
{
	test();
	system("pause");
	return 0;
}