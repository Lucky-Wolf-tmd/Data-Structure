#pragma once
#include<string>
using namespace std;

//ͨ���������ַ���������������£�ɢ�к�����Ҫ��ϸѡ��


//һ�ַ����ǰ��ַ������ַ���ASCII��ֵ���������������£�
int hash1(const string& key, int tableSize)
{
	int hashVal = 0;

	for (int i = 0; i < key.length(); i++)
		hashVal += key[i];

	return hashVal % tableSize;
}

//����Key�����������ַ���27��ʾӢ����ĸ�����ĸ������һ���ո�729��27��ƽ��
//�ú���ֻ����ǰ�����ַ�
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