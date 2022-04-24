#include"IntCell.h"

	/*
	* Construct the IntCell:
	* Initial value is 0.
	*/
	IntCell::IntCell(int initialValue,int initialptr)//在实现处，函数前不得有explicit，参数也不得初始化
	:storedValue(initialValue)       //使用初始化列表来初始化数据成员
	{
		ptr = new int(initialptr);
	}

	/*
	* Return the stored value.
	*/
	int IntCell::readST() const       //在后面加上const后，成为只读函数，无法修改内部数据
	{ return storedValue; }

	/*
	* Change the stored value to x.
	*/
	void IntCell::writeST(int x)
	{ storedValue = x; }

	IntCell::IntCell(const IntCell & rhs)
	{
		this->storedValue = rhs.storedValue;
		if (MODE == shallowcopy)//浅复制
			 this->ptr = rhs.ptr;
		else                    //深复制
			this->ptr = new int(*rhs.ptr);
	}
	const IntCell& IntCell::operator=(const IntCell& rhs)
	{
		if (this != &rhs)
		{
			storedValue = rhs.storedValue;
			if(MODE == shallowcopy)//浅复制
				ptr = rhs.ptr;
			else                   //深复制
				*(this->ptr) = *rhs.ptr;
		}
		return *this;

	}
	bool IntCell::operator<(const IntCell& rhs) const
	{
		return this->storedValue < rhs.storedValue;
	}
	IntCell::~IntCell()
	{
		if (MODE == shallowcopy)//浅复制
			/* nothing to do */;
		else                    //深复制
			delete ptr;
	}


