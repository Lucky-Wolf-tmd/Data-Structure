//利用树求解四皇后问题所有合法布局
/*
* 这是一棵四叉树（每个非终端节点度都为4），树中每个节点表示一个局部布局或者完整布局
* 根节点表示棋盘的初始状态：棋盘上无任何棋子
* 每个皇后都有四个可选位置，但在任何时刻，棋盘的合法布局必须满足一下三个约束
* 1.任何两个棋子都不占据棋盘的同一行
* 2.任何两个棋子都不占据棋盘的同一列
* 3.任何两个棋子都不占据棋盘的同一对角线
* 
* 求所有合法布局的过程即为在上述约束条件下，先序遍历状态树的过程。
* 遍历中访问节点的操作为：判别棋盘上是否已经得到一个完整布局（即棋盘上是否已经摆上4个棋子）
* 若是，则输出该布局；否则，依次先序遍历满足约束条件的各棵子树，
* 首先判断该子树的布局是否合法
* 若合法，则先序遍历该子树；否则剪去该子树分支
*/

#include<iostream>
using namespace std;
const int QueenNum = 8;

class Backtracking
{
private:
	int* C;//存放棋子位置的数组
	int n;//n*n的棋盘
	int count;//解的个数
public:
	Backtracking() { n = QueenNum; C = new int[n]; count = 0; }
	void Trial(int i);//trial试验
	void Print();//输出棋盘当前的布局
	int Check(int i);//检查当前布局是否合法
};

void Backtracking::Trial(int i)
{
	if (i == n)
		Print();
	else
	{
		for (int j = 0; j < n; j++)//先序遍历状态树,从空集开始遍历
		{
			C[i] = j;//C[i]的可能值为 0，1，2，3
			if (Check(i))//当前布局合法
				Trial(i + 1);
		}
	}
}

int Backtracking::Check(int i)
{
	for (int j = 0; j < i; j++)
	{
		if (C[i] == C[j] || i - C[i] == j - C[j] || i + C[i] == j + C[j])
			return 0;
	}
	return 1;
}

void Backtracking::Print()
{
	cout << "解" << ++count << endl;
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (j == C[i])//j是列
				cout << "*";
			else
				cout << "-";
		}
		cout << endl;//所以i是行
	}
}

int main()
{
	Backtracking T;
	T.Trial(0);
	return 0;
}
