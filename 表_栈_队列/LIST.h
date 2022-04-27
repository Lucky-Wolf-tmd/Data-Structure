#pragma once
#include"MyException.h"

template<typename Object>
class List
{
private:
	struct Node {
		Object data;
		Node* prev;
		Node* next;

		Node(const Object& d = Object(), Node* p = nullptr, Node* n = nullptr)
			:data(d), prev(p), next(n) {}
	};
public:
	class const_iterator {
	public:
		const_iterator() :current(nullptr) {}
		const Object& operator*()const { return retrieve(); }
		const_iterator& operator++() {
			current = current->next;
			return *this;
		}
		const_iterator operator++(int) {
			const_iterator old = *this;
			++(*this);
			return old;
		}
		const_iterator& operator--() {
			current = current->prev;
			return *this;
		}
		const_iterator operator--(int) {
			const_iterator old = *this;
			--(*this);
			return old;
		}
		bool operator==(const const_iterator& rhs)const
		{
			return current == rhs.current;
		}
		bool operator!=(const const_iterator& rhs)const
		{
			return !(*this == rhs);
		}
	protected:
		Node* current;

		Object& retrieve() const { return current->data; }
		const_iterator(Node* p) :current(p) {}

		//错误检验能力的实现工具
		const List<Object>* theList;
		const_iterator(const List<Object>& lst, Node* p) :theList(&lst), current(p) {}
		void assertIsValid() const
		{
			ABORT((theList == nullptr || current == nullptr || current == theList->head),
				"Iterator Out Of Bounds Exception");
		}
		void assertIsinList(const List<Object>* thisList) const {
			ABORT((theList != thisList),
				"Iterator Mismatch Exception!");
		}
		friend class List<Object>;
	};
	class iterator : public const_iterator {
	public:
		iterator() {}
		Object& operator*() { return const_iterator::retrieve(); }
		const Object& operator*()const { return const_iterator::operator*(); }

		iterator& operator++() {
			const_iterator::current = const_iterator::current->next;
			return *this;
		}
		iterator operator++(int) {
			iterator old = *this;
			++(*this);
			return old;
		}
		iterator& operator--() {
			const_iterator::current = const_iterator::current->prev;
			return *this;
		}
		iterator operator--(int) {
			iterator old = *this;
			--(*this);
			return old;
		}

	protected:
		iterator(const List<Object>& lst, Node* p) : const_iterator(lst, p) {  }
		friend class List<Object>;
	};

public:
	List() { init(); }
	~List() {
		clear();
		delete head;
		delete tail;
	}
	List(const List& rhs)
	{
		init();
		*this = rhs;
	}
	const List& operator=(const List& rhs) {
		if (this == &rhs)return *this;
		clear();
		for (const_iterator itr = rhs.begin(); itr != rhs.end(); ++itr)
			push_back(*itr);
		return *this;
	}

	iterator begin() { return iterator(*this, head->next); }
	iterator end() { return iterator(*this, tail); }
	const_iterator begin() const { return ++const_iterator(*this, head); }
	const_iterator end() const { return const_iterator(*this, tail); }

	int size() const { return theSize; }
	bool empty() const { return size() == 0; }
	void clear() { while (!empty()) pop_front(); }

	Object& front() { return *begin(); }
	Object& back() { return *--end(); }
	const Object& front() const { return *begin(); }
	const Object& back() const { return *--end(); }

	void push_front(const Object& x) { insert(begin(), x); }
	void push_back(const Object& x) { insert(end(), x); }
	void pop_front() { erase(begin()); }
	void pop_back() { erase(--end()); }

	//Insert x before itr.
	iterator insert(iterator itr, const Object& x)
	{
		itr.assertIsValid();
		itr.assertIsinList(this);

		Node* p = itr.current;
		theSize++;
		return iterator(*this,
			p->prev = p->prev->next = new Node(x, p->prev, p));
	}
	iterator erase(iterator itr)
	{
		itr.assertIsValid();
		itr.assertIsinList(this);

		Node* p = itr.current;
		iterator retVal(*this, p->next);
		p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p;
		theSize--;

		return retVal;//返回删除结点的后继结点
	}
	iterator erase(iterator start, iterator end)
	{
		start.assertIsValid();
		end.assertIsValid();
		start.assertIsinList(this);
		end.assertIsinList(this);

		for (iterator itr = start; itr != end;)
			itr = erase(itr);
		return end;
	}


private:
	int theSize;
	Node* head;
	Node* tail;

	void init()
	{
		theSize = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
	}
};//class List