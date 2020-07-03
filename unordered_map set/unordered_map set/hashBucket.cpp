#define  _CRT_SECURE_NO_WARNINGS 1
#include<vector>
#include<iostream>
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
	typedef HIterator<V> Self;
	pNode _node;
	htable *_ht
	HIterator(pNode node,htable* ht)
		:_node(node)
		, _ht(ht)
	{}
	V& operator *()
	{
		return _node->_data;
	}
	V& operator ->()
	{
		return *_node->_data;
	}
	bool operator !=(const Self& it)
	{
		return _node != it._node;
	}
	Selft& operator++()
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
	friend struct HIterator
	bool insert(const V&data)
	{
		check();
		KeyofValue kov;
		int idx = kov(data) % _table.size();
		pNode cur = _table[idx];
		while (cur)
		{
			if (kov(cur->_data) == kov(data))
				return false;
			cur = cur->_next;
		}
		cur = new Node(data);
		cur->_next = _table[idx];
		_table[idx] = cur;
		_size++;
		return true;
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
template<class K,class V>
class Unoreder_map
{
	struct MayKeyofValue
	{
		const K& operator()(const pair<K, V>& data)
		{
			return data.first;
		}
	};
public:
	bool insert(const pair<K, V>& data)
	{
		return _hb.insert(data);
	}
private:
	HashBacket<K, pair<K, V>, MapKeyofValue> _hb;
};
void test()
{
	HashBacket<int, int, KeyofValue<int>> hb;
	hb.insert(21);
	hb.insert(48);
	hb.insert(36);
	hb.insert(43);
	hb.insert(5);
	hb.insert(61);
	hb.insert(78);
	hb.insert(15);
	hb.insert(6);
	hb.insert(23);
	hb.insert(51);
	hb.insert(52);
	hb.insert(53);
	hb.insert(54);
	hb.insert(55);
	hb.insert(56);



}

int main()
{
	test();
	return 0;
}