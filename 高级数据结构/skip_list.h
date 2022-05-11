#pragma once
/*1-2-3确定性跳跃表(deterministic skip list */

template<typename Comparable>
class DSL {
public:
	/*
	* Construct the tree.
	* inf is the largest Comparable.
	*/

	explicit DSL(const Comparable& inf) :INFINITY(inf) {
		bottom = new SkipNode();
		bottom->right = bottom->down = bottom;
		tail = new SkipNode(INFINITY);
		tail->right = tail;
		header = new SkipNode(INFINITY, tail, bottom);
	}
	
	//Additional public member functions(not shown)
	void insert(const Comparable& x);
	bool contains(const Comparable& x)const;

private:
	struct SkipNode {
		Comparable element;
		SkipNode* right;
		SkipNode* down;

		SkipNode(const Comparable&theElement = Comparable(),
			SkipNode* rt = nullptr,SkipNode*dt = nullptr)
			: element(theElement),right(rt),down(dt){}
	};

	Comparable INFINITY;
	SkipNode* header;//The list
	SkipNode* bottom;
	SkipNode* tail;

	//Additional private member funcions (not shown)
};

template<typename Comparable>
inline void DSL<Comparable>::insert(const Comparable& x)
{ 
	SkipNode* current = header;
	bottom->element = x;
	while (current != bottom)
	{
		while (current->element < x)
			current = current->right;

		//If gap size is 3 or at bottom level and
		// must insert, then promote middle element

		if (current->down->right->right->element < current->element) {
			current->right = new SkipNode(current->element,
				current->right, current->down->right->right);
			current->element = current->down->right->element;
		}
		else
			current = current->down;

	}
	//Raise height of DSL if necessary
	if (header->right != tail) header = new SkipNode(INFINITY, tail, header);
}

template<typename Comparable>
inline bool DSL<Comparable>::contains(const Comparable& x) const
{
	SkipNode* current = header;

	bottom->element = x;
	for (;;)
		if (x < current->element)     current = current->down;
		else if (current->element < x)current = current->right;
		else                          return current != bottom;
}
