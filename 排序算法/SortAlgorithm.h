#pragma once
#include<functional>//less<>��greater<>
#include<vector>
#include<algorithm>
using namespace std;

/*
* Bubble Sort
* �㷨˼�룺
*    �Ƚ����ڵ�Ԫ�ء������һ���ȵڶ����󣬾ͽ�������������
*    ��ÿһ������Ԫ����ͬ���Ĺ������ӿ�ʼ��һ�Ե���β�����һ�ԡ��ⲽ���������Ԫ�ػ�����������
*    ������е�Ԫ���ظ����ϵĲ��裬�������һ����
*    ����ÿ�ζ�Խ��Խ�ٵ�Ԫ���ظ�����Ĳ��裬ֱ��û���κ�һ��������Ҫ�Ƚϡ�
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
				Comparable tmp = a[j];  //����
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
		}
	}
}

/*
* Selection Sort
* �㷨˼�룺
*    ��δ�����������ҵ���С����Ԫ�أ���ŵ��������е���ʼλ��
*    ��ʣ��δ����Ԫ���м���Ѱ����С����Ԫ�أ�Ȼ��ŵ����������е�ĩβ
*    �Դ����ƣ�ֱ������Ԫ�ؾ��������
*/
template<typename Comparable>
void SelectionSort(vector<Comparable>& a) {
	int minIndex;
	Comparable temp;
	for (int i = 0; i < a.size()-1; i++) {
		minIndex = i;
		for (int j = i + 1; j < a.size(); j++) {
			if (a[j] < a[minIndex]) minIndex = j;       // Ѱ����С����
		}
		temp = a[i];
		a[i] = a[minIndex];
		a[minIndex] = temp;
	}
}

/*
* ��������
* ��������ͳ��С�ڵ��ڸ�Ԫ��ֵ��Ԫ�صĸ���i�����Ǹ�Ԫ�ؾͷ���Ŀ�����������iλ��i��0����

    �����������һ�����裬���������е���������Ϊ�������ҳ����ڣ�0��k��������֮�ڡ�
    ��� k��������������ֵ�� �����������ϴ�Ŀռ临�Ӷȣ�һ������������ 0 �� 100 ֮������ֵ���õ��㷨�����������ʺϰ���ĸ˳������������
    ���������ǱȽ�����������ٶȿ����καȽ������㷨��

�㷨˼�룺

    �ҳ��������������������С��Ԫ�أ�
    ͳ��������ÿ��ֵΪ i ��Ԫ�س��ֵĴ������������� C �ĵ� i �
    �����еļ����ۼӣ��� C �еĵ�һ��Ԫ�ؿ�ʼ��ÿһ���ǰһ����ӣ���
    �����Ŀ�����飺��ÿ��Ԫ�� i ����������ĵ� C[i] �ÿ��һ��Ԫ�ؾͽ� C[i] ��ȥ 1��
*/

// ��������
template<typename Comparable>
void CountSort(vector<Comparable>& vecRaw)
{
	// ȷ�������������ǿ�
	if (vecRaw.empty())
		return;
	vector<Comparable> vecCount;
	// ͳ��ÿ����ֵ���ֵĴ���
	for (int i = 0; i < vecRaw.size(); i++)
		vecCount[vecRaw[i]]++;
	/*
	// ����ļ�ֵ���ֵ�λ��Ϊǰ�����м�ֵ���ֵĴ���֮��
	for (int i = 1; i < vecCountLength; i++)
		vecCount[i] += vecCount[i - 1];

	// ����ֵ�ŵ�Ŀ��λ��
	for (int i = vecRaw.size(); i > 0; i--)	// �˴�������Ϊ�˱�����ͬ��ֵ���ȶ���
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
* ��STL�У��������̲����þ��пɱ��Ե�������ɵ�������Ϊ��һ�Ĳ�����
* ���ǽ���һ�Ե�������������ĳ��Χ�ڵ���ʼ����ֹ��־��
* һ��˫������������ʹ��һ�Ե�������������������ǿ�����ġ�
* ��һ������������������һ������������Ϊ������������
* 
* ʹ��STL�н��ܵĹ۵���ת���������������㷨�����Թ۵��ǣ�
* 1�����Ǳ����дһ��˫���������һ����������������̡�
* ����˫���������������������ͬʱʹ��less<Object>()��Ϊ����������
* 2��������ʱ���ת���ɵ��������ʡ�
* 3��ԭʼ���봴����tmp�����´�����������������Object
*/

//˫����ͨ�����ø������������Object
template<typename Iterator>
void insertionSort(const Iterator& begin, const Iterator& end) {
	if (begin != end)
		insertionSortHelp(begin, end, *begin);
}
//˫������������ͨ��������������������ʵ������Ĭ�ϵ���������Ϊless<>
template<typename Iterator,typename Object>
void insertionSortHelp(const Iterator& begin, const Iterator& end, const Object& obj) {
	insertionSort(begin, end, less<Object>());
}
//������ͨ�����ø����Ĳ������������Object
template<typename Iterator,typename Comparator>
void insertionSort(const Iterator& begin, const Iterator& end, Comparator lessThan) {
	if (begin != end)insertionSort(begin, end, lessThan, *begin);
}
//�Ĳ������������������ͷ������begin������β������end���ȽϷº���coparator�������洢������object
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
* �����о�ָ������ʵ������Щ���е�����Ҫ��Hibbard�ĺõö࣬������õ�����{1��5��19��41��109��...}
* �������е�������� 9*4^i-9*2^i+1;	������4^i-3*2^i+1;
* ͨ������Щֵ�ŵ�һ�������п������׵�ʵ�ָ��㷨����Ȼ�п��ܴ���ĳ����������ʹ���ܹ���л�����������ʵ�������ش�Ľ���
* ���������������ʵ���л�����Ϊ���ǳƵ��ġ�
*/

/* ������ ��heapsort�� */
/*
* ���ȶ��п���������O(NlogN)ʱ���������
* ���ڸ�˼����㷨�����������ø���������������������ѵĴ�O����ʱ��
* ����N��Ԫ�صĶ������Ҫ����O(N)��ʱ��.
* Ȼ��ִ��N��deleteMin������ÿ��deleteMin����O(logN)ʱ�䣬
* ����ܵ�����ʱ����O(NlogN)
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
* ��鲢����һ������������Ҳ�Ƿ��εĵݹ��㷨��
* ������S����Ļ����㷨�����м򵥵��Ĳ���ɣ�
* 1�����S��Ԫ�ظ�����0��1���򷵻ء�
* 2��ȡS����һԪ��v����֮Ϊ ��ŦԪ(pivot)��
* 3����S-{v}(S������Ԫ��)���ֳ��������ཻ�ļ��ϣ�S1 = {x��S-{v}|x<=v} �� S2 = {x��S-{v}|x>=v}
* 4������{quicksort(S1)},���v���̶�quicksort(S2)}
*/

/*
* ��ŦԪ��ѡȡ��
* 1.��һ�������һ��Ԫ�ض��ǲ�������Ϊ��ŦԪѡȡ�ģ�Ҳ����һ�������е����Ԫ�غ���СԪ��
* 2.���ѡȡ�������ǰ�ȫ��Ч�ģ�����������ܴ������⣬��������Ĳ����ǰ���ģ��޷���Ч�����㷨��ʱ��
* 3.������ֵ�ָ��
* ѡ��������β������Ԫ�أ�ȡ����ֵΪ��ŦԪ
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
			//ע�������++ǰ׺�������ѭ���ж�������++���жϣ��������ѭ��
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

/* ������� */
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

/* �Դ������еļ������ */
template<typename Comparable>
void largeObjectSort(vector<Comparable>& a) {
	vector<Pointer<Comparable>> p(a.size());
	int i, j, nextj;

	for (i = 0; i < a.size(); i++)p[i] = &a[i];

	quicksort(p);

	// shuffle items in place
	for (i = 0; i < a.size(); i++)
	{
		if (p[i] != &a[i])/* �Ƚ� Pointer<Comparable> �� Comparable*,
						   * ���������ʽת��,��Pointer<Comparable>����*����ת�����õ�Comparable*
						   */
		{
			Comparable tmp = a[i];
			for (j = i; p[j] != &a[i]; j = nextj)
			{
				nextj = p[j] - &a[0];//ָ��֮��ļ�����Ptr1-Ptr2�õ���������ָ��֮��ֿ��ľ��룬�þ���Ϊint����
									//��ˣ�p[j] - &a[0]��p[j]��ָ����������
				a[j] = *p[j];
				p[j] = &a[j];
			}
			a[j] = tmp;
			p[j] = &a[j];
		}
	}
}

/*
* ˫����ʽ����ת���ᵼ������
* ���磺p[i]!=&a[i]
* ����ȿ��Խ�p[i]ת��ΪComparable*����ʹ��Ϊ����ָ����������!=������
* Ҳ���Խ�&a[i]ת��ΪPointer<Comparable>����ʹ�ù��캯����Ȼ��ʹ��Pointer<Comparable>�����!=������
* 
* ����෽�����Խ��������⣬����ֻҪ�����κ���Ҫ�����ж���˫����ʽת�����㹻�ˡ�
* ������ʹ��explicit����ֱ�Ӳ�ʹ������ת������������ô����Զ������������⡣
*/