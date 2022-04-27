#include<vector>
#include<iostream>
using namespace std;
namespace LOG {
	/*
	* Performs the standard binary search using two comparisons per level.
	* Returns index where item is found or -1 if not found.
	*/
	//�����㷨 ����������ֵѰ���±�
	template <typename Comparable>
	int binarySearch(const vector<Comparable>& a, const Comparable& x)
	{
		int low = 0, high = a.size() - 1;
		while (low <= high)//ѭ������
		{
			int mid = (low + high) / 2;
			if (a[mid] < x)
				low = mid + 1;
			else if (a[mid] > x)
				high = mid - 1;
			else 
				return mid; //Found
		}
		return -1;//-1 means not found
	}

	//ŷ������㷨 �����������
	long gcd(long m, long n)
	{
		while (n != 0)
		{
			long rem = m % n;
			m = n;
			n = rem;
		}
		return m;
	}

	//��Ч�����㣨�ݹ���֣�
	long pow(long x, int n)
	{
		if (n == 0)
			return 1;
		if (n % 2 == 0)
			return pow(x * x, n / 2);
		else
			return pow(x * x, n / 2) * x;
	}

	//��С��n�ķ�Χ�ڣ�������������ȵ�������Ϊ�����ĸ���
	double probRelPrime(int n)
	{
		int rel = 0, tot = 0;
		for(int i =1;i<n;i++)
			for (int j = i + 1; j <=n; j++)
			{
				tot++;
				if (gcd(i, j) == 1)
					rel++;
			}
		return (double)rel / (double)tot;
	}
}
int main()
{
	vector<int>a;
	for (int i = 0; i < 100; i++)
		a.push_back(i);
	int sixty_three = LOG::binarySearch(a, 63);
	int nine = LOG::gcd(81, sixty_three);
	int twonine = pow(2, nine);
	if (twonine != 512)abort();
	double n = LOG::probRelPrime(4);
	cout << n << endl;

	return 0;
}