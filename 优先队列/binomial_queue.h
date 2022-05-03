#pragma once
#include<vector>
using namespace std;
template<typename Comparable>
class BinomialQueue
{
public:
	BinomialQueue();
	BinomialQueue(const Comparable& item);
	BinomialQueue(const BinomialQueue& rhs);
	~BinomialQueue();

	bool isEmpty()const;
	const Comparable& findMin()const;

	void insert(const Comparabl& x);
	void deleteMin();

	/*
	* Remove the minimum item and place it in minItem.
	* Throws UnderflowException if empty.
	*/
	void deleteMin(Comparable& minitem) {
		if (isEmpty())throw UnderflowException();

		int minIndex = findMinIndex();
		minItem = theTrees[minIndex]->element;

		BinomialNode* oldRoot = theTrees[minIndex];
		BinomialNode* deletedTree = oldRoot->leftChild;
		delete oldRoot;

		// Construct H''
		BinomialQueue deletedQueue;
		deletedQueue.theTrees.resize(minIndex + 1);
		deletedQueue.currentSize = (1 << minIndex) - 1;
		for (int j = minIndex - 1; j >= 0; j--)
		{
			deletedQueue.theTrees[j] = deletedTree;
			deletedTree = deletedTree->nextSibling;
			deletedQueue.theTrees[j]->nextSibling = nullptr;
		}

		// Construct H'
		theTrees[minIndex] = nullptr;
		currentSize -= deletedQueue.currentSize + 1;
		merge(deletedQueue);
	}

	void makeEmpty();

	/*
	*  Merge rhs into the priority queue.
	* rhs becomes empty. ths must be different from this.
	* 
	* 优化方案：a.如果没有树留在H2中，且carry树为nullptr，则修改merge例程以中止合并
	*			（在实现b的前提下，当whichcase为既没有t2也没有carry的时候就跳出循环（需要findMinindex)）
	*		   b.修改merge使得较小的树总被合并到较大的树种(在函数里搞几个引用就可以了 ）
	*/
	void merge(BinomialQueue& rhs) {
		if (this == &rhs)// Avoid aliasing problems
			return;

		currentSize += rhs.currentSize;
		if (currentSize > capacity())
		{
			int oldNumTrees = theTrees.size();
			int newNumTrees = max(theTrees.size(), rhs.theTrees.size()) + 1;
			theTrees.resize(newNumTrees);
			for (int i = oldNumTrees; i < newNumTrees; i++)
				theTrees[i] = nullptr;
		}

		BinomialNode* carry = nullptr;
		for (int i = 0, j = 1; j <= currentSize; i++, j *= 2) {
			BinomialNode* t1 = theTrees[i];
			BinomialNode* t2 = i < rhs.theTrees.size() ? rhs.theTrees[i] : nullptr;
			int whichCase = t1 == nullptr ? 0 : 1;
			whichCase += t2 == nullptr ? 0 : 2;
			whichCase += carry == nullptr ? 0 : 4;

			switch (whichCase)
			{
			case 0:/* No trees */
			case 1:/* Only this */
				break;
			case 2:/* Only rhs */
				theTrees[i] = t2;
				rhs.theTrees[i] = nullptr;
				break;
			case 4:/* Only carry */
				theTrees[i] = carry;
				carry = nullptr;
				break;
			case 3:/* this and rhs */
				carry = combineTrees(t1, t2);
				theTrees[i] = rhs.theTrees[i] = nullptr;
				break;
			case 5:/* this and carry */
				carry = combineTrees(t1, carry);
				theTrees[i] = nullptr;
				break;
			case  6:/*rhs and carry */
				carry = combineTrees(t2, carry);
				rhs.theTrees[i] = nullptr;
				break;
			case 7:/* All three */
				theTrees[i] = carry;
				caary = combineTrees(t1, t2);
				rhs.theTrees[i] = nullptr;
				break;
			}
		}
		for (int k = 0; k < rhs.theTrees.size(); k++)
			rhs.theTrees[k] = nullptr;
		rhs.currentSize = 0;
	}


	

	const BinomialQueue& operator=(const BinomialQueue& rhs);

private:
	struct BinomialNode
	{
		Comparable element;
		BinomialNode* leftChild;
		BinomialNode* nextSibling;

		BinomialNode(const Comparable& theElement, BinomialNode* lt, BinomialNode* rt)
			:element(theElement), leftChild(lt), nextSibling(rt){}
	};

	enum{DEFAULT_TREES = 1};

	int currentSize;               // Number of items in priority queue
	vector<BinomialNode*>theTrees;// An array of tree roots

	/*
	* Return the result of merging equal-sized t1 and t2.
	*/
	BinomialNode* combineTrees(BinomialNode* t1, BinomialNode* t2)
	{
		if (t2->element < t1->element)return combineTrees(t2, t1);
		t2->nextSibling = t1->leftChild;
		t1->leftChild = t2;
		return t1;
	}

	int findMinIndex()const {
		int i;
		int minIndex;
		for (i = 0; theTrees[i] == nullptr; i++)
			;

		for (minIndex = i; i < theTrees.size(); i++)
		{
			if (theTrees[i] != nullptr && theTrees[i]->element < theTrees[minIndex]->element)
				minIndex = i;
		}
		return minIndex;
	}
	int capacity()const { return theTrees.size(); }
	BinomialNode* combineTrees(BinomialNode* t1, BinomialNode* t2);
	void makeEmpty(BinomialNode*& t);
	BinomialNode* clone(BinomialNode* t)const;
};