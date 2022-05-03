#pragma once
template<typename Comparable>
struct AvlNode {
	Comparable element;
	AvlNode* left;
	AvlNode* right;
	int height;

	AvlNode(const Comparable& theElement, AvlNode* lt, AvlNode* rt, int h = 0):
		element(theElement),left(lt),right(rt),height(h){}

	/*
	* Return the height of node t or -1 if nullptr.
	*/
	int height(AvlNode* t)const
	{
		return t == nullptr ? -1 : t->height;
	}

	int max(int a, int b) { return a > b ? a : b; }
	/*
	* Rotate binary tree node with left child.
	* For AVL trees, this is a single rotation 
	* Update heights, then set new root.
	*/
	void rotateWithLeftChild(AvlNode*& cur) {
		AvlNode* curL = cur->left;
		cur->left = curL->right;
		curL->right = cur;

		cur->height = max(height(cur->left), height(cur->right)) + 1;
		curL->height = max(height(curL->left), height(curL->right)) + 1;

		cur = curL;
	}
	/*
	* Rotate binary tree node with right child.
	*/
	void rotateWithRightChild(AvlNode*& cur) {
		AvlNode* curR = cur->right;
		cur->right = curR->left;
		curR->left = cur;

		cur->height = max(height(cur->left), height(cur->right)) + 1;
		curR->height = max(height(curR->left), height(curR->right)) + 1;

		cur = curR;
	}

	/*
	* Double rotate binary tree node: first left child
	* with its right child; then node cur with new left child.
	* For AVL trees ,this is a double rotation 
	* Update heights, then set new root.
	*/
	void doubleWithLeftChild(AvlNode*& cur)
	{
		rotateWithRightChild(cur->left);
		rotateWithLeftChild(cur);
	}
	void doubleWithRightChild(AvlNode*& cur)
	{
		rotateWithLeftChild(cur->right);
		rotateWithRightChild(cur);
	}

	/*
	* Internal method to insert into a subtree.
	* x is the item to insert.
	* t is the node that roots the subtree.
	* Set the new root of the subtree.
	*/
	void insert(const Comparable& x, AvlNode*& t)
	{
		if (t == nullptr)t = new AvlNode(x, nullptr, nullptr);
		else if (x < t->element) {
			insert(x, t->left);
			if (height(t->left) - height(t->right) == 2) //不平衡，插完之后左倾
			{
				if (x < t->left->element)rotateWithLeftChild(t);
				else                     doubleWithLeftChild(t);
			}
		}
		else if (t->element < x) {
			insert(x, t->right);
			if (height(t->right) - height(t->left) == 2) //不平衡，插完之后右倾
			{
				if (t->right->element < x)rotateWithRightChild(t);
				else                      doubleWithRightChild(t);
			}

		}
		else /* x == t->element */; // Duplicate; do nothing
		t->height = max(height(t->left), height(t->right)) + 1;
	}

	/*
	* Internal method to remove a subtree.
	* x is the item to remove.
	* t is the node that roots the subtree.
	* Set the new root of the subtree.
	*/
	void remove(const Comparable& x, AvlNode*& t) {
		if (x == t->element)  removeMin(t);
		else if (x < t->element)  m_remove(x, t->left);
		else if (t->element < x)  m_remove(x, t->right);
		else; /* (t == nullptr)*/  // Item not found;remove failed
	}
	void removeMin(AvlNode*& t) {
		AvlNode* temp = t, minPrev = t->left;
		if (t->left == nullptr) { t = t->right; delete temp; return true; }
		else if (t->right == nullptr) { t = t->left; delete temp; return true; }
		else {
			while (minPrev->right) { temp = minPrev; minPrev = minPrev->right; }
			t->element = minPrev->element;//将删除结点的值换为最近前驱
			if (temp != t)temp->right = minPrev->left;
			else          temp->left = minPrev->left;
			delete minPrev;
		}
	 }

	const AvlNode*& operator=(const AvlNode*& rhs)
	{
		if (this != &rhs) {
			makeEmpty();
			root = clone(rhs.root);
		}
		return *this;
	}
};

