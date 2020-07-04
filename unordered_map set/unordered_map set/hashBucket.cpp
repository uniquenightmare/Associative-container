#define  _CRT_SECURE_NO_WARNINGS 1
#include<vector>
#include<iostream>
#include<string>
using namespace std;
template<class K>
struct KeyofValue
{
	const K& operator()(const K&key)
	{
		return key;
	}
};
template<class V>
struct HashNode
{
	HashNode<V> * _next;
	V _data;
	HashNode(const V& data = V())
		:_next(nullptr)
		, _data(data)
	{}
};
template<class K, class V, class KeyofValue>
class HashBacket;
template<class K, class V, class KeyofValue>
struct HIterator
{
	typedef HashNode<V> Node;
	typedef Node* pNode;
	
	typedef HashBacket<K, V, KeyofValue> htable;
	typedef HIterator<K,V,KeyofValue> Self;
	pNode _node;
	htable *_ht;
	HIterator(pNode node,htable* ht)
		:_node(node)
		, _ht(ht)
	{}
	V& operator *()
	{
		return _node->_data;
	}
	V* operator ->()
	{
		return &_node->_data;
	}
	bool operator !=(const Self& it)
	{
		return _node != it._node;
	}
	Self& operator++()
	{
		if (_node->_next)
		{
			_node = _node->_next;
		}
		else
		{
			KeyofValue kov;
			int idx = kov(_node->_data) % _ht->_table.size();
			++idx;
			for (; idx < _ht->_table.size(); ++idx)
			{
				if (_ht->_table[idx])
				{
					_node = _ht->_table[idx];
					break;
				}
			}
			if (idx == _ht->_table.size())
				_node = nullptr;
		}
		return *this;
	}
};
template<class K,class V,class KeyofValue>
class HashBacket
{
public:
	typedef HashNode<V> Node;
	typedef Node* pNode;
	template<class K, class V, class KeyofValue>
	friend struct HIterator;
	typedef HIterator<K, V, KeyofValue> iterator;
	iterator begin()
	{
		for (size_t i = 0; i < _table.size(); i++)
		{
			if (_table[i])
			{
				return iterator(_table[i], this);
			}
		}
		return end();
	}
	iterator end()
	{
		return iterator(nullptr,this);
	}
	pair<iterator,bool> insert(const V&data)
	{
		check();
		KeyofValue kov;
		int idx = kov(data) % _table.size();
		pNode cur = _table[idx];
		while (cur)
		{
			if (kov(cur->_data) == kov(data))
				return make_pair(iterator(cur,this),false);
			cur = cur->_next;
		}
		cur = new Node(data);
		cur->_next = _table[idx];
		_table[idx] = cur;
		_size++;
		return make_pair(iterator(cur, this), true);
	}
	void check()
	{
		if (_size == _table.size())
		{
			size_t newC = _table.size() == 0 ? 10 : 2 * _table.size();
			vector<pNode> _newT;
			_newT.resize(newC);
			KeyofValue kov;
			for (auto &ch : _table)
			{
				pNode cur = ch;
				while (cur)
				{
					pNode next = cur->_next;
					int idx = kov(cur->_data) % _newT.size();
					cur->_next = _newT[idx];
					_newT[idx] = cur;
					cur = next;
				}
				ch = nullptr;
			}
			_table.swap(_newT);
		}
	}
private:
	vector<pNode> _table;
	size_t _size;
};
template<class K>
struct HashFun
{
	int operator()(const string&key)
	{
		return key;
	}
};
template<>
struct HashFun<string>
{
	int operator()(const string&key)
	{
		int hash = 0;
		for (auto &ch : key)
		{
			hash = hash * 131 + ch;
		}
		return hash;
	}
};
template<class K,class V>
class Unoreder_map
{
	struct MapKeyofValue
	{
		const K& operator()(const pair<K, V>& data)
		{
			return data.first;
		}
	};
public:
	typedef typename HashBacket<K, pair<K, V>, MapKeyofValue>::iterator iterator;
	iterator begin()
	{
		return _hb.begin();
	}
	iterator end()
	{
		return _hb.end();
	}
	bool insert(const pair<K, V>& data)
	{
		return _hb.insert(data);
	}
	V& operator[](const K& key)
	{
		pair<iterator, bool> ret = _hb.insert(make_pair(key, V()));
		return ret.first->second;
	}
private:
	HashBacket<K, pair<K, V>, MapKeyofValue> _hb;
};
template <class V>
class Unorder_set
{
	
	struct SetKeyofValue
	{
		const V& operator()(const V&data)
		{
			return data;
		}
	};
public:
	typedef typename HashBacket<V, V, SetKeyofValue>::iterator iterator;
	bool insert(const V&data)
	{
		return _hb.insert(data);
	}
	iterator begin()
	{
		return _hb.begin();
	}
	iterator end()
	{
		return _hb.end();
	}
private:
	HashBacket<V, V, SetKeyofValue> _hb;
};
void test()
{
	Unoreder_map<int, int> mp;
	mp[1] = 1;
	mp[2] = 2;
	mp[3] = 3;
	mp[4] = 4;
	Unoreder_map<int, int>::iterator it = mp.begin();
	for (; it != mp.end() ; it++)
	{
		cout << it->first << "-->" << it->second << endl;
	}
}

int main()
{
	test();
	system("pause");
	return 0;
}