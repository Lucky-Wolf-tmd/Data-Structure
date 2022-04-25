//����������Ļʺ��������кϷ�����
/*
* ����һ���Ĳ�����ÿ�����ն˽ڵ�ȶ�Ϊ4��������ÿ���ڵ��ʾһ���ֲ����ֻ�����������
* ���ڵ��ʾ���̵ĳ�ʶ״̬�����������κ�����
* ÿ���ʺ����ĸ���ѡλ�ã������κ�ʱ�̣����̵ĺϷ����ֱ�������һ������Լ��
* 1.�κ��������Ӷ���ռ�����̵�ͬһ��
* 2.�κ��������Ӷ���ռ�����̵�ͬһ��
* 3.�κ��������Ӷ���ռ�����̵�ͬһ�Խ���
* 
* �����кϷ����ֵĹ��̼�Ϊ������Լ�������£��������״̬���Ĺ��̡�
* �����з��ʽڵ�Ĳ���Ϊ���б��������Ƿ��Ѿ��õ�һ���������֣����������Ƿ��Ѿ�����4�����ӣ�
* ���ǣ�������ò��֣��������������������Լ�������ĸ���������
* �����жϸ������Ĳ����Ƿ�Ϸ�
* ���Ϸ�������������������������ȥ��������֧
*/

#include<iostream>
using namespace std;

class Backtracking
{
private:
	int* C;//�������λ�õ�����
	int n;//n*n������
	int count;//��ĸ���
public:
	Backtracking() { n = 4; C = new int[n]; count = 0; }
	void Trial(int i);//trial����
	void Print();//������̵�ǰ�Ĳ���
	int Check(int i);//��鵱ǰ�����Ƿ�Ϸ�
};

void Backtracking::Trial(int i)
{
	if (i == n)
		Print();
	else
	{
		for (int j = 0; j < n; j++)//�������״̬��,�ӿռ���ʼ����
		{
			C[i] = j;//C[i]�Ŀ���ֵΪ 0��1��2��3
			if (Check(i))//��ǰ���ֺϷ�
				Trial(i + 1);
		}
	}
}

int Backtracking::Check(int i)
{
	for (int j = 0; j < i; j++)
	{
		if (C[i] == C[j] || i - C[i] == j - C[j] || i + C[i] == j + C[j])
			return 0;
	}
	return 1;
}

void Backtracking::Print()
{
	cout << "��" << ++count << endl;
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (j == C[i])//j����
				cout << "*";
			else
				cout << "-";
		}
		cout << endl;//����i����
	}
}

int main()
{
	Backtracking T;
	T.Trial(0);
	return 0;
}