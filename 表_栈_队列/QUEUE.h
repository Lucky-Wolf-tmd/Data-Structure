#pragma once
#include"VECTOR.h"
#include"LIST.h"
template<typename Object>
class Queue_vector {
	Queue_vector() { init(); }
	~Queue_vector() { delete theQueue; }
	Queue_vector(const Stack_list& rhs)
	{
		init();
		*this = rhs;
	}
	const Queue_vector& operator=(const Queue_vector& rhs) {
		if (this == &rhs)//如果这两个东西地址相同（即是同一个东西）
			return *this;
		*theQueue = rhs.theQueue;
		return *this;
	}

	const Object front() const { return theQueue->front(); }
	const Object back() const { return theQueue->back(); }

	int size() const { return theQueue->size(); }
	bool empty() const { return size() == 0; }
	void clear() { theQueue->clear(); }

	void enqueue(const Object& x) { theQueue->push_back(x); }
	Object dequeue() { Object A = theQueue->front(); theQueue->pop_front(); return A; }
private:
	Vector<Object>* theQueue;
	void init() {	theQueue = new Vector<Object>;};
};