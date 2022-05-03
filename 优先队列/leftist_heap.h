#pragma once
template<typename Comparable>
class LeftistHeap
{
public:
	LeftistHeap();
	LeftistHeap(const LeftistHeap& rhs);
	~LeftistHeap();

	bool isEmpty() const { return this->root == nullptr; }
	const Comparable& findMin()const;

	/*
	* Insert x; duplicates allowed.
	*/
	void insert(cosnt Comparable& x) {
		root = merge(new LeftistNode(x), root);
	}
	void makeEmpty();

	/*
	* Merge rhs into the priority queue.
	* rhs becomes emtpy. rhs must be different from this.
	*/
	void merge(LeftistHeap& rhs) {
		if (this == &rhs)return;
		root = merge(root, rhs.root);
		rhs.root = nullptr;
	}

	const LeftistHeap& operator=(const LeftistHeap& rhs) {
		if (this != &rhs) {
			makeEmpty();
			root = clone(rhs.root);
		}
		return *this;
	}

	/*
	* Remove the minimum item.
	* Throws UnderflowException if empty.
	*/
	void deleteMin() {
		if (isEmpty())throw UnderflowException();
		LeftistNode* oldRoot = root;
		root = merge(root->left, root->right);
		delete oldRoot;
	}
	/*
	* Remove the minimum item and place it in minItem.
	* Throws UnderflowExcetion if empty.
	*/
	void deleteMin(Comparable& minItem) {
		minItem = findMin();
		deleteMin();
	}
private:
	struct LeftistNode
	{
		Comparable element;
		LeftistNode* left;
		LeftistNode* right;
		int npl;

		LeftistNode(const Comparable & theElement,LeftistNode*lt = nullptr,
			LeftistNode*rt = nullptr,int np = 0)
			:element(theElement),left(lt),right(rt),npl(np){}

		
	};
	const LeftistNode& operator=(const LeftistNode& rhs) {
		if (this != &rhs) {
			makeEmpty();
			root = clone(rhs.root);
		}
		return *this;
	}

	LeftistNode* root;

	/*
	* Internal method to merge two roots.
	* Deals with deviant cases and calls revursive merge1.
	*/
	LeftistNode* merge(LeftistNode* hl, LeftistNode* h2) {
		if (h1 == nullptr)                      return h2;
		if (h2 == nullptr)                      return h1;

		if (h1->element < h2->element)          return merge1(h1, h2);
		else                                    return merge1(h2, h1);
	}

	/*
	* Internal method to merge two roots.
	* Assumes trees are not empty, and h1's root contains smallest item.
	*/
	LeftistNode* merge1(LeftistNode* h1, LeftistNode* h2) {
		if (h1->left == nullptr)  // Single node
			h1->left = h2;        // Other fields in h1 already accurate.
		else {
			h1->right = merge(h1->right, h2);
			if (h1->left->npl < h1->right->npl)
				swapChildren(h1);
			h1->npl = h1->right->npl + 1;
		}
		return h1;
	}

	void swapChildren(LeftistNode* t) {
		auto temp = new LeftistNode;
		temp = t->right;
		t->right = t->left;
		t->left = temp;
		delete temp;
	}
	void reclaimMemory(LeftistNode* t);
	LeftistNode* clone(LeftistNode* t)const {
		if (t = nullptr)return nullptr;
		return new LeftistNode(t.element, clone(t.left), clone(t.right), t.npl);
	}
};