#pragma once
#include<functional>//less<>、greater<>
#include<vector>
#include<algorithm>
using namespace std;

/*
* Bubble Sort
* 算法思想：
*    比较相邻的元素。如果第一个比第二个大，就交换他们两个。
*    对每一对相邻元素作同样的工作，从开始第一对到结尾的最后一对。这步做完后，最后的元素会是最大的数。
*    针对所有的元素重复以上的步骤，除了最后一个。
*    持续每次对越来越少的元素重复上面的步骤，直到没有任何一对数字需要比较。
*/
template<typename Comparable>
void BubbleSort(vector<Comparable>&a)
{
	for (int i = 0; i <a.size(); ++i)
	{
		for (int j = 0; j < a.size() - i - 1; ++j)
		{
			if (a[j] > a[j + 1])
			{
				Comparable tmp = a[j];  //交换
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
		}
	}
}

/*
* Selection Sort
* 算法思想：
*    在未排序序列中找到最小（大）元素，存放到排序序列的起始位置
*    从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾
*    以此类推，直到所有元素均排序完毕
*/
template<typename Comparable>
void SelectionSort(vector<Comparable>& a) {
	int minIndex;
	Comparable temp;
	for (int i = 0; i < a.size()-1; i++) {
		minIndex = i;
		for (int j = i + 1; j < a.size(); j++) {
			if (a[j] < a[minIndex]) minIndex = j;       // 寻找最小的数
		}
		temp = a[i];
		a[i] = a[minIndex];
		a[minIndex] = temp;
	}
}

/*
* 计数排序
* 计数排序统计小于等于该元素值的元素的个数i，于是该元素就放在目标数组的索引i位（i≥0）。

    计数排序基于一个假设，待排序数列的所有数均为整数，且出现在（0，k）的区间之内。
    如果 k（待排数组的最大值） 过大则会引起较大的空间复杂度，一般是用来排序 0 到 100 之间的数字的最好的算法，但是它不适合按字母顺序排序人名。
    计数排序不是比较排序，排序的速度快于任何比较排序算法。

算法思想：

    找出待排序的数组中最大和最小的元素；
    统计数组中每个值为 i 的元素出现的次数，存入数组 C 的第 i 项；
    对所有的计数累加（从 C 中的第一个元素开始，每一项和前一项相加）；
    向填充目标数组：将每个元素 i 放在新数组的第 C[i] 项，每放一个元素就将 C[i] 减去 1；
*/

// 计数排序
template<typename Comparable>
void CountSort(vector<Comparable>& vecRaw)
{
	// 确保待排序容器非空
	if (vecRaw.empty())
		return;
	vector<Comparable> vecCount;
	// 统计每个键值出现的次数
	for (int i = 0; i < vecRaw.size(); i++)
		vecCount[vecRaw[i]]++;
	/*
	// 后面的键值出现的位置为前面所有键值出现的次数之和
	for (int i = 1; i < vecCountLength; i++)
		vecCount[i] += vecCount[i - 1];

	// 将键值放到目标位置
	for (int i = vecRaw.size(); i > 0; i--)	// 此处逆序是为了保持相同键值的稳定性
		vecObj[--vecCount[vecRaw[i - 1]]] = vecRaw[i - 1];
		*/
	vecRaw.clear();
	for (int i = 0; i < vecCount.size(); i++)
	{
		for (; vecCount[i] > 0; vecCount[i]--) {
			vecRaw.push_back(i);
		}
	}
}

/*
* Simple insertion sort
*/
template<typename Comparable>
void insertionSort(vector<Comparable>& a)
{
	int j;
	for (int p = 1; p < a.size(); p++)
	{
		Comparable tmp = a[p];
		for (j = p; j > 0 && tmp < a[j - 1]; j--)
			a[j] = a[j - 1];
		a[j] = tmp;
	}
}
/*
* 在STL中，排序历程不采用具有可比性的项所组成的数组作为单一的参数，
* 而是接收一对迭代器来代表在某范围内的起始和终止标志。
* 一个双参数排序例程使用一对迭代器，并假设所有项都是可排序的。
* 而一个三参数排序例程有一个函数对象作为第三个参数。
* 
* 使用STL中介绍的观点来转换上述插入排序算法，明显观点是：
* 1）我们必须编写一个双参数排序和一个三参数排序的例程。
* 假设双参数排序调用三参数排序，同时使用less<Object>()作为第三个参数
* 2）数组访问必须转换成迭代器访问。
* 3）原始代码创建的tmp，在新代码中它将具有类型Object
*/

//双参数通过调用辅助函数来获得Object
template<typename Iterator>
void insertionSort(const Iterator& begin, const Iterator& end) {
	if (begin != end)
		insertionSortHelp(begin, end, *begin);
}
//双参数辅助函数通过调用三参数函数来来实现排序，默认第三个参数为less<>
template<typename Iterator,typename Object>
void insertionSortHelp(const Iterator& begin, const Iterator& end, const Object& obj) {
	insertionSort(begin, end, less<Object>());
}
//三参数通过调用辅助四参数函数来获得Object
template<typename Iterator,typename Comparator>
void insertionSort(const Iterator& begin, const Iterator& end, Comparator lessThan) {
	if (begin != end)insertionSort(begin, end, lessThan, *begin);
}
//四参数插入排序包括容器头迭代器begin，容器尾迭代器end，比较仿函数coparator，容器存储类类型object
template<typename Iterator,typename Comparator,typename Object>
void insertionSort(const Iterator& begin, const Iterator& end,
	Comparator lessThan, const Object& obj)
{
	Iterator j;
	for (Iterator p = begin + 1; p != end; ++p) {
		Object tmp = *p;
		for (j = p; j != begin && lessThan(tmp, *(j - 1)); --j)
			*j = *(j - 1);
		*j = tmp;
	}
}

/*
* Shellsort, using Shell's (poor) increments.
*/
template<typename Comparable>
void shellsort(vector<Comparable>& a) {
	for(int gap = a.size()/2;gap>0;gap/=2)
		for (int i = gap; i < a.size(); i++)
		{
			Comparable tmp = a[i];
			int j = i;
			for (; j >= gap && tmp < a[j - gap]; j -= gap)
				a[j] = a[j - gap];
			a[j] = tmp;
		}
}
/*ShellSort
* 经验研究指出，在实践中这些序列的运行要必Hibbard的好得多，其中最好的序列{1，5，19，41，109，...}
* 该序列中的项或者是 9*4^i-9*2^i+1;	或者是4^i-3*2^i+1;
* 通过将这些值放到一个数组中可以容易的实现该算法。虽然有可能存在某个增量序列使得能够对谢尔排序的运行实践做出重大改进，
* 但这个增量序列在实践中还是最为人们称道的。
*/

/* 堆排序 （heapsort） */
/*
* 优先队列可以用于以O(NlogN)时间进行排序。
* 基于该思想的算法叫做堆排序，让给出我们至今所见到的最佳的大O运行时间
* 建立N个元素的二叉堆需要花费O(N)的时间.
* 然后执行N次deleteMin操作。每个deleteMin花费O(logN)时间，
* 因此总的运行时间是O(NlogN)
*/

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
void percDown(vecotr < Comparable& a, int i, int n) {
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
	/* deleteMax */
	for(int j = a.size() - 1; j > 0; j--)
	{
		swap(a[0], a[j]);
		percDown(a, 0, j);
	}
		
}

/*
* Mergesort algorithm (driver).
*/
template<typename Comparable>
void mergeSort(vector<Comparable>& a)
{
	vector<Comparable> tmpArray(a.size());
	mergeSort(a, tmpArray, O, a.size() - 1);
}

/*
* Internal method that makes recursive calls.
* a is an array of Comparable items.
* tmpArray is an array to place the merged result.
* left is the left-most index of the subarray.
* right is the right-most index of the subarray.
*/
template<typename Comparable>
void mergeSort(vector<Comparable>& a, vector<Comparable>& tmpArray, int left, int right)
{
	if (left < right) {
		int center = (left + right) / 2;
		mergeSort(a, tmpArray, left, center);
		mergeSort(a, tmpArray, center + 1, right);
		merge(a, tmpArray, left, center + 1, right);
	}
}

/*
* Internal method that merges two sorted halves of a subarray.
* a is an array of Comparable items.
* tmpArray is an array to place the merged result.
* leftPos is the left-most index of the subarray.
* rightPos is the right-most index of the subarray.
* rightEnd is the right-most index of the subarray.
*/
template<typename Comparable>
void merge(vector<Comparable> & a, vector<Comparable>& tmpArray,
	int leftPos, int rightPos, int rightEnd)
{
	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int numElement = rightEnd - leftPos + 1;

	//Mainloop
	while (leftPos <= leftEnd && rightPos <= rightEnd)
	{
		if (a[leftPos] <= a[rightPos])tmpArray[tmpPos++] = a[leftPos++];
		else                          tmpArray[tmpPos++] = a[rightPos++];
	}
	while(leftPos<=leftEnd)       // Copy rest of left half
		tmpArray[tmpPos++] = a[leftPos++];

	while (leftPos <= rightEnd)   // Copy rest of right half
		tmpArray[tmpPos++] = a[rightPos++];

	// Copy tmpArray back
	for (int i = 0; i < numElements; i++, rightEnd--)
		a[rightEnd] = tmpArray[rightEnd];
}

/*
* QuickSort
* 像归并排序一样，快速排序也是分治的递归算法。
* 将数组S排序的基本算法由下列简单的四步组成：
* 1）如果S中元素个数是0或1，则返回。
* 2）取S中任一元素v，称之为 枢纽元(pivot)。
* 3）将S-{v}(S中其余元素)划分成两个不相交的集合：S1 = {x∈S-{v}|x<=v} 和 S2 = {x∈S-{v}|x>=v}
* 4）返回{quicksort(S1)},后跟v，继而quicksort(S2)}
*/

/*
* 枢纽元的选取：
* 1.第一个和最后一个元素都是不建议作为枢纽元选取的，也包括一个数组中的最大元素和最小元素
* 2.随机选取理论上是安全有效的，但随机器可能存在问题，且随机数的产生是昂贵的，无法有效减少算法的时间
* 3.三数中值分割法：
* 选择数组首尾中三个元素，取其中值为枢纽元
*/

/*
* Return median of left, center, and right.
* Order these and hide the pivot.
*/
template<typename Comparable>
const Comparable& median3(vector<Comparable>& a, int left, int right) {
	int center = (left + right) / 2;
	if (a[center] < a[left])swap(a[left], a[center]);
	if (a[right] < a[left])swap(a[left], a[right]);
	if (a[right] < a[center])swap(a[center], a[right]);

	// Place pivot at position right -1
	swap(a[center], a[right - 1]);
	return a[right - 1];
}

/*
* Internal quicksort method that makes recursive calls.
* Uses median-of-three partitioning and a cutoff of 10.
* a is an array of Comparable items.
* left is the left-most index of the subarray.
* right is the right-most index of the subarray.
*/
template<typename Comparable>
void quicksort(vector<Comparable>& a, int left, int right){
	if (left + 10 <= right) {
		Comparable pivot = median3(a, left, right);

		// Begin partioning
		int i = left, j = right - 1;
		for (;;) {
			//注：这里的++前缀必须放在循环判断语句里，先++再判断，否则会死循环
			while (a[++i] < pivot) {}
			while (pivot < a[--j]) {}
			if (i < j) swap(a[i], a[j]);
			else break;
		}
		swap(a[i], a[right - 1]);  // Restore pivot

		quicksort(a, left, i - 1); // Sort small elements
		quicksort(a, i + 1, right);// Sort large elements
	}
	else // Do an insertion sort on the subarray
		insertionSort(a, left, right);
}

/*
* Quicksort algorithm (driver).
*/
template<typename Comparable>
void quicksort(vector<Comparable>& a) {
	quicksort(a, 0, a.size() - 1);
}

/*
* Internal selection method that makes recursive calls.
* Uses median-of-three partitioning and a cutoff of 10.
* Places the kth smallest in a[k-1].
* a is an array of Comparable items.
* left is the left-most index of the subarray.
* k is the desired rank (1 is minimum) in the entire array.
*/
template<typename Comparable>
void quickSelect(vector<Comparable>& a, int left, int right, int k){
	if (left + 10 <= right)
	{
		Comparable pivot = median3(a, left, right);

		// Begin partitioning
		int i = left, j = right - 1;
		for (;;)
		{
			while (a[++i] < pivot) {}
			while (pivot < a[--j]) {}
			if (i < j)swap(a[i], a[j]);
			else break;
		}
		swap(a[i], a[right - 1]);  // Restore pivot
			// Recurse; only this part changes
		if (k <= i)
			quickSelect(a, left, i - 1, k);
		else if (k > i + 1)
			quickSelect(a, i + 1, right, l);
	}
	else // Do an insertion sort on the subarray
		insertionSort(a, left, right);
}

/* 间接排序 */
template<typename Comparable>
class Pointer
{
public:
	Pointer(Comparable *rhs = nullptr):pointee(rhs){}

	bool operator<(const Poiner& rhs)const { return *pointee < *rhs.pointee; }
	operator Comparabale* ()const { return pointee; }
private:
	Comparable* pointee;
};

/* 对大对象进行的间接排序 */
template<typename Comparable>
void largeObjectSort(vector<Comparable>& a) {
	vector<Pointer<Comparable>> p(a.size());
	int i, j, nextj;

	for (i = 0; i < a.size(); i++)p[i] = &a[i];

	quicksort(p);

	// shuffle items in place
	for (i = 0; i < a.size(); i++)
	{
		if (p[i] != &a[i])/* 比较 Pointer<Comparable> 和 Comparable*,
						   * 这里存在隐式转换,将Pointer<Comparable>调用*类型转换符得到Comparable*
						   */
		{
			Comparable tmp = a[i];
			for (j = i; p[j] != &a[i]; j = nextj)
			{
				nextj = p[j] - &a[0];//指针之间的减法，Ptr1-Ptr2得到的是两个指针之间分开的距离，该距离为int类型
									//因此，p[j] - &a[0]是p[j]所指向对象的索引
				a[j] = *p[j];
				p[j] = &a[j];
			}
			a[j] = tmp;
			p[j] = &a[j];
		}
	}
}

/*
* 双向隐式类型转换会导致歧义
* 例如：p[i]!=&a[i]
* 这里既可以将p[i]转换为Comparable*，并使用为基本指针变量定义的!=操作符
* 也可以将&a[i]转换为Pointer<Comparable>，并使用构造函数，然后使用Pointer<Comparable>定义的!=操作符
* 
* 有许多方法可以解决这个问题，但是只要不在任何重要的类中定义双向隐式转换就足够了。
* 如果坚持使用explicit或者直接不使用类型转换操作符，那么就永远遇不到这个问题。
*/