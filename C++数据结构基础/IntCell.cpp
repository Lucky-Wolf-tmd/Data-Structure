#include"IntCell.h"

	/*
	* Construct the IntCell:
	* Initial value is 0.
	*/
	IntCell::IntCell(int initialValue,int initialptr)//��ʵ�ִ�������ǰ������explicit������Ҳ���ó�ʼ��
	:storedValue(initialValue)       //ʹ�ó�ʼ���б�����ʼ�����ݳ�Ա
	{
		ptr = new int(initialptr);
	}

	/*
	* Return the stored value.
	*/
	int IntCell::readST() const       //�ں������const�󣬳�Ϊֻ���������޷��޸��ڲ�����
	{ return storedValue; }

	/*
	* Change the stored value to x.
	*/
	void IntCell::writeST(int x)
	{ storedValue = x; }

	IntCell::IntCell(const IntCell & rhs)
	{
		this->storedValue = rhs.storedValue;
		if (MODE == shallowcopy)//ǳ����
			 this->ptr = rhs.ptr;
		else                    //���
			this->ptr = new int(*rhs.ptr);
	}
	const IntCell& IntCell::operator=(const IntCell& rhs)
	{
		if (this != &rhs)
		{
			storedValue = rhs.storedValue;
			if(MODE == shallowcopy)//ǳ����
				ptr = rhs.ptr;
			else                   //���
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
		if (MODE == shallowcopy)//ǳ����
			/* nothing to do */;
		else                    //���
			delete ptr;
	}


