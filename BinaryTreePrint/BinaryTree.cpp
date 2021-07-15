#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
	m_root = new Node;
}

BinaryTree::~BinaryTree()
{
}

BinaryTree::Node* BinaryTree::getRoot()
{
	return m_root;
}

void BinaryTree::printInorder()
{
	printInorder_(getRoot());
}

void BinaryTree::printPreorder()
{
	printPreorder_(getRoot());
}

void BinaryTree::printPostorder()
{
	printPostorder_(getRoot());
}

void BinaryTree::printInorder_(Node* node)
{
	if (node == nullptr)
	{
		return;
	}

	printInorder_(node->left);

	std::cout << node->data << " ";
	
	printInorder_(node->right);
}

void BinaryTree::printPreorder_(Node* node)
{
	if (node == nullptr)
	{
		return;
	}

	std::cout << node->data << " ";

	printPreorder_(node->left);

	printPreorder_(node->right);
}

void BinaryTree::printPostorder_(Node* node)
{
	if (node == nullptr)
	{
		return;
	}

	printPostorder_(node->left);

	printPostorder_(node->right);

	std::cout << node->data << " ";
}