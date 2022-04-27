#include<list>
#include<vector>
#include<iostream>
#include<time.h>
#include"VECTOR.h"
#include"LIST.h"
#include"STACK.h"
#include<string>
using namespace std;
namespace LAB {
	const int MAXSIZE = 100000;
	template<typename Container>
	void removeEveryOtherItem(Container& lst)
	{
		typename Container::iterator it = lst.begin();
		while (it != lst.end())
		{
			it = lst.erase(it);
			if (it != lst.end())
				++it;
		}
	}

	template<typename Container, typename Object>
	void change(Container& c, const Object& newvalue)
	{
		typename Container::iterator it = c.begin();
		while (it != c.end())
			*it++ = newvalue;
	}

#if 0
	template<typename Container>
	void print(const Container& lst, ostream& out = cout)
	{//注意这里是const Container 
		typename Container::iterator it = lst.begin();
		int i = 0;
		while (it != lst.end())
		{
			//*it = 0;  //This is fishy !!! //与const目的相背,编译器报错
			out << *it << " ";
			it++;
		}
	}
#endif

	template<typename Container>
	void printCollection(const Container& c, ostream& out = cout)
	{
		if (c.empty())
			out << "(empty)";
		else
		{
			typename Container::const_iterator itr = c.begin();
			out << "[ " << *itr++;    //Print first item
			while (itr != c.end())
				out << "," << *itr++;
			out << " ]" << endl;
		}
	}
}
void test_LAB() {
	using namespace LAB;
	vector<int> vec;
	list<int> lst;
	clock_t start, end;

	for (int i = 0; i < MAXSIZE; i++)
	{
		vec.push_back(MAXSIZE - i);
		lst.push_back(MAXSIZE - i);
	}

	for (int i = 0; i < 2; i++)
	{
		cout << "Container " << (i ? "STL::list" : "STL::vector") << " erase time use: \t";
		start = clock();
		switch (i)
		{
		case 0:removeEveryOtherItem(vec); break;
		case 1:removeEveryOtherItem(lst); break;
		default:
			break;
		}
		end = clock();
		double T = (double)(end - start);
		cout << T << "ms" << endl;
	}

	printCollection(lst);//warning::there are 100000 elements in this container!
}

void test_VECTOR()
{
	Vector<int> a, b;
	auto ita = a.begin();
	b.push_back(*ita);
}

void test_outofbounds() {
	List<int> a;
	auto ita = ++a.end();
	a.insert(ita, 8);
	a.erase(ita);
	a.erase(a.begin(), ita);

}
void test_mismatch() {
	List<int>a, b;
	auto ita = a.begin();
	auto itb = b.begin();
	a.erase(itb);
}
void test_operator()
{
	List<int>a;
	a.push_back(1);
	List<int> b(a);
	ABORT((b.front() != 1), "== have not been override!");
}
void test_LIST() {
	//test_outofbounds();
	//test_mismatch();
	test_operator();
}

void test_Stack_list()
{
	Stack_list<int> a;
	a.push(998);
	ABORT((a.top() != 998), "Push Error!");
	ABORT((a.empty()), "Not Empty!");
	ABORT((a.size() != 1), "Size Error!");
	a.pop();
	ABORT((!a.empty()), "Is Empty!");

}
void test_Stack_vector() {
	Stack_vector<int> A;
	A.push(8);
	int b = A.pop();
	cout << b << endl;
}

//括号平衡
inline bool matchsign(char l, char r,Stack_list<char> & stack,char s) {
	if (s == r) {
		if (stack.top() == l)stack.pop();
		else {
			ABORT(1, "The brackets mismatched "); return 0;
		}
	}
	return 1;
}
bool balance_of_sign(const string & s) {
	Stack_list<char> stack;
	int i = 0;
	while (s[i] != '\0') {
		if ( s[i] == '{' || s[i] == '(' || s[i] == '[')
			stack.push(s[i]);
		matchsign('{', '}', stack, s[i]);
		matchsign('[', ']', stack, s[i]);
		matchsign('(', ')', stack, s[i]);
		i++;
	}
	if (stack.size() != 0) { 
		ABORT(1, " Brackets still have not been balanced");
		return 0; 
	}
	return 1;
}
void test_balance() {
	const char* right = "{这个}(因为)[有][[[中文]]][({所以是错的吧})]";
	const char* wrong2 = "{{[[(([[";
	const char* wrong = "{but[this(dont[have{chinese]character)so]maybe]right)";
	balance_of_sign(right);
	balance_of_sign(wrong);
	balance_of_sign(wrong2);
}

double mypow(double x, int n)
{
	if (n == 0)
		return 1;
	if (n % 2 == 0)
		return mypow(x * x, n / 2);
	else
		return mypow(x * x, n / 2) * x;
}

//后缀表达式计算,逆波兰记法（reverse Polish notation）
inline bool IsDigit( char s) {
	if (s <= '9' && s>='0')
		return 1;
	return 0;
}
double postfix(const string & str) {
	balance_of_sign(str);
	Stack_list<char> A;
	Stack_list<char> temp;
	Stack_list<double> numlist;
	string num;
	int i = 0;
	while (str[i] != '\0') {
		if (IsDigit(str[i])||str[i]=='.') { 
			A.push(str[i]);
		}
		else {
			while (IsDigit(A.top())||A.top()=='.') {
				temp.push(A.pop());
			}
			while (!temp.empty()) {
				num += temp.pop();
			}
			if(!num.empty())
			numlist.push(stod(num));
			num.clear();
		}
		if (str[i] == '*') {
			numlist.push(numlist.pop() * numlist.pop());
		}
		else if (str[i] == '/') {
			double dvd = numlist.pop();
			numlist.push(numlist.pop()/ dvd);
		}
		else if (str[i] == '+') {
			numlist.push(numlist.pop() + numlist.pop());
		}
		else if (str[i] == '-') {
			double dvd = numlist.pop();
			numlist.push(numlist.pop() - dvd);
		}
		else if (str[i] == '^') {
			double dvd = numlist.pop();
			numlist.push(mypow(numlist.pop(), dvd));
		}
		i++;
	}
	return numlist.pop();
}
void test_postfix()
{
	cout<<postfix("6 5 2 3 + 8 * + 3 + *")<<endl;
	cout << postfix("4.99 1.06 * 5.99 + 6.99 1.06 * +") << endl;
}

//中缀表达式
double infix(const string& str)
{
	balance_of_sign(str);
	string A;
	Stack_vector<char> B;
	int i = 0;
	while (str[i] != '\0') {
		if (IsDigit(str[i]) || str[i] == '.') {
			A+=str[i];
		}
		else {
			if (B.empty()) {
				B.push(str[i]); 
				A += ' '; }
			else
			{
				if (str[i] == '(') {
					if (B.top()!='(') {
						auto x =  B.pop();
						if (B.top() != '('&&A.empty()) { A += x; A += ' '; }
						else B.push(x);
						
					}
					B.push(str[i]);	
				}
				else if (str[i] == '*' || str[i] == '/') {
					A += ' ';
					if (B.top() == '*' || B.top() == '/'||B.top()=='^') { 
						A += B.pop();
						A += ' ';
					}
					B.push(str[i]);
				}
				else if (str[i] == '+' || str[i] == '-') {
					A += ' ';
					if (B.top() != '(') {
						A += B.pop();
						A += ' ';
					}
					B.push(str[i]);
				}
				else if (str[i] == '^') {
					A += ' ';
					if (B.top() == '^') {
						A += B.pop(); A += ' ';
					}
					B.push(str[i]);
				}
				else if (str[i] == ')') {
					while (B.top() != '(') {
						A += ' ';
						A += B.pop();
					}
					B.pop();
				}
			}
		}
		i++;
	}
	while (!B.empty()) {
		A += B.pop(); A += ' ';
	}
	return postfix(A);
}
void test_infix() {
	cout << infix("1+2*3+(4*5+6)*7") << endl;
	cout << infix("(((6+9)*(8+7)-8)/6)+(2-4)") << endl;
	cout << infix("68894-878652") << endl;
	cout << infix("3^(2^2)") << endl;
	//cout << postfix("1 2 3 * 4 5 * 6 + 7*++") << endl;
	//cout << postfix("1 2 3 * + 4 5 * 6 + 7 * +") << endl;
}

int main()
{
	//test_LAB();
	//test_VECTOR();
	//test_LIST();
	//test_Stack_list();
	//test_balance();
	//test_Stack_vector();
	//test_postfix();
	test_infix();
	return 0;
}