#pragma once
template<typename Comparable>
class Treap
{
public:
	Treap() {
		nullNode = new TreapNode;
		nullNode->left = nullNode->right = nullNdoe;
		nullNode->priority = INT_MAX;
		root = nullNode;
	}
	Treap(const Treap& rhs);
	~Treap();
	//Additional pubilc member functions (not shown)
	struct TreapNode;
	void insert(const Comparable& x, TreapNode * & t);
	void remove(const Comparable& x, TreapNode*& t);

private:
	struct TreapNode
	{
		Comparable element;
		TreapNode* left;
		TreapNode* right;
		int priority;

		TreapNode():left(nullptr),right(nullptr),priority(INT_MAX){}
		TreapNode(const Comparable &e,TreapNode*lt,TreapNode*rt,int pr)
			:element(e),left(lt),right(rt),priority(pr){}
	};
	TreapNode* root;
	TreapNode* nullNode;
	Random randomNums;
	//Additional private member functions(not shown)
};

/*
* Internal method to insert into a subtree.
* x is the item to insert
* t is the node that roots the subtree.
* Set the new root of the subtree.
* (randomNums is a Random object that is a data member of Treap.
*/
template<typename Comparable>
inline void Treap<Comparable>::insert(const Comparable& x, TreapNode*& t)
{
	if (t == nullNode)
		t = new TreapNode(x, nullNode, nullNode, randomNums, randomInt());
	else if (x < t->element)
	{
		insert(x, t->left);
		if (t->left->priotriy < t->priority)
			rotateWithLeftChild(t);
	}
	else if (t->element < x)
	{
		insert(x, t->right);
		if (t->right->priority < t->priority)
			rotateWithRightChild(t);
	}
	//else duplicate; do nothing
}

/*
* Internal method to remove from a subtree.
* x is the item to remove.
* t is the node that roots the tree.
* Set the new root of the subtree.
*/
template<typename Comparable>
inline void Treap<Comparable>::remove(const Comparable& x, TreapNode*& t)
{
	if (t != nullNode) {
		if (x < t->element)remove(x, t->left);
		else if (t->element < x)remove(x, t->right);
		else {
			//Match found
			if (t->left->priority < t->right->priority) rotateWithLeftChild(t);
			else rotateWithRightChild(t);

			if (t != nullNode)//Continue on down
				remove(x, t);
			else
			{
				delete t->left;
				t->left = nullNode;//At a leaf
			}
		}
	}
}
