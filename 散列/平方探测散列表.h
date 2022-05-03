#pragma once
#include<vector>
using namespace std;

/*
* 不使用链表的散列表
* 如果发生冲突，尝试另一个单元。
* 尝试单元按 h[0](x),h[1](x),h[2](x) ....依次尝试
* h[i](x) = ( hash(x) + f(i) ) mod TableSize 且 f(0) = 0
* 函数f是冲突解决函数
* 一般来说，对不使用分离链接法的散列表来说，其填装因子应该低于λ=0.5
* 我们称这样的表为 探测散列表 (probing hash tables)
* 下面考察三种常见的解决冲突方法
*/

/* 线性探测 */
/*
* 在线性探测中，函数f是i的线性函数，一般情况下f(i) = i.
* 在多次冲突分配之后，即时表相对较空，也会形成 一次聚集 (primary clustering)
* 此后，散列到区块中的任何键都需要多次试选单元才能够解决冲突，然后该键才被添加到相应区块中。
* 
* 特性：
* 如果表将有多于一半被填满的话，那么线性探测就不是个好办法。
* 然而，如果λ=0.5，那么插入操作平均只需要2.5次探测，并且对于成功查找的平均只需要1.5次探测
*/


/* 平方探测 */
/*
* 平方探测的冲突函数为二次函数，流行选择是 f(i) = i^2
* 虽然 平方探测 排除了 一次聚集，但是散列到同一位置上的元素将探测相同的备选单元，
* 这成为二次聚集。模拟结果指出，对每次查找，它一般要引起另外少于一半的探测。
* 
* 特性：
* 如果使用平方探测，且表的大小是素数，那么当表至少有一半是空的时候，总能够插入一个新元素。
* 如果哪怕表有比一半多一个的位置被填满，那么插入都有可能失败（即时这种可能性很小）
* 另外，表的大小是素数也非常重要，如果表的大小不是素数，则备选单元个数可能会锐减
*/

/* 双散列(double hashing) */
/*
* 对于双散列，一种流行的选择是f(i) = i*hash[2](x)
* 这个公式的意思是，将第二个散列函数应用到x 并在距离hash[2](x),2hash[2](x) ...等处探测
* hash[2](x)选择得不好将会非常糟糕。
* 另外，保证所有单元都能被探测到也很重要，而且表的大小要是素数。
* 诸如 hash[2](x) = R - (x mod R)这样的函数将起到良好的最用，其中R是小于TableSize的素数
* 
* 特性：
* 如果 双散列正确实现，模拟表明：预期的探测次数几乎和随机冲突解决方法的情形相同
* 这使得双散列在理论上很有吸引力。
* 不过，平方探测不需要使用第二个散列函数，从而在实践中可能更简单并且更快。
* 当键为字符串时，尤其如此，因为其散列函数的计算很耗时。
*/

/*
* 再散列 可以用平方探测以多种方法实现。
* 一种做法是只要表满到一半就再散列。
* 另一种极端方法是只有当插入失败时才再散列
* 第三种方法即途中策略：当表达到某一个填装因子时进行再散列。
* 由于随着填装因子的增加，表的性能的确在下降，因此，以最好的截止点实现第三种策略
* 可能是最好的策略
*/

template<typename HashedObj>
class HashTable
{
public:
	explicit HashTable(int size = 101):array(nextPrime(size))
	{	makeEmpty();}

	bool contains(const HashedObj& x)const {
		return isActive(findPos(x));
	}
	

	void makeEmpty()
	{
		currentSize = 0;
		for (int i = 0; i < array.size(); i++)array[i].info = EMPTY;
	}
	bool insert(const HashedObj& x);
	bool remove(const HashedObj& x);

	enum EntryType(ACTIVE, EMPTY, DELETED);

private:
	struct HashEntry
	{
		HashedObj element;
		EntryType info;

		HashEntry(const HashedObj & e = HashedObj(),EntryType i = EMPTY)
			:element(e),info(i){}
	};

	vector<HashEntry> array;

	int findPos(const HashedObj& x)const
	{
		int offset = 1;
		int currentPos = myhash(x);

		while (array[currentPos].info != EMPTY &&
			array[currentPos].element != x)
		{
			currentPos += offset;  //Compute ith probe
			offset += 2;
			if (currentPos >= array.size())
				currentPos -= array.size();
		}
	}
	bool isActive(int currentPos)const {
		return array[currentPos].info == ACTIVE;
	}
	void rehash() 
	{
		vector<HashEntry> oldArray = array;

		//Create new double-sized, empty table
		array.resize(nextPrime(2 * oldArray.size()));
	}

	int myhash(const HashedObj& x)const;
};