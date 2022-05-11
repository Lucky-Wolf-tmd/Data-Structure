#pragma once

/*
* 红黑树说具有下列着色性质的二叉查找树
* 1.每一个结点 要么是红色，要么是黑色
* 2.根结点是黑色的
* 3.如果一个结点是红色的，那么它的子节点一定是黑色的。
* 4.从一个结点到一个nullptr指针的每一条路径都必须包含相同数目的黑色结点
*/

template<typename Comparable>
class RedBlackTree {
public:
	explicit RedBlackTree(const Comparable& negInf);
	RedBlackTree(const RedBlackTree& rhs);
	~RedBlackTree();

	const Comparable& findMin()cosnt;
	const COmparable& findMax()const;
	bool contains(const Comparable& x)const;
	bool isEmpty()const;
	void printTree() const;

	void makeEmpty();
	void insert(const Comparable& x);
	void remove(const Comparable& x);
	enum{RED,BLACK};

	const RedBlackTree& operator=(const RedBlackTree& rhs);

private:
	struct RedBlackNode {
		Comparable element;
		RedBlackNode* left;
		RedBlackNode* right;
		int color;

		RedBlackNode(const Comparable & theElement = Comparable(),
			RedBlackNode*lt = nullptr,RedBlackNode*rt = nullptr,
			int c = BLACK)
			:element(theElement),left(lt),right(rt),color(c){}
	};

	RedBlackNode* header;//The tree header(contains neginf)
	RedBlackNode* nullNode;

	//Used in insert routine and its helpers (logically static)
	RedBlackNode* current;
	RedBlackNode* parent;
	RedBlackNode* grand;
	RedBlackNode* great;

	//Usual recursive stuff
	void reclaimMemory(RedBlackNode* t);
	void printTree(RedBlackNode* t)const;
	RedBlackNode* clone(RedBlackNode* t)const;

	//Red-Black tree manipulations
	void handleReorient(const Comparable& item);
	RedBlackNode* rotate(const Comparable& item, RedBlackNode* theParent);
	void rotateWithLeftChild(RedBlackNode*& k2);
	void rotateWithRightChild(RedBlackNode*& k1);
};

/*
* Construct the tree
* negInf is a value less than or equal to all others
*/
template<typename Comparable>
inline RedBlackTree<Comparable>::RedBlackTree(const Comparable& negInf)
{
	nullNode = new RedBlackNode;
	nullNode->left = nullNode->right = nullNode;
	header = new RedBlackNode(negInf);
	header->left = header->right = nullNode;
}

template<typename Comparable>
inline void RedBlackTree<Comparable>::printTree() const
{
	if (header->right == nullNode)cout << "Empty tree" << endl;
	else printTree(header->right);
}

template<typename Comparable>
inline void RedBlackTree<Comparable>::printTree(RedBlackNode* t) const
{
	if (t != t->left) {
		printTree(t->left);
		cout << t->element << endl;
		printTree(t->right);
	}
}

template<typename Comparable>
inline const RedBlackTree<Comparable>& RedBlackTree<Comparable>::operator=(const RedBlackTree& rhs)
{
	if (this != &rhs) {
		makeEmpty();
		header->right = clone(rhs.header->right);
	}
	return *this;
}

template<typename Comparable>
inline RedBlackTree<Comparable>::RedBlackNode* RedBlackTree<Comparable>::clone(RedBlackNode* t) const
{
	if (t == t->left)//Can not test against nullNode!!!
		return nullNode;
	else
		return new RedBlackNode(t->element, clone(t->left), clone(t->right), t->color);
}

/*
* Internal routine that performs a single or double rotation.
* Because the result is attacked to the parent, there are four cases.
* Called by handleReorient.
* item is the item in handleReorient.
* theParent is the parent of the root of the rotated subtree.
* Return the root of the rotated subtree.
*/
template<typename Comparable>
inline RedBlackTree<Comparable>::RedBlackNode* RedBlackTree<Comparable>::rotate(const Comparable& item, RedBlackNode* theParent)
{
	if (item < theParent->element) {
		item < theParent->left->element ?
			rotateWithLeftChild(theParent->left) : //LL
			rotateWithRightChild(theParent->left); //LR
		return theParent->left;
	}
	else
	{
		item < theParent->right->element ?
			rotateWithLeftChild(theParent->right) : //RL
			rotateWithRightChild(theParent->right); //RR
		return theParent->right;
	}
}

/*
* Internal routine that is called during an insertion if a node has two red children.
* Performs flip and rotations. 
* item is the item being inserted.
*/
template<typename Comparable>
inline void RedBlackTree<Comparable>::handleReorient(const Comparable& item)
{
	//Do the color flip
	current->color = RED;
	current->left->color = BLACK;
	current->right->color = BLACK;

	if (parent->color == RED)//Have to rotate
	{
		grand->color = RED;
		if (item < grand->element != item < parent->element)
			parent = rotate(item, grand); //Start dbl rotate
		current = rotate(item, great);
		current->colot = BLACK;
	}
	header->right->color = BLACK;//make root black
}

template<typename Comparable>
inline void RedBlackTree<Comparable>::insert(const Comparable& x)
{
	current = parent = grand = header;
	nullNode->element = x;

	while (current->element != x) {
		great = grand; greand = parent; parent = current;
		current = x < current->element ? current->left : current->right;

		//check if two red children; fix if so
		if (current->left->color == RED && current->right->color == RED)
			handleReorient(x);
	}

	//insertion fails if already present
	if (current != nullNode)return;
	current = new RedBlackNode(x, nullNode, nullNode);

	//Attach to parent
	if (x < parent->element)
		parent->left = current;
	else
		parent->right = current;
	handleReorient(x);//Reorient 重新定向
}