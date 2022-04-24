#ifndef _INTCELL_H_
#define _INTCELL_H_
enum {shallowcopy,deepcopy};
const int MODE = shallowcopy;
/*
*  A class for simulating an integer memory cell
*/
class IntCell
{
public:
	//在前面加入explicit防止隐式类型转换（比如直接使用=运算符来赋值该类）
	//使用初始化列表来初始化数据成员
	explicit IntCell(int initialValue = 0,int initialptr = 0);     
	int readST() const;    //在后面加上const后，成为只读函数，无法修改内部数据
	void writeST(int x);

	//三大函数
	~IntCell();
	IntCell(const IntCell& rhs);
	const IntCell& operator=(const IntCell& rhs);

	bool operator<(const IntCell& rhs) const;

	//API
	int readptr() const { return *ptr; }
	void writeptr(int ptrx) { *ptr = ptrx; }
	int* readadr() const { return ptr; }

private:
	int storedValue;
	int* ptr;
};
#endif // ! _INTCELL_H_