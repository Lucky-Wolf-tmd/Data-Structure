#include"BSTree.h"
#include<ctime>
#include<stdlib.h>
#include<Windows.h>
 void BSTree_test()
{
	srand(time(0));
	BSTree<int> T;
	for (int j = 0; j < 100; j++) {
		for (int i = 0; i < 10; i++) {
			T.insert(rand() % 100 + 1);
			T.printTree();	
			Sleep(500);
			system("cls");
		}
		for (int i = 0; i < 100; i++) {
			if(T.remove(rand() % 100 + 1))
			{
				T.printTree();
				Sleep(500);
				system("cls");
			}						
		}
	}
}
int main() {
	BSTree_test();
}