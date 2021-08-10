#include "RedBlackTree.h"

void FillRandomNumber(RedBlackTree& tree, int treeSize)
{
	for (int i = 0; i < treeSize; ++i)
	{
		tree.Insert(rand() % 100);
	}
}

int main()
{
	RedBlackTree tree;

	tree.Insert(50);
	tree.Insert(40);
	tree.Insert(30);
	tree.Insert(60);
	tree.Insert(55);
	tree.Insert(45);
	tree.Insert(80);
	//tree.Insert(100);

	tree.Print();
}
