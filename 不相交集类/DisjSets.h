#pragma once
#include<vector>
using namespace std;
// 不相交集类架构(Disjoint Sets)
class DisjSets
{
public:
	explicit DisjSets(int numElements);

	int find(int x)const;
	int find(int x);
	void unionSets(int root1, int root2);

private:
	vector<int>s;
};

/*
* Construct the disjoint sets object.
* numElements is the initial number of disjoint sets.
*/
DisjSets::DisjSets(int numElements) :s(numElements) {
	for (int i = 0; i < s.size(); i++)s[i] = -1;
}

/*
* Union two disjoint sets.
* For simplicity, we assume root1 and root2 are distinct
* and represent set names.
* root 1 is the root of set 1.
* root 2 is the root of set 2.
*/
void DisjSets::unionSets(int root1, int root2)
{
	s[root2] = root1;  //不是最好的方法
}

/*
* Perform a find.
* Error checks omitted again for simplicity.
* Return the set containing x.
*/
int DisjSets::find(int x)const {
	if (s[x] < 0)return x;
	else return find(s[x]);
}

/*
* Union two disjoint sets.
* For simplicity, we assume root1 and root2 are distince.
* and represent set names.
* root1 is the root of set 1.
* root2 is the root of set 2.
*/
void DisjSets::unionSets(int root1, int root2)
{
	if (s[root2] < s[root1])  // root2 is deeper.
		s[root1] = root2;     // Make root2 new root
	else
	{
		if (s[root1] == s[root2])
			s[root1]--;      // Update height if same.
		s[root2] = root1;    // Make root1 new root.
	}
}

/*
* Perform a find with path compression.
* Error checks omitted again for simplicity.
* Return the set containing x.
*/
int DisjSets::find(int x) {
	if (s[x] < 0) return x;
	else return s[x] = find(s[x]);
}