#include<vector>
#include<list>
#include<string>
using namespace std;
template<typename HashedObj>
class HashTable
{
public:
	explicit HashTable(int size = 101;);
	bool contains(const HashedObj& x)const {
		const list<HashedObj>& whichList = theLists[myhash(x)];
		return find(whichList.begin(), whichList.end(), x) != whichList.end();
	}
	
	void makeEmpty() {
		for (int i = 0; i < theLists.size(); i++)theLists[i].clear();
	}
	void insert(const HashedObj& x) {
		list<HashedObj>& whichList = theLists[myhash(x)];
		if (find(whichList.begin(), whichList.end(), x) != whichList.end())
			return false;
		whichList.push_back(x);

		//Rehash; see Section 5.5
		if (++currentSize > theLists.size())rehash();
		return true;
	}
	void remove(const HashedObj& x) {
		list<HashedObj>& whichList = theLists[myhash(x)];
		list<HashedObj>::iterator itr = find(whichList.begin(), whichList.end(), x);

		if (itr == whichList.end())return false;

		whichList.erase(itr);
		--currentSize;
		return true;
	}

private:

	vector<list<HashedObj>>theLists;
	int currentSize;

	void rehash() {
		vector<list<HashedObj>> oldLists = theLists;

		//Create new double-sized, empty table
		theLists.resize(nextPrime(2 * theLists.size()));
		for (int j = 0; j < theLists.size(); j++)
			theLists[j].clear();

		//Copy table over
		currentSize = 0;
		for (int i = 0; i < oldLists.size(); i++)
		{
			list<HashedObj>::iterator itr = oldLists[i].begin();
			while (itr != oldLists[i].end())
				insert(*itr++);
		}

	}
	int myhash(const HashedObj& x)const
	{
		int hashVal = hash(x);
		hashVal %= theLists.size();
		if (hashVal < 0)hashVal += theLists.size();
		return hashVal;
	}
	
};

int hash(const string & key);
int hash(int key);

template<typename HashedObj>
int HashTable<HashedObj>::myhash(const HashedObj& x) const


//Example of an Employee class
class Employee
{
public:
	const string& getName()const { return name; }
	bool operator==(const Employee&rhs)const
	{
		return getName() == rhs.getName();
	}
	bool operator!=(const Employee &rhs)const
	{
		return !(*this == rhs);
	}

	//Addtional public members not shown

private:
	string name;
	double salary;
	int seniority;

	//Additional private members not shown

};

int hash(const Employee&item)
{
	return hash(item.getName());
}