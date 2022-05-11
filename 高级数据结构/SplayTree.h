#pragma once
/*
* 自顶向下的伸展树
*/
template<typename Comparable>
class SplayTree
{
public:
	SplayTree() {
		nullNode = new BinaryNode;
		nullNode->left = nullNode->right = nullNode;
		root = nullNode;
	}

	~SplayTree() {
		makeEmpty();
		delete nullNode;
	}

	//Same methods as for BinarySearchTree (omitted)
	void insert(const Comparable& x);
	void remove(const Comparable& x);
	void makeEmpty();

	SplayTree(const SplayTree& rhs);
	const SplayTree& operator=(const SplayTree& rhs);

private:
	struct BinaryNode {	/*Usual code for binary search tree nodes */};
	BinaryNode* root;
	BinaryNode* nullNode;
	//same methods as for BinarySearchTree (omitted)

		//Tree manipulations
	void rotateWithLeftChild(BinaryNode*& k2);
	void rotateWithRightChild(BinaryNode*& k1);
	void splay(const Comparable& x, BinaryNode*& t);
		
};



/*
* splaying algorithm, however, the splay tree code
* depends on the accessed item going to the root.
* x is the target item to splay around.
* t is the root of the subtree to splay.
*/
template<typename Comparable>
inline void SplayTree<Comparable>::splay(const Comparable& x, BinaryNode*& t)
{
	BinaryNode* leftTreeMax, * rightTreeMin;
	static BinaryNode header;

	header.left = header.right = nullNode;
	leftTreeMax = rightTreeMin = &header;

	nullNode->element = x;//Guarantee a mathc
	for (;;)
		if (x < t->element)
		{
			if (x < t->left->element) rotateWithLeftChild(t);
			if (t->left == nullNode)break;
			//Link right
			rightTreeMin->left = t;
			rightTreeMin = t;
			t = t->left;
		}
		else if (t->element < x) {
			if (t->right->element < x) rotateWithRightChild(t);
			if (t->right == nullNode)break;
			//Link Left
			leftTreeMax->right = t;
			leftTreeMax = t;
			t = t->right;
		}
		else break;
	leftTreeMax->right = t->left;
	rightTreeMin->left = t->right;
	t->left = header.right;
	t->right = header.left;
}

template<typename Comparable>
inline void SplayTree<Comparable>::insert(const Comparable& x)
{
	static BinaryNode* newNode = nullptr;
	if (newNode == nullptr) newNode = new BinaryNode;
	newNode->element = x;

	if (root == nullNode) {
		newNode->left = newNode->right = nullNode;
		root = newNode;
	}
	else {
		splay(x,root);
		if (x < root->element) {
			newNode->left = root->left;
			newNode->right = root;
			root->left = nullNode;
			root = newNode;
		}
		else
			if (root->element < x) {
				newNode->right = root->right;
				newNode->left = root;
				root->right = nullNode;
				root = newNode;
			}
			else return;

	}
	newNode = nullptr;// So next insert will call new
}

template<typename Comparable>
inline void SplayTree<Comparable>::remove(const Comparable& x)
{
	BinaryNode* newTree;
	//if x is found, it will be at the root
	splay(x, root);
	if (root->element != x)return;//item not found; do nothing
	if (root->left == nullNode) newTree = root->right;
	else {
		//FInd the maximum in the left subtree.
		//Splay it to the root; and then attach right child;
		newTree = root->left;
		splay(x, newTree);
		newTree->right = root->right;
	}
	delete root;
	root = newTree;
}

template<typename Comparable>
inline void SplayTree<Comparable>::makeEmpty()
{
	while (!isEmpty())
	{
		findMax();//Splay max item to root
		remove(root->element);
	}
}
