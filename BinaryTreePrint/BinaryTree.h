#pragma once
#include<iostream>

class BinaryTree
{
public:
	struct Node
	{
		int data = 0;
		Node* left = nullptr;
		Node* right = nullptr;
	};

	BinaryTree();
	
	~BinaryTree();

	Node* getRoot();

	void printInorder();

	void printPreorder();

	void printPostorder();

private:
	void printInorder_(Node* Node);
	
	void printPreorder_(Node* Node);
	
	void printPostorder_(Node* Node);

	Node* m_root;
};

