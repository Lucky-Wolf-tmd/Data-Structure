#pragma once
#include"LIST.h"
#include"VECTOR.h"
template<typename Object>
class Stack_list {
public:
	Stack_list() { init(); }
	~Stack_list() { delete theStack; }
	Stack_list(const Stack_list& rhs)
	{
		init();
		*this = rhs;
	}
	const Stack_list& operator=(const Stack_list& rhs) {
		if (this == &rhs)//如果这两个东西地址相同（即是同一个东西）
			return *this;
		*theStack = rhs.theStack;
		return *this;
	}

	int size() const { return theStack->size(); }
	bool empty() const { return size() == 0; }
	void clear() { theStack->clear(); }

	const Object& top()const  { return theStack->back(); }

	void push(const Object& x) { theStack->push_back(x); }
	Object pop() { Object A = top(); theStack->pop_back(); return A; }

private:
	List<Object>* theStack;
	void init() { theStack = new List<Object>; }
};

template<typename Object>
class Stack_vector {

public:
	Stack_vector() { init(); }

	~Stack_vector() { delete theStack; }
	Stack_vector(const Stack_vector& rhs)
	{
		init();
		*this = rhs;
	}
	const Stack_vector& operator=(const Stack_vector& rhs) {
		if (this == &rhs)//如果这两个东西地址相同（即是同一个东西）
			return *this;
		*theStack = rhs.theStack;
		return *this;
	}

	int size() const { return theStack->size(); }
	bool empty() const { return size() == 0; }
	void clear() { theStack->clear(); }

	const Object& top()const { return theStack->back(); }

	void push(const Object& x) { theStack->push_back(x); }
	Object pop() { Object A = top(); theStack->pop_back(); return A; }

private:
	Vector<Object>* theStack;
	void init() { theStack = new Vector<Object>; }
};