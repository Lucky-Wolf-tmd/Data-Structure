
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include<functional>
using namespace std;

struct Container {
	int num;
	string name;
	Container(int n,const string& str):num(n),name(str){}
	const Container& operator=(const Container& rhs) {
		if (this == &rhs)return *this;
		this->name = rhs.name;
		this->num = rhs.num;
		return *this;
	}

	bool operator<(const Container& rhs) {
		return this->num < rhs.num;
	}
};

void Load(vector<Container>& vec,const string & str) {
	ifstream ifs(str, ios::in);
	string data;
	cout << "Loading...." << endl;
	while (ifs >> data) {
		int pos = -1;
		int start = 0;
		while (1) {
			pos = data.find(",", start);
			if (pos == -1)break;
			string tmp = data.substr(start, pos - start);
			int flag = 0;
			for (auto x = vec.begin(); x != vec.end(); x++)
			{
				if (x->name == tmp) {
					x->num++;
					flag = 1;
				}
			}
			if (!flag) {
				Container tmpC(1, tmp);
				vec.push_back(tmpC);
			}
			start = pos + 1;
		}
	}
	ifs.close();
}
void Sort(vector<Container>& vec) {
	int j;
	for (int p = 1; p < vec.size(); p++)
	{
		Container tmp = vec[p];
		for (j = p; j > 0 && tmp.num > vec[j - 1].num; j--)
			vec[j] = vec[j - 1];
		vec[j] = tmp;
	}
}
void Print(const vector<Container>& vec) {
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i].name << "\t\t" << vec[i].num << endl;
	}
}
void Print(const vector<int>& vec) {
	for (int i = 0; i < vec.size(); i++)
	{
		cout <<"["<< vec[i] << "]";
	}
	cout << endl;
}

void print(const Container& a) {
	cout << "\t" << a.name << "\t" << a.num << endl;
}

template<typename Comparable>
void shellsort(vector<Comparable>& a) {
	Print(a);
	for (int gap = a.size() / 2; gap > 0; gap /= 2) {
		cout << endl;
		cout << "Gap == " << gap << endl;
		for (int i = gap; i < a.size(); i++)
		{

			
			
			Comparable tmp = a[i];
			int j = i;
			for (; j >= gap && tmp < a[j - gap]; j -= gap) {
				cout << "\t"<<a[j] << "-->";
				a[j] = a[j - gap];
				cout << a[j] << endl;
			}

			a[j] = tmp;

		}
		Print(a);
	}
}

/*
* Internal method for heapsort
* i is the index of an item in the heap.
* Returns the index of the left child.
*/
inline int leftChild(int i) { return 2 * i + 1; }

/*
* Internal method for heapsort that is used in deleteMax and buildHeap.
* i is the position from which to percolate down.
* n is the logical size of the binary heap.
*/
template<typename Comparable>
void percDown(vector < Comparable>& a, int i, int n) {
	int child;
	Comparable tmp;
	for (tmp = a[i]; leftChild(i) < n; i = child)
	{
		child = leftChild(i);
		if (child != n - 1 && a[child] < a[child + 1])         child++;
		if (tmp < a[child])                            a[i] = a[child];
		else                                                     break;
	}
	a[i] = tmp;
}

/*
* Standard heapsort.
*/
template<typename Comparable>
void heapsort(vector<Comparable>& a)
{

	/* buildHeap */
	for(int i = a.size() / 2; i >= 0; i--) {
		percDown(a, i, a.size());
	}
	Print(a);

	/* deleteMax */
	for(int j = a.size() - 1; j > 0; j--)
	{
		swap(a[0], a[j]);
		percDown(a, 0, j);
		Print(a);
	}

}

// 计数排序
template<typename Comparable>
 vector<Comparable> CountSort(vector<Comparable>& vecRaw)
{
	// 确保待排序容器非空
	if (vecRaw.empty())
		return {};
	vector<Comparable> vecCount(11, 0);
	vector<Comparable> vecObj(vecRaw.size());

	// 统计每个键值出现的次数
	for (int i = 0; i < vecRaw.size(); i++)
		vecCount[vecRaw[i]]++;
	
	// 后面的键值出现的位置为前面所有键值出现的次数之和
	for (int i = 1; i < vecCount.size(); i++)
		vecCount[i] += vecCount[i - 1];

	// 将键值放到目标位置
	for (int i = vecRaw.size(); i > 0; i--)	// 此处逆序是为了保持相同键值的稳定性
		vecObj[--vecCount[vecRaw[i - 1]]] = vecRaw[i - 1];

	return vecObj;
		
	
}
#if 0
int main()
{

	//vector<Container> C;
	//Load(C, "文本.txt");
	//Sort(C);
	vector<int> c;
	c.push_back(10);
	c.push_back(6);
	c.push_back(8);
	c.push_back(1);
	c.push_back(7);
	c.push_back(3);
	c.push_back(2);
	c.push_back(5);
	c.push_back(4);
	c.push_back(9);
	Print(CountSort(c));

	return 0;
}
#endif