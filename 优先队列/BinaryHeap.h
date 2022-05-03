#pragma once
#include<vector>
using namespace std;
/*
* 堆序性质：
* 小根堆和大根堆
* 在堆中，对于每个结点X，X的父亲的Key小于X的Key，根节点除外（无父节点）
*/
template<typename Comparable>
class BinaryHeap
{
public:
	explicit BinaryHeap(int capacity = 100);
	explicit BinaryHeap(const vector<Comparable>& items)
		:theArray(items.size()+10),currentSize(items.size())
	{
		for (int i = 0; i < items.size(); i++)
			theArray[i + 1] = items[i];
		buildHeap();
	}

	bool isEmpty() const;
	const Comparable& findMin()const;

	void insert(const Comparable& x) {
		if (currentSize == theArray.size() - 1)
			theArray.resize(theArray.size() * 2);

		// Percolate up  上滤
		int hole = ++currentSize;
		for (; hole > 1 && x < theArray[hole / 2]; hole /= 2)
			theArray[hole] = theArray[hole / 2];
		theArray[hole] = x;

	}

	/*
	* Remove the minimum item.
	* Throws UnderflowException if empty.
	*/
	void deleteMin() {
		if (isEmpty())throw "underflowException()";

		theArray[1] = theArray[currentSize--];
		percolateDown(1);
	}
	/*
	* Remove the minimum item and place it in minItem.
	* Throws UnderflowExcetion if empty.
	*/
	void deleteMin(Comparable& minItem) {
		if (isEmpty())throw "UnderflowException()";

		minItem = theArray[1];
		theArray[1] = theArray[currentSize--];
		percolateDown(1);
	}
	void makeEmpty();

private:
	int  currentSize;  //Number of elements in heap
	vector<Comparable>theArray; // The heap array


	/*
	* Establish heap order property from an arbitrary
	* arrangement of items.Runs in linear time.
	*/
	void buildHeap() {
		for (int i = currentSize / 2; i > 0; i--)percolateDown(i);
	}

	/*
	* Internal method to percolate down in the heap.
	* hole is the index at which the percolate begins.
	*/
	void percolateDown(int hole) {
		int child;
		Comparable tmp = theArray[hole];

		for (; hole * 2 <= currentSize; hole = child)
		{
			child = hole * 2;
			if (child != currentSize && theArray[child + 1] < theArray[child])
				child++;
			if (theArray[child] < tmp)
				theArray[hole] = theArray[child];
			else
				break;
		}
		theArray[hole] = tmp;
	}
};