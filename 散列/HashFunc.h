#pragma once
#include<string>
using namespace std;

//通常，键是字符串；在这种情况下，散列函数需要仔细选择


//一种方法是把字符串中字符的ASCII码值加起来，代码如下：
int hash1(const string& key, int tableSize)
{
	int hashVal = 0;

	for (int i = 0; i < key.length(); i++)
		hashVal += key[i];

	return hashVal % tableSize;
}

//假设Key至少有三个字符，27表示英文字母表的字母个数加一个空格。729是27的平方
//该函数只考察前三个字符
int hash2(const string& key, int tableSize)
{
	return (key[0] + 27 * key[1] + 729 * key[2]) % tableSize;
}

//A hash routine for string objects
int hash3(const string& key, int tableSize)
{
	int hashVal = 0;

	for (int i = 0; i < key.length(); i++)
		hashVal = 37 * hashVal + key[i];

	hashVal %= tableSize;
	if (hashVal < 0)hashVal += tableSize;

	return hashVal
}