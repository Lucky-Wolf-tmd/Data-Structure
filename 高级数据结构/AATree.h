#pragma once
/*
* BB���Ǵ���һ�����������ĺ������һ����������һ����ɫ�Ķ��ӡ�
* 
* ����Ϣ����һ��С�������У������ǰ���ɫλ��ÿ�����һ��洢
* �����Ϣ���ǽ��Ĳ�Σ�level����
* ���Ĳ�Σ�
* ���ý������Ҷ����level = 1��
* ���ý���Ǻ�ɫ�ģ���level�����丸����level
* ���ý���Ǻ�ɫ�ģ���level�����ĸ����level��1
*/

template<typename Comparable>
class AATree {
public:
	AATree() {
		nullNode = new AANode;
		nullNode->left = nullNode->right = nullNode;
		nullNode->level = 0;
		root = nullNode;
	}
private:
	struct AANode {
		Comparable element;
		AANode* left;
		AANode* right;
		int level;

		AANode():left(nullptr),right(nullptr),level(1){}
		AANode(cosnt Comparable& e,AANode*lt,AANode*rt,int lv=1)
			:element(e),left(lt),right(rt),level(lv){}
	};
};

/*
* Skew primitive for AA-trees
* t is the node that roots the tree.
*/
void skew(AANode*& t) {
	if (t->left->level == t->level) rotateWithLeftChild(t);
}

/*
* Split primitive for AA-trees.
* t is the node that roots the tree.
*/
void split(AANode*& t) {
	if (t->right->right->level == t->level) {
		rotateWithRightChild(t);
		t->level++;
	}
}

/*
* Internal method to insert into a subtree.
* x is the item to insert.
* t is the node that roots the tree.
* Set the new root of the subtree.
*/
void insert(const Comparable& x, AANode*& t)
{
	if (t == nullNode)
		t = new AANode(x, nullNode, nullNode);
	else if (x < t->element)
		insert(x, t->left);
	else if (t->element < x)
		insert(x, t->right);
	else return;  //Duplicate; do nothing

	skew(t);
	split(t);
}

/*
* Internal method to remove from a subtree.
* x is the item to remove.
* t is the node that roots the tree.
* Set the new root of the subtree.
*/
void remove(const Comparable& x, AANode*& t) {
	static AANode* lastNode, * deletedNode = nullNode;
	if (t != nullNode)
	{
		//Step1:Search down the tree and set lastNode and deletedNode
		lastNode = t;
		if (x < t->element)
			remove(x, t->left);
		else
		{
			deletedNode = t;
			remove(x, t->right);
		}

		//Step2: if at the bottom of the tree and x is present, we remove it.
		if (t == lastNode) {
			if (deletedNode == nullNode || x != deletedNode->element)return;//Item not found
			deletedNode->element = t->element;
			deletedNode = nullNode;
			t = t->right;
			delete lastNode;
		}

		//Step3: Otherwise,we are not at the bottom; rebalance 
		else
			if (t->left - level < t->level - 1 ||
				t->right->level < t->level - 1) {
				if (t->right->level > --t->level)
					t->right->level = t->level;
				skew(t);
				skew(t->right);
				skew(t->right->right);
				split(t);
				split(t->right);
			}
	}
}
