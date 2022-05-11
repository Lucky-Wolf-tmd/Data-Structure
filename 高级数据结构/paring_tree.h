#pragma once
struct PairNode;
typedef PairNode* Position;

/*
* Insert item x into the priority queue, maintaining heap order.
* Return the Position(a pointer to the node) containing the new item.
*/
Position insert(cosnt Comparable& x) {
	PairNode* newNode = newPairNode(x);

	if (root = nullptr)root = newNode;
	else compareAndLink(root, newNode);
	return newNode;
}

/*
* Change the value of the item stored in the pairing heap.
* Throw IllegalArgumentException if newVal is larger than
*  currently stored value.
* p is a Position returned by insert.
* newVal is the new value, which must be smaller
* than the currently stored value.
*/
void decreasedKey(Position p, const Comparable& newVal) {
	if (p->element < newVal)throw IllegalArgumentException();//newVal cannot be bigger
	p->element = newVal;
	if (p != root) {
		if (p->nextSibling != nullptr)p->nextSibling->prev = p->prev;
		if (p->prev->leftChild == p)p->prev->leftChild = p->nextSibling;
		else  p->prev->nextSibling = p->nextSibling;

		p->nextSibling = nullptr;
		compareAndLink(root, p);
	}
}

void deleteMin()
{
	if (isEmpty())throw UnderFlowException();
	PairNode* oldRoot = root;

	if (root->leftChild == nullptr)root = nullptr;
	else root = combineSiblings(root->leftChild);
	delete oldRoot;
}

/*
* Internal method that implements two-pass merging.
* firstSibling the root of the conglomerate and is assumed not nullptr.
*/
PairNode* combineSiblings(PairNode* firstSibling)
{
	if (firstSibling->nextSibling == nullptr)return firstSibling;

	//Allocate the array
	static vector<PairNode*> treeArray(5);

	//Store the subtrees in an array
	int numSiblings = 0;
	for (; firstSibling != nullptr; numSiblings++) {
		if (numSiblings == treeArray.size())
			treeArray.resize(numSiblings * 2);
		treeArray[numSiblings] = firstSibling;
		firstSibling->prev->nextSibling = nullptr;//break links
		firstSibling = firstSibling->nextSibling;
	}

	if (numSiblings == treeArray.size())
		treeArray.resize(numSiblings + 1);
	treeArray[numSiblings] = nullptr;

	//Combine subtrees two at a time, going left to right
	int i = 0;
	for (; i + 1 < numSiblings; i += 2)
		compareAndLink(treeArray[i], treeArray[i + 1]);
	int j = i - 2;

	// j has the result of last comparaAndLind.
	// If an odd number of trees, get the last one.
	if (j == numSiblings - 3)
		compareAndLink(treeArray[j], treeArray[j + 2]);

	//Now go right to left, merging last tree with
	// next to last. The result becomes the new last.
	for (; j >= 2; j -= 2)
		compareAndLink(treeArray[j - 2], treeArray[j]);
	return treeArray[0];
}