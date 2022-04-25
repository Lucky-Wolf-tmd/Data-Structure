#include"IntCell.h"
#include<iostream>  
#include<vector>
#include<string>
#include<stdlib.h>  //rand() srand()
#include<ctime>     //time()
#include<functional>//less<>

using namespace std;
//1
//类的接口与实现
void test_IntCell()
{
	IntCell m;//Or, IntCell m(0); but not IntCell m();

	m.writeST(5);
	cout << " Cell contents: " << m.readST() << endl;

}

//2
//vector的使用
void test_vector()
{
	vector<int> squares(100);

	for (int i = 0; i < squares.size(); i++)
		squares[i] = i * i;
	for (int i = 0; i < squares.size(); i++)
		cout << i << " " << squares[i] << endl;
	
}

 //3
//new 与 delete 示例
void test_ptr_DAM_IntCell()
{
	IntCell *m;
	m = new IntCell(0);
	//or m = new IntCell();//有零参构造函数
	//or m = new IntCell;  //有零参构造函数

	m->writeST(5);
	cout << " Cell contents: " << m->readST() << endl;

	delete m;
}

//4
//不同的传入参数会有不同的效果
namespace FINDMAX
{
	/*
	* 这个函数的返回值是安全的，因为外部传进来的arr的生命周期 会比该函数的生命周期长
	* 所以返回其引用是可以控制的
	*/
	const string& sfindMax(const vector<string>& arr)
	{
		int maxIndex = 0;
		for (int i = 0; i < arr.size(); i++)
			if (arr[maxIndex] < arr[i])
				maxIndex = i;

		return arr[maxIndex];
	}

	/*
	* 这个函数的返回值是危险的，错误的，
	* 因为返回的是局部变量的引用，
	* 当该函数调用结束，局部变量会由编译器释放，至于何时释放取决于编译器
	* 释放之后的变量为空，则导致返回值在程序的某一个时刻成为了空引用
	* 这是禁止的。
	*/
	const string& sfindMaxWrong(const vector<string>& arr)
	{
		string maxValue = arr[0];
		for (int i = 0; i < arr.size(); i++)
			if (maxValue < arr[i])
				maxValue = arr[i];

		return maxValue;// warn
	}
}
void test_findmax()
{
	vector<string> arr = { "b","c","k","j","r","z","a" };
	cout << FINDMAX::sfindMax(arr) << endl;
	//cout << FINDMAX::sfindMaxWrong(arr) << endl;//造成调试错误（或者未发现，那将更加危险）
}

//5
//深复制与浅复制
void test_DS_copy()
{
	IntCell Acell(10,10);
	IntCell Bcell(Acell);
	IntCell Ccell = Acell;

	cout << "*(Acell.ptr) = " << Acell.readptr() << endl;
	cout << "*(Bcell.ptr) = " << Bcell.readptr() << endl;
	cout << "*(Ccell.ptr) = " << Ccell.readptr() << endl;
	cout << "Acell.ptr    = " << Acell.readadr() << endl;
	cout << "Bcell.ptr    = " << Bcell.readadr() << endl;
	cout << "Ccell.ptr    = " << Ccell.readadr() << endl;
	Acell.writeptr(11);
	cout << "*(Acell.ptr) = " << Acell.readptr() << endl;
	cout << "*(Bcell.ptr) = " << Bcell.readptr() << endl;
	cout << "*(Ccell.ptr) = " << Ccell.readptr() << endl;

	
}

//6
//模板函数示例
namespace FINDMAX {
	/*
	* Return the maximum item in array A.
	* Assumes A.size() > 0.
	* Comparable objects must provide operator< and operator=
	*/
#define rando (rand()%(i+1))

	template<typename T>
	const T& FindMax(const vector<T>& A)
	{
		int maxIndex = 0;
		for (int i = 0; i < A.size(); i++)
			if (A[maxIndex] < A[i])
				maxIndex = i;
		return A[maxIndex];
	}

	template<typename T>
	void fillfull(vector<T>& A)
	{
		for (int i = 0; i < A.size(); i++)
			A[i] = rando;
	}
	template<>
	void fillfull(vector<IntCell>& A)
	{
		for (int i = 0; i < A.size(); i++)
			A[i] =(IntCell(rando, rando));
	}
}
void test_templateFunc()
{
	vector<int>       v1(37);
	vector<double>    v2(40);
	vector<string>    v3(80);
	vector<IntCell>   v4(75);

	// Addtional code to fill in the vector not shown.
	//自己随便写了个模板来填满容器
	FINDMAX::fillfull(v1);
	FINDMAX::fillfull(v2);
	FINDMAX::fillfull(v3);
	FINDMAX::fillfull(v4);

	cout << FINDMAX::FindMax(v1) << "\t"; //OK: Comparable = int
	cout << FINDMAX::FindMax(v2) << "\t"; //OK: Comparable = double
	cout << FINDMAX::FindMax(v3) << "\t"; //OK: Comparable = string
	cout << FINDMAX::FindMax(v4).readST() << "\t"; // Illegal: opearator< undefined
	cout << endl;

}

//7
//模板类示例
namespace MC {
	/*
	* A template class for simulating memory cell
	*/
	template<typename T>
	class MemoryCell
	{
	public:
		explicit MemoryCell (const T & initialValue = T()) :storedValue(initialValue) {}	
		const T& read() const { return storedValue; }
		void write(const T& x) { storedValue = x; }
	private:
		T storedValue;
	};
}
void test_templateClass() {
	MC::MemoryCell<int>    m1;
	MC::MemoryCell<string> m2("hello");

	m1.write(37);
	m2.write(m2.read() + "world");
	cout << m1.read() << endl;
	cout << m2.read() << endl;
}

//8
//可以Compare的类类型
namespace COMPARE {
	class Employee
	{
	public:
		void setValue(const string& n, double s) { name = n; salary = s; }
		void print(ostream& out)const { out << name << " (" << salary << ")"; }
		bool operator<(const Employee& rhs)const { return salary < rhs.salary; }

		//Other general accessors and mutators, not shown
		//Mutators
		explicit Employee(const string& n = "*NULL*", double s = 0) :name(n), salary(s) {};
		~Employee(){}
		Employee(const Employee& rhs) { name = rhs.name; salary = rhs.salary; }
		const Employee& operator=(const Employee& rhs)
		{name = rhs.name; salary = rhs.salary; return *this; }
		//Accessors
		const string& getName() const { return name; }
		double getSalary() const { return salary; }
		void modifyName(const string& xname) { name = xname; }
		void modifySalary(double xsalary) { salary = xsalary; }
	private:
		string name;
		double salary;
	};
}
void test_comparable_class() {
	vector<COMPARE::Employee> v(4);
	v[0].setValue("George Bush", 400000.00);
	v[1].setValue("Bill Gates", 2000000000.00);
	v[3].setValue("Dr.Phil", 13000000.00);
	cout << FINDMAX::FindMax(v).getSalary() << endl;
}

//9
//泛型类型函数对象（函数作参数）
namespace FINDMAX {
	//Generic findMax,with a function object, Version #1.
	//Precondition: a.size() > 0;
	template<typename Object,typename Comparator>
	const Object& GfindMax(const vector<Object>& arr, Comparator cmp)
	{
		int maxIndex = 0;
		for (int i = 1; i < arr.size(); i++)
			if (cmp.isLessThan(arr[maxIndex], arr[i]))
				maxIndex = i;
		return arr[maxIndex];
	}
	class CaseInsensitiveCompare
	{
	public:bool isLessThan(const string& lhs, const string& rhs) const
	{return _stricmp(lhs.c_str(), rhs.c_str()) < 0;}
	};
}
void test_generic_func()
{
	vector<string>arr(3);
	arr[0] = "ZEBRA";
	arr[1] = "alligator";
	arr[2] = "crocodile";
	cout << FINDMAX::GfindMax(arr, FINDMAX::CaseInsensitiveCompare()) << endl;
}

//10
//更典型的C++泛型类型编程
namespace FINDMAX {
	//Generic findMax, with a function object, C++ style.
	//Precondition: a.size() > 0.
	template<typename Object,typename Comparator>
	const Object& CfindMax(const vector<Object>& arr, Comparator isLessThan)
	{
		int maxIndex = 0;
		for(int i = 1;i<arr.size();i++)
			if(isLessThan(arr[maxIndex], arr[i]))
			maxIndex = i;
		return arr[maxIndex];
	}

	//Generic findMax, using default ordering.
	template<typename Object>
	const Object& CfindMax(const vector<Object>& arr)
	{
		return CfindMax(arr, less<Object>());
	}
	class CaseInsensitiveCompareC
	{
	public:
		bool operator()(const string& lhs, const string& rhs)const
		{return _stricmp(lhs.c_str(), rhs.c_str()) < 0;}
	};
}
void test_More_CPP_GFunc() {
	vector<string>arr(3);
	arr[0] = "ZEBRA";
	arr[1] = "alligator";
	arr[2] = "crocodile";
	cout << FINDMAX::CfindMax(arr, FINDMAX::CaseInsensitiveCompareC()) << endl;
	cout << FINDMAX::CfindMax(arr) << endl;
}

//matrix的[]重载及使用
namespace MATRIX {
	template<typename Object>
	class matrix
	{
	public:
		matrix(int rows, int cols) :array(rows)
		{
			for (int i = 0; i < rows; i++)
				array[i].resize(cols);
		}

		const vector<Object> & operator [](int row)const
		{	return array[row];	}
		vector<Object> & operator[](int row)
		{	return array[row];	}

		int numrows()const { return array.size(); }
		int numcols()const { return (numrows() ? array[0].size() : 0); }

	private:
		vector<vector<Object>>array;
	};
}
void test_matrix(){
	MATRIX::matrix<IntCell> MatrixCell(5, 5);
	for (int i = 0; i < MatrixCell.numrows(); i++)
		FINDMAX::fillfull(MatrixCell[i]);

	for (int i = 0; i < MatrixCell.numrows(); i++) {
		for (int j = 0; j < MatrixCell.numcols(); j++)
			cout << MatrixCell[i][j].readST() << "\t";
		cout << endl;
	}
	cout << "*************************************" << endl;
	for (int i = 0; i < MatrixCell.numrows(); i++) {
		for (int j = 0; j < MatrixCell.numcols(); j++)
			MatrixCell[i][j] = MatrixCell[j][i];
	}
	for (int i = 0; i < MatrixCell.numrows(); i++) {
		for (int j = 0; j < MatrixCell.numcols(); j++)
			cout << MatrixCell[i][j].readST() << "\t";
		cout << endl;
	}

}

void choose_test(int index) {
	switch (index)
	{
	case 1:test_IntCell();									 break;
	case 2:test_vector();									 break;
	case 3:test_ptr_DAM_IntCell();							 break;
	case 4:test_findmax();									 break;
	case 5:test_DS_copy();									 break;
	case 6:for (int i = 0; i < 10; i++) test_templateFunc(); break;
	case 7:test_templateClass();							 break;
	case 8:test_comparable_class();							 break;
	case 9:test_generic_func();								 break;
	case 10:test_More_CPP_GFunc();							 break;
	case 11:test_matrix();									 break;
	default:break;
	}
}
int main()
{
	srand((unsigned)time(0));
	choose_test(11);

	return 0;
}