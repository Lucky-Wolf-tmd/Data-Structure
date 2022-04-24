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
	//��ǰ�����explicit��ֹ��ʽ����ת��������ֱ��ʹ��=���������ֵ���ࣩ
	//ʹ�ó�ʼ���б�����ʼ�����ݳ�Ա
	explicit IntCell(int initialValue = 0,int initialptr = 0);     
	int readST() const;    //�ں������const�󣬳�Ϊֻ���������޷��޸��ڲ�����
	void writeST(int x);

	//������
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