#pragma once
#include<iostream>

class RedBlackTree
{
public:
	enum class Color {RED , BLACK };
	struct Node
	{
		int value;
		Node* right;
		Node* left;
		Color color;
		Node* parent;
		Node(int val, Color col, Node* par)
		{
			value = val;
			right = nullptr;
			left = nullptr;
			color = col;
			parent = par;
		}
	};
public:
	RedBlackTree();
	~RedBlackTree();
	void Insert(int val);
	void Print();
	void Delete(int val);
private:
	/// internal implementation
	Node* Insert_(int val, Node* parent);
	void DeleteNode(Node* node);
	void NewNodeChecker(Node* newNode);
	/// Rotations
	void RightRightRotation(Node* oldRoot);
	void LeftLeftRotation(Node* oldRoot);
	void LeftRightRotation(Node* oldRoot);
	void RightLeftRotation(Node* oldRoot);
	/// Debug
	int getDepth_(Node* node);
	int getBlackDepth_(Node* node);
	int getBlackDepthreverse_(Node* node);
	void PrintLayer_(int depth, Node* node);
private:
	Node* m_root;
};

