#include<vector>
#include<functional>
#include<algorithm>
#include<numeric>
#include<iostream>
#include<time.h>
using namespace std;
namespace algorithm {
	/*
	* Cubic maximum conitguous subsequence sum algorithm.
	*/
	//穷举法 for循环三连套， 别跟我讲什么时间复杂度，for循环套娃就完事了！
	//把所有的子串全部取出来了一遍，
	int maxSubSum1(const vector<int>& a) {
		int maxSum = 0;
		for(int i =0;i<a.size();i++)
			for (int j = i; j < a.size(); j++)
			{
				int thisSum = 0;
				for (int k = i; k <= j; k++) //用累加法求子串和
					thisSum += a[k];
				if (thisSum > maxSum)
					maxSum = thisSum;
			}
		return maxSum;
	}

	/*
	* Quadratic maximum contiguous subsequence sum algorithm
	*/
	int maxSubSum2(const vector<int>& a)
	{
		int maxSum = 0;
		for (int i = 0; i < a.size(); i++)
		{
			int thisSum = 0;//注意thisSum声明的位置，它在第二个循环外面
			for (int j = i; j < a.size(); j++)
			{
				thisSum += a[j];//子串由第二个循环来计算，每次循环只需加入当前元素
				if (thisSum > maxSum)
					maxSum = thisSum;
			}
		}
		return maxSum;
	}

	
	/*
	* Recursive maximum contiguous subsequence sum algorithm.
	* Finds maximum sum in subarray spanning a [left..right].
	* Does not attempt to maintain actual best sequence.
	*/
	int max2(int a, int b) { return a > b ? a : b; }
	int max3(int a, int b, int c) { return max2(max2(a, b), c); }
	int maxSumRec(const vector<int>& a, int left, int right)
	{
		if (left == right)   //Base case
		{
			if (a[left] > 0)
				return a[left];
			else
				return 0;
		}

		int center = (left + right) / 2;
		int maxLeftSum = maxSumRec(a, left, center);
		int maxRightSum = maxSumRec(a, center + 1, right);
		
		int maxLeftBorderSum = 0, leftBorderSum = 0;
		for (int i = center; i >= left; i--)
		{
			leftBorderSum += a[i];
			if (leftBorderSum > maxLeftBorderSum)
				maxLeftBorderSum = leftBorderSum;
		}

		int maxRightBorderSum = 0, rightBorderSum = 0;
		for (int i = center+1; i <=right; i++)
		{
			rightBorderSum += a[i];
			if (rightBorderSum > maxRightBorderSum)
				maxRightBorderSum = rightBorderSum;
		}

		return max3(maxLeftSum, maxRightSum,
			maxLeftBorderSum + maxRightBorderSum);
	}
	int maxSubSum3(const vector<int>& a) {
		return maxSumRec(a, 0, a.size() - 1);
	}

	/*
	* Linear-time maximum contiguous subsequence sum algorithm.
	*/
	int maxSubSum4(const vector<int>& a)
	{
		int maxSum = 0, thisSum = 0;
		for (int j = 0; j < a.size(); j++)
		{
			thisSum += a[j];
			if (thisSum > maxSum)
				maxSum = thisSum;
			else if (thisSum < 0)
				thisSum = 0;
		}
		return maxSum;
	}
}//algorithm

int main()
{
	clock_t start, end;
	start = clock();
	vector<int>a;
	for (int i = 0; i <1500; i++)
		a.push_back(i);
	for (int i = 0; i < 4; i++)
	{
		cout << "algorithm " << i+1 << " time use: \t";
		start = clock();
		switch (i)
		{
		case 0:algorithm::maxSubSum1(a); break;//33602ms
		case 1:algorithm::maxSubSum2(a); break;//  130ms
		case 2:algorithm::maxSubSum3(a); break;//    2ms
		case 3:algorithm::maxSubSum4(a); break;//    0ms
		default:break;
		}
		end = clock();
		double T = (double)(end - start);
		cout << T <<"ms"<< endl;
	}
	

	return 0;
}