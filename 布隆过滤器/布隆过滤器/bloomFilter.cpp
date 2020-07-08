#define  _CRT_SECURE_NO_WARNINGS 1
#include<vector>
#include<iostream>
#include<string>
using namespace std;
class BitMap
{
public:
	BitMap(size_t range)
	{
		vec.resize((range >> 5) + 1);
	}
	void set(int data)
	{
		int idx = data >> 5;
		int bitidx = data % 32;
		vec[idx] |= 1 << bitidx;
	}
	bool test(int data)
	{
		int idx = data >> 5;
		int bitidx = data % 32;
		return (vec[idx] >> bitidx) & 1;
	}
	void reset(int data)
	{
		int idx = data >> 5;
		int bitidx = data % 32;
		vec[idx] &= ~(1 << bitidx);
	}
private:
	vector<int> vec;
};
template<class K,class HF1.class HF2,class HF3>
class BloomFilter
{
public:
	BloomFilter(size_t range)
		:_bm(range * 5)
		,bitsize(range * 5)
	{}
	void set(const K& key)
	{
		size_t idx1 = HF1()(key) % bitsize;
		size_t idx2 = HF2()(key) % bitsize;
		size_t idx3 = HF3()(key) % bitsize;
		_bm.set(idx1);
		_bm.set(idx2);
		_bm.set(idx3);
	}
	void test()
	{
		size_t idx1 = HF1()(key) % bitsize;
		size_t idx2 = HF2()(key) % bitsize;
		size_t idx3 = HF3()(key) % bitsize;
		if (!_bm.test(idx1))
		{
			return false;
		}
		if (!_bm.test(idx2))
		{
			return false;
		}
		if (!_bm.test(idx3))
		{
			return false;
		}
		return true;
	}
private:
	BitMap _bm;
	size_t bitsize;
};
struct HF1
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		for (auto &ch : str)
		{
			hash = hash * 131 + ch;
		}
		return hash;
	}
};
struct HF2
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		for (auto &ch : str)
		{
			hash = hash * 65599 + ch;
		}
		return hash;
	}
};
struct HF3
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		size_t magic = 63689;
		for (auto &ch : str)
		{
			hash = hash * magic + ch;
			magic *= 378551;
		}
		return hash;
	}
};