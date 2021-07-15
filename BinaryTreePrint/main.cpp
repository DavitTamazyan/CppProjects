#include"BinaryTree.h"

int main()
{
	BinaryTree tree;
	BinaryTree::Node* root = tree.getRoot();
	root->data = 1;
	root->right = new BinaryTree::Node;
	root->right->data = 3;
	root->left = new BinaryTree::Node;
	root->left->data = 2;
	root->left->left = new BinaryTree::Node;
	root->left->left->data = 4;
	root->left->right= new BinaryTree::Node;
	root->left->right->data= 5;

	tree.printPostorder();
	std::cout << std::endl;
	tree.printPreorder();
	std::cout << std::endl;
	tree.printInorder();
}
