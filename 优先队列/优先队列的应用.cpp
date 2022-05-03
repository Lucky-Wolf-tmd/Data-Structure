#include"BinaryHeap.h"

/*
* 一、选择问题(selection problem)
* 输入N个元素以及一个整数k，输出第k个最大元素
*/

/*
* 1.算法6A
* 将N个元素 读入一个数组，对该数组buildHeap，然后执行k次deleteMin/deleteMax
* 最后取堆顶，得到目标元素。
* buildHeap最坏情形是O(N)时间，每次deleteMin是O(logN)时间，一共有k次deleteMin
* 
* 总运行时间：O(N + k logN)
* 如果k = O(N/logN) 运行时间取决于buildHeap操作，即O(N)
* 对于k较大的情况，运行时间为O(klogN)
* 如果k=向上取整（N/2)，那么运行时间则为Θ(NlogN)
* 
* 注意：令k==N，运行程序，并在元素离开堆时记录下这些元素的值，
* 那么实际上就是对输入文件以时间O(NlogN)进行了排序。
* 这就是堆排序(Heapsort)的思想
*/

/*
* 2.算法6B
* 读入前k个元素后，维持k个最大元素集合S。
* 当再读入一个新元素时，与第k个最大值比较，
* 若新元素更大，则用新元素替换S中的S[k]
* 此时S将有一个新的最小元素。
* 当输入完成后，我们找到S中最小元素，将其返回，得到的就是该问题的答案。
* buildHeap将前k个元素以总时间O(k)入堆。
* 处理其余每个元素时间为O(1)，总时间为O(N-k)
* 还要加上O(logk)的时间用来检测元素是否放入S，并在需要时删除S[k]并插入新元素。
* 
* 因此总时间为：O(k+(N-k)logk) = O(N logk).
* 该算法找出中位数的时间界为Θ(NlogN)
*/

//有证据显示，实践中4堆胜过二叉堆

/*
* 除了不能执行find操作外，堆的实现的最明显的缺点是：将两个堆合二为一是很困难的操作。
* 这个附加操作称为合并(merge)。
* 有许多实现堆的方法可以使一次merge操作的运行时间是O(logN）
* 
* 下面讨论三种复杂程度不一的Data Structure。他们都有效的支持merge操作
*/

/* 左式堆 */
/* 
* 左式堆(leftist heap)像二叉堆那样既有结构性质，又有堆序性质。
* 不仅如此，左式堆也是二叉树。
* 左式堆和二叉堆唯一的区别是：左式堆不是理想平衡的（perfectly balanced），
* 且事实上是趋于非常不平衡的。
*/

/*
* 我们把任一结点X的 零路径长(null path length) npl(X)定义为从X到一个不具有两个儿子的结点的最短路径的长
* 因此，具有0个或1个儿子的结点的npl为0，而npl(NULL) = -1.
* 
* 左式堆性质：对于每一结点X，左儿子的npl至少与右儿子的npl一样大
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