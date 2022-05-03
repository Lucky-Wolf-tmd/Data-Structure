#include"BinaryHeap.h"

/*
* һ��ѡ������(selection problem)
* ����N��Ԫ���Լ�һ������k�������k�����Ԫ��
*/

/*
* 1.�㷨6A
* ��N��Ԫ�� ����һ�����飬�Ը�����buildHeap��Ȼ��ִ��k��deleteMin/deleteMax
* ���ȡ�Ѷ����õ�Ŀ��Ԫ�ء�
* buildHeap�������O(N)ʱ�䣬ÿ��deleteMin��O(logN)ʱ�䣬һ����k��deleteMin
* 
* ������ʱ�䣺O(N + k logN)
* ���k = O(N/logN) ����ʱ��ȡ����buildHeap��������O(N)
* ����k�ϴ�����������ʱ��ΪO(klogN)
* ���k=����ȡ����N/2)����ô����ʱ����Ϊ��(NlogN)
* 
* ע�⣺��k==N�����г��򣬲���Ԫ���뿪��ʱ��¼����ЩԪ�ص�ֵ��
* ��ôʵ���Ͼ��Ƕ������ļ���ʱ��O(NlogN)����������
* ����Ƕ�����(Heapsort)��˼��
*/

/*
* 2.�㷨6B
* ����ǰk��Ԫ�غ�ά��k�����Ԫ�ؼ���S��
* ���ٶ���һ����Ԫ��ʱ�����k�����ֵ�Ƚϣ�
* ����Ԫ�ظ���������Ԫ���滻S�е�S[k]
* ��ʱS����һ���µ���СԪ�ء�
* ��������ɺ������ҵ�S����СԪ�أ����䷵�أ��õ��ľ��Ǹ�����Ĵ𰸡�
* buildHeap��ǰk��Ԫ������ʱ��O(k)��ѡ�
* ��������ÿ��Ԫ��ʱ��ΪO(1)����ʱ��ΪO(N-k)
* ��Ҫ����O(logk)��ʱ���������Ԫ���Ƿ����S��������Ҫʱɾ��S[k]��������Ԫ�ء�
* 
* �����ʱ��Ϊ��O(k+(N-k)logk) = O(N logk).
* ���㷨�ҳ���λ����ʱ���Ϊ��(NlogN)
*/

//��֤����ʾ��ʵ����4��ʤ�������

/*
* ���˲���ִ��find�����⣬�ѵ�ʵ�ֵ������Ե�ȱ���ǣ��������Ѻ϶�Ϊһ�Ǻ����ѵĲ�����
* ������Ӳ�����Ϊ�ϲ�(merge)��
* �����ʵ�ֶѵķ�������ʹһ��merge����������ʱ����O(logN��
* 
* �����������ָ��ӳ̶Ȳ�һ��Data Structure�����Ƕ���Ч��֧��merge����
*/

/* ��ʽ�� */
/* 
* ��ʽ��(leftist heap)�������������нṹ���ʣ����ж������ʡ�
* ������ˣ���ʽ��Ҳ�Ƕ�������
* ��ʽ�ѺͶ����Ψһ�������ǣ���ʽ�Ѳ�������ƽ��ģ�perfectly balanced����
* ����ʵ�������ڷǳ���ƽ��ġ�
*/

/*
* ���ǰ���һ���X�� ��·����(null path length) npl(X)����Ϊ��X��һ���������������ӵĽ������·���ĳ�
* ��ˣ�����0����1�����ӵĽ���nplΪ0����npl(NULL) = -1.
* 
* ��ʽ�����ʣ�����ÿһ���X������ӵ�npl�������Ҷ��ӵ�nplһ����
*/

#include<vector>
#include<queue>//priority_queue
#include<functional>//greater<typename>
#include<string>
#include<iostream>
using namespace std;

// Empty the priority queue and print its contents.
template<typename PriorityQueue>
void dumpContents(const string& msg, PriorityQueue& pq)
{
	cout << msg << ":" << endl;
	while (!pq.empty())
	{
		cout << pq.top() << endl;
		pq.pop();
	}
}

int main()
{
	priority_queue<int>  maxPQ;
	priority_queue<int, vector<int>, greater<int>>minPQ;

	minPQ.push(4); minPQ.push(3); minPQ.push(5);
	maxPQ.push(4); maxPQ.push(3); maxPQ.push(5);

	dumpContents("minPQ", minPQ);
	dumpContents("maxPQ", maxPQ);
	return 0;
}