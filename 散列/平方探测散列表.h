#pragma once
#include<vector>
using namespace std;

/*
* ��ʹ�������ɢ�б�
* ���������ͻ��������һ����Ԫ��
* ���Ե�Ԫ�� h[0](x),h[1](x),h[2](x) ....���γ���
* h[i](x) = ( hash(x) + f(i) ) mod TableSize �� f(0) = 0
* ����f�ǳ�ͻ�������
* һ����˵���Բ�ʹ�÷������ӷ���ɢ�б���˵������װ����Ӧ�õ��ڦ�=0.5
* ���ǳ������ı�Ϊ ̽��ɢ�б� (probing hash tables)
* ���濼�����ֳ����Ľ����ͻ����
*/

/* ����̽�� */
/*
* ������̽���У�����f��i�����Ժ�����һ�������f(i) = i.
* �ڶ�γ�ͻ����֮�󣬼�ʱ����ԽϿգ�Ҳ���γ� һ�ξۼ� (primary clustering)
* �˺�ɢ�е������е��κμ�����Ҫ�����ѡ��Ԫ���ܹ������ͻ��Ȼ��ü��ű���ӵ���Ӧ�����С�
* 
* ���ԣ�
* ������ж���һ�뱻�����Ļ�����ô����̽��Ͳ��Ǹ��ð취��
* Ȼ���������=0.5����ô�������ƽ��ֻ��Ҫ2.5��̽�⣬���Ҷ��ڳɹ����ҵ�ƽ��ֻ��Ҫ1.5��̽��
*/


/* ƽ��̽�� */
/*
* ƽ��̽��ĳ�ͻ����Ϊ���κ���������ѡ���� f(i) = i^2
* ��Ȼ ƽ��̽�� �ų��� һ�ξۼ�������ɢ�е�ͬһλ���ϵ�Ԫ�ؽ�̽����ͬ�ı�ѡ��Ԫ��
* ���Ϊ���ξۼ���ģ����ָ������ÿ�β��ң���һ��Ҫ������������һ���̽�⡣
* 
* ���ԣ�
* ���ʹ��ƽ��̽�⣬�ұ�Ĵ�С����������ô����������һ���ǿյ�ʱ�����ܹ�����һ����Ԫ�ء�
* ������±��б�һ���һ����λ�ñ���������ô���붼�п���ʧ�ܣ���ʱ���ֿ����Ժ�С��
* ���⣬��Ĵ�С������Ҳ�ǳ���Ҫ�������Ĵ�С������������ѡ��Ԫ�������ܻ����
*/

/* ˫ɢ��(double hashing) */
/*
* ����˫ɢ�У�һ�����е�ѡ����f(i) = i*hash[2](x)
* �����ʽ����˼�ǣ����ڶ���ɢ�к���Ӧ�õ�x ���ھ���hash[2](x),2hash[2](x) ...�ȴ�̽��
* hash[2](x)ѡ��ò��ý���ǳ���⡣
* ���⣬��֤���е�Ԫ���ܱ�̽�⵽Ҳ����Ҫ�����ұ�Ĵ�СҪ��������
* ���� hash[2](x) = R - (x mod R)�����ĺ����������õ����ã�����R��С��TableSize������
* 
* ���ԣ�
* ��� ˫ɢ����ȷʵ�֣�ģ�������Ԥ�ڵ�̽����������������ͻ���������������ͬ
* ��ʹ��˫ɢ���������Ϻ�����������
* ������ƽ��̽�ⲻ��Ҫʹ�õڶ���ɢ�к������Ӷ���ʵ���п��ܸ��򵥲��Ҹ��졣
* ����Ϊ�ַ���ʱ��������ˣ���Ϊ��ɢ�к����ļ���ܺ�ʱ��
*/

/*
* ��ɢ�� ������ƽ��̽���Զ��ַ���ʵ�֡�
* һ��������ֻҪ������һ�����ɢ�С�
* ��һ�ּ��˷�����ֻ�е�����ʧ��ʱ����ɢ��
* �����ַ�����;�в��ԣ�����ﵽĳһ����װ����ʱ������ɢ�С�
* ����������װ���ӵ����ӣ�������ܵ�ȷ���½�����ˣ�����õĽ�ֹ��ʵ�ֵ����ֲ���
* ��������õĲ���
*/

template<typename HashedObj>
class HashTable
{
public:
	explicit HashTable(int size = 101):array(nextPrime(size))
	{	makeEmpty();}

	bool contains(const HashedObj& x)const {
		return isActive(findPos(x));
	}
	

	void makeEmpty()
	{
		currentSize = 0;
		for (int i = 0; i < array.size(); i++)array[i].info = EMPTY;
	}
	bool insert(const HashedObj& x);
	bool remove(const HashedObj& x);

	enum EntryType(ACTIVE, EMPTY, DELETED);

private:
	struct HashEntry
	{
		HashedObj element;
		EntryType info;

		HashEntry(const HashedObj & e = HashedObj(),EntryType i = EMPTY)
			:element(e),info(i){}
	};

	vector<HashEntry> array;

	int findPos(const HashedObj& x)const
	{
		int offset = 1;
		int currentPos = myhash(x);

		while (array[currentPos].info != EMPTY &&
			array[currentPos].element != x)
		{
			currentPos += offset;  //Compute ith probe
			offset += 2;
			if (currentPos >= array.size())
				currentPos -= array.size();
		}
	}
	bool isActive(int currentPos)const {
		return array[currentPos].info == ACTIVE;
	}
	void rehash() 
	{
		vector<HashEntry> oldArray = array;

		//Create new double-sized, empty table
		array.resize(nextPrime(2 * oldArray.size()));
	}

	int myhash(const HashedObj& x)const;
};