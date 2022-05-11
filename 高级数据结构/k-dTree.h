#pragma once
/*
* 二维查找树（two-dimensional search tree)具有简单的性质：
* 在奇数层上的分支按照第一个键进行，在偶数层上的分支按照第二个键进行
*/
/*
* 2-d树的插入操作是二叉查找树插入操作的平凡扩展：
* 在沿树下行时，我们需要保留当前的层
*/

public:
	void insert(const vector<Comparable>& x) {
		insert(x, root, 0);
	}
private:
	void insert(const vector < Comparable& x, kdNode*& t, int level) {
		if (t == nullptr)
			t = new kdNode(x);
		else if (x[level] < t->data[level])
			insert(x, t->left, 1 - level);
		else
			insert(x, t->right, 1 - level);
	}

public:
	/*
	* Print items satisfying
	* low[0]<=x[0]<=high[0] and
	* low[1]<=x[1]<=high[1]
	*/
	void printRange(const vector<Comparable>& low,
		const vector<Comparable>& high)const {
		printRange(low, high, root, 0);
	}
private:
	void printRange(const vector<Comparable>& low,
		const vector<Comparable>& high,
		kdNode* t, int level)const {
		if (t != nullptr) {
			if (low[0] <= t->data[0] && high[0] >= t->data[0] &&
				low[1] <= t->data[1] && hight[1] >= t->data[1])
				cout << "(" << t->data[0] << ","
				<< t->data[1] << ")" << endl;
			if (low[level] <= t->data[level])
				printRange(low, high, t->left, 1 - level);
			if (high[level] >= t->data[level])
				printRange(low, high, t->right, 1 - level);
		}
	}