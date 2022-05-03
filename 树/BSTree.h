#pragma once
#include<iostream>
#include<queue>
using namespace std;

template<typename Comparable>
class BSTree {
public:
	BSTree();
	BSTree(const BSTree& rhs);
	~BSTree();

	const Comparable& findMin()const;
	const Comparable& findMax()const;
	bool contains(const Comparable& x)const;
	bool isEmpty() const;
	void printTree() const;

	void makeEmpty();
	bool insert(const Comparable& x);
	bool remove(const Comparable& x);

	const BSTree& operator=(const BSTree& rhs);

	
	void coutw(int x, const char* s)const
	{
		for (int i = 0; i < x; i++)
			cout << s;
	}
	int pow(int x, int n)const
	{
		if (n == 0)
			return 1;
		if (n % 2 == 0)
			return pow(x * x, n / 2);
		else
			return pow(x * x, n / 2) * x;
	}
private:
	struct BNode {
		Comparable element;   // The data in the node
		BNode* left;     // Left child
		BNode* right;    // Right child

		BNode(const Comparable&theElement,BNode *lt,BNode*rt)
			:element(theElement),left(lt),right(rt){}
		const BNode operator=(const BNode& rhs)
		{
			if (this != &rhs) { 
				m_makeEmpty(*this);
				this = m_clone(rhs);
			}
			return *this;
		}
		BNode* m_clone(BNode* t)const
		{
			if (t == nullptr)return nullptr;
			return new BNode(t->element, m_clone(t->left), m_clone(t->right));
		}
	};
	BNode* root;

	int GetTreeDepth(const BNode* T)const 
	{
		if (!T)return 0;
		int l = GetTreeDepth(T->left);
		int r = GetTreeDepth(T->right);
		return (l >= r ? l : r) + 1;
	}

	bool m_insert(const Comparable& x, BNode*& t)const;
	bool m_remove(const Comparable& x, BNode*& t)const;
	void removeMin(BNode*& t)const;
	bool m_search(BSTree cur, const Comparable& x, BSTree father, BSTree* ret);
	BNode* m_findMin(BNode* t)const {//递归
		if (t == nullptr)return nullptr;
		if (t->left == nullptr)return t;
		return m_findMin(t->left);
	}
	BNode* m_findMax(BNode* t)const {//迭代
		if (t != nullptr)
			while (t->right != nullptr)t = t->right;
		return t;
	}

	bool m_contains(const Comparable& x, BNode* t)const;
	void m_makeEmpty(BNode*& t);
	void m_printTree(BNode* T)const {
		int depth = GetTreeDepth(T);
		BNode* flag = new BNode(-1, nullptr, nullptr);
		// 1.初始化
		queue<BNode*> q;
		if (T == nullptr) { // 二叉树为空
			return;
		}
		q.push(T);
		// 2.遍历整棵树
		while (1) {
			coutw(pow(2, depth), " ");
			int cnt = q.size(); // 要处理层的节点个数
			int flag2 = 0;

			for (int i = 0; i < cnt; i++)
			{
				if (q.front()->element != -1)
					flag2 = 1;
				q.push(q.front());
				q.pop();
			}

			if (!flag2)break;

			// 3.遍历该层
			while (cnt--) {
				BNode* cur= q.front();
				q.pop();

				// 4.对 cur 的操作，根据题意更改
				if (cur->element == -1)
				cout << "n";
				else
					cout << cur->element;
				coutw(pow(2, depth + 1) - 1, " ");
				// 5.将左右孩子放入队列
				if (cur->left) q.push(cur->left);
				else q.push(flag);
				if (cur->right) q.push(cur->right);
				else q.push(flag);
			}
			cout << endl;
			depth--;
		}
		delete flag;
	}

	

	
	
};



template<typename Comparable>
inline BSTree<Comparable>::BSTree()
{
}

template<typename Comparable>
inline BSTree<Comparable>::BSTree(const BSTree& rhs)
{
	this->root = rhs.root;
	return *this;
}

template<typename Comparable>
inline BSTree<Comparable>::~BSTree()
{
	makeEmpty();
}

template<typename Comparable>
inline const Comparable& BSTree<Comparable>::findMin() const
{
	return this->m_findMin();
}

template<typename Comparable>
inline const Comparable& BSTree<Comparable>::findMax() const
{
	return this->m_findMax();
}



template<typename Comparable>
inline bool BSTree<Comparable>::isEmpty() const
{
	return this->root==nullptr;
}

template<typename Comparable>
inline void BSTree<Comparable>::printTree() const
{
	m_printTree(this->root);
}

template<typename Comparable>
inline void BSTree<Comparable>::makeEmpty()
{
	this->m_makeEmpty(this->root);
}

// Returns true if x is found in the tree
template<typename Comparable>
inline bool BSTree<Comparable>::contains(const Comparable& x) const
{
	return this->m_contains(x, root);
}

// Insert x into the tree; duplicates are ignored
template<typename Comparable>
inline bool BSTree<Comparable>::insert(const Comparable& x)
{
	return this->m_insert(x, root);
}

// Remove x from the tree. Nothing is done if x is not found.
template<typename Comparable>
inline bool BSTree<Comparable>::remove(const Comparable& x)
{
	return this->m_remove(x, root);
}

/*
* Deep copy.
*/
template<typename Comparable>
inline const BSTree<Comparable>& BSTree<Comparable>::operator=(const BSTree& rhs)
{
	if (this != &rhs) {
		makeEmpty();
		root = m_clone(rhs.root);
	}
	return *this;
}

/*
* Internal method to insert into a subtree.
* x is the item to insert.
* t is the node that roots the subtree.
* Set the new root of the subtree.
*/
template<typename Comparable>
inline bool BSTree<Comparable>::m_insert(const Comparable& x, BNode*& t) const
{
	if (t == nullptr) { t = new BNode(x, nullptr, nullptr); return true; }
	else if (x < t->element)return m_insert(x, t->left);
	else if (t->element < x)return m_insert(x, t->right);
	else return false;// Duplicate; do nothing
}
#if 0
/*
* 这个是数据结构书上的，它的低效之处在于第二个else if，findMin查找到最近前驱后
* 不是直接删除这个找到的结点，而是用这个结点的data来再次递归寻找，
* 确确实实的如书中所言查找了两遍（不过确实很简明就是了）
* #endif下面那个m_remove函数是我自己改进之后的
*/
template<typename Comparable>
inline bool BSTree<Comparable>::m_remove(const Comparable& x, BNode*& t) const
{
	if (t == nullptr)return;// Item not found;do nothing
	if (x < t->element)remove(x, t->left);
	else if (t->element < x)remove(x, t->right);
	else if (t->left != nullptr && t->right != nullptr)// Found and have two children
	{
		t->element = findMin(t->right)->element;
		remove(t->element, t->right);
	}
	else{
		BNode* oldNode = t;
		t = (t->left != nullptr) ? t->left : t->right;
		delete oldNode;
}
#endif
template<typename Comparable>
inline bool BSTree<Comparable>::m_remove(const Comparable& x, BNode*& t) const
{
	if (t == nullptr)         return false;        // Item not found;remove failed
	if (x < t->element)
	{
		if (t->left)return m_remove(x, t->left);
		else return false;
	}
	else if (t->element < x) 
	{
		if (t->right)return m_remove(x, t->right);
		else return false;
	}
	else /* (x ==t->element)*/{removeMin(t); return true; }
}
template<typename Comparable>
inline void BSTree<Comparable>::removeMin(BNode*& t) const
{
	BNode* temp = t;
	BNode* minPrev = t->left;
	if      (t->left == nullptr) { t = t->right; delete temp;  }
	else if (t->right== nullptr) { t = t->left ; delete temp;  }
	else {
		while (minPrev->right) { temp = minPrev; minPrev = minPrev->right; }
		t->element = minPrev->element;//将删除结点的值换为最近前驱
		if (temp != t)temp->right = minPrev->left;
		else          temp->left  = minPrev->left;
		delete minPrev;
	}
}

#if 0
//其实如果if条件语句之后的执行语句很简短，可以将他们写在一行
template<typename Comparable>
inline bool BSTree<Comparable>::m_search(BSTree cur, const Comparable& x, BSTree father, BSTree* ret)
{
	if      (!cur)          { *ret = Father; return false;}
	else if (key < cur->data) return SearchBST(cur->lchild, key, cur, ret);
	else if (cur->data < key) return SearchBST(cur->rchild, key, cur, ret);
	else     /* Match */    { *ret = cur;	return true; }	
}


/*
* Internal method to find the smallest item in a subtree t.
* Return node containing the smallest item.
*/
template<typename Comparable>
inline BSTree<Comparable>::BNode* BSTree<Comparable>::m_findMin(BNode* t) const


/*
* Internal method to find the largest item in a subtree t.
* Return node containing the largest item.
*/
template<typename Comparable>
inline BSTree<Comparable>::BNode* BSTree<Comparable>::m_findMax(BNode* t) const

template<typename Comparable>
inline void BSTree<Comparable>::m_printTree(BNode* T) const
#endif

/*
* Internal method to test if an item is in a subtree.
* x is item to search for.
* t is the node that roots the subtree.
*/
template<typename Comparable>
inline bool BSTree<Comparable>::m_contains(const Comparable& x, BNode* t) const
{
	if (t == nullptr)       return false;
	else if (x < t->element)return m_contains(x, t->left );
	else if (x > t->element)return m_contains(x, t->right);
	else                    return true; // Match
}

/*
* Internal method to make subtree empty.
*/
template<typename Comparable>
inline void BSTree<Comparable>::m_makeEmpty(BNode*& t)
{
	if (t != nullptr)
	{
		m_makeEmpty(t->left);
		m_makeEmpty(t->right);
		delete t;
	}
	t = nullptr;
}




#if 0
//我觉得这个例子没有必要，但它也只是展示一种仿函数的使用方法
template<typename Object,typename Comparator=less<Object>>
class BinarySearchTree {
public:
	// Same methods, with Object replacing Comparable

private:
	BinaryNode* root;
	Comparator isLessThan;

	// Same methods, with Object replacing Comparable

	/*
	* Internal method to test if an item is in a subtree.
	* x is item to search for.
	* t is the node that roots the subtree.
	*/
	bool contains(const Object& x, BinaryNode* t) const
	{
		if (t == nullptr)       return false;
		else if (isLessThan(x, t->element))return m_contains(x, t->left);
		else if (isLessThan(t->element, x)) return m_contains(x, t->right);
		else                    return true; // Match
	}
};

#endif

