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
		int height = -1;

		void updateHeight()
		{
			height = std::max(getHeight_(left), getHeight_(right)) + 1;
		}

		int getHeight_(Node* node)
		{
			return (nullptr == node) ? 0 : node->height;
		}

		Node& operator=(const Node& rhs)
		{
			this->data = rhs.data;
			this->right = rhs.right;
			this->left = rhs.left;

			return *this;
		}
	};

	BinaryTree();
	
	~BinaryTree();

	void addNode(int val);

	bool search(int key);

	bool remove(int key);

	int getDepth();

	void printInorder();

	void printPreorder();

	void printPostorder();

	void Print();

private:
	void addNode_(int val, Node*& node);

	bool search_(Node*& node, int key);

	bool remove_(Node*& node, int key);
	
	int getHeight(Node* node);

	void smoothing_(Node*& node);

	void rotate_(Node*& node);

	void Rightrotate2_(Node*& node);

	void Rightrotate_(Node*& node);

	void Leftrotate2_(Node*& node);

	void Leftrotate_(Node*& node);

	void RightLeftrotate_(Node*& node);

	void LeftRightrotate_(Node*& node);

	int getDepth_(Node* node);

	int getHeight_(Node* node);

	void printInorder_(Node* Node);
	
	void printPreorder_(Node* Node);
	
	void printPostorder_(Node* Node);

	void PrintLayer_(int depth, Node* node);

	Node* m_root;
};

