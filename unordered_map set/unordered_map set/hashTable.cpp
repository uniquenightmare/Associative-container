#define  _CRT_SECURE_NO_WARNINGS 1
#include<vector>
#include<iostream>
using namespace std;
enum state
{
	EXIST,
	DELETE,
	EMPTY
};

template<class K,class V>
struct Node
{
	pair<K, V> _value;
	state _state;
};
template<class K,class V>
class HashTable
{
public:
	typedef Node<K, V> Node;
	HashTable(size_t N = 10)
	{
		_table.resize(N);
		for (auto &ch : _table)
		{
			ch._state = EMPTY;
		}
		_size = 0;
	}
	bool insert(const pair<K,V>& data)
	{
		check();
		int idx = data.first % _table.size();
		while (_table[idx]._state == EXIST)
		{
			if (_table[idx]._value.first == data.first)
				return false;
			idx++;
			if (idx == _table.size())
				idx = 0;
		}
		_table[idx]._value = data;
		_table[idx]._state = EXIST;
		++_size;
		return true;
	}
	void check()
	{
		if (_size * 1.0 / _table.size() >= 0.7)
		{
			int newc = _table.size() * 2;
			HashTable<K, V> newHt(newc);
			for (auto &ch : _table)
			{
				if (ch._state == EXIST)
				{
					newHt.insert(ch._value);
				}	
			}
			_table.swap(newHt._table);
		}
	}
	Node* find(const K& key)
	{
		int idx = key % _table.size();
		while (_table[idx]._state != EMPTY)
		{
			if (_table[idx]._state == EXIST&&_table[idx]._value.first == key)
			{
				return &_table[idx];
			}
			++idx;
			if (idx == _table.size())
			{
				idx = 0;
			}
		}
		return nullptr;
	}
	bool erase(const K&key)
	{
		Node* node = find(key);
		if (node)
		{
			node->_state = DELETE;
			--_size;
			return true;
		}
		return false;
	}
private:
	vector<Node> _table;
	size_t _size;
};
void test()
{
	HashTable<int, int> ht;
	ht.insert(make_pair(1, 1));
	ht.insert(make_pair(18, 18));
	ht.insert(make_pair(23, 23));
	ht.insert(make_pair(4, 4));
	ht.insert(make_pair(54, 54));
	cout << ht.erase(18) << endl;
	cout << ht.erase(17) << endl;

}
int main()
{
	test();
	system("pause");
	return 0;
}