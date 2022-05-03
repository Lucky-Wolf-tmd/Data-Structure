#include"AVLTree.h"
int main()
{
	Node<int> N(1, nullptr, nullptr, 0);
	BalanceBiTree<int> A(&N);
	A.menu();

	return 0;

}