#include "RedBlackTree.h"

void RedBlackTree::Insert(int val)
{
	NewNodeChecker(Insert_(val, m_root));
	m_root->color = Color::BLACK;
}

RedBlackTree::Node* RedBlackTree::Insert_(int val, Node* parent)
{
	if (nullptr == parent)
	{
		m_root = new Node(val,Color::BLACK, parent);
		return m_root;
	}
	if (parent->value > val)
	{
		if (nullptr != parent->left)
		{
			return Insert_(val, parent->left);
		}
		else
		{
			parent->left = new Node(val, Color::RED, parent);
			return parent->left;
		}
	}
	else
	{
		if (nullptr != parent->right)
		{
			return Insert_(val, parent->right);
		}
		else
		{
			parent->right = new Node(val, Color::RED, parent);
			return parent->right;
		}
	}
}

void RedBlackTree::NewNodeChecker(Node* newNode)
{
	if (nullptr == newNode->parent  || Color::BLACK == newNode->parent->color)
	{
		return;
	}
	else
	{
		Node* newNodePar = newNode->parent;
		Node* newNodeGPar = newNode->parent->parent;
		Node* newNodeUncle = (newNodeGPar->left == newNodePar) ? newNodeGPar->right : newNodeGPar->left;
		if (nullptr != newNodeUncle && Color::RED == newNodeUncle->color)
		{
			newNodePar->color = Color::BLACK;
			newNodeUncle->color = Color::BLACK;
			newNodeGPar->color = Color::RED;
			NewNodeChecker(newNodeGPar);
		}
		else
		{
			if (newNode == newNodePar->right && newNodePar == newNodeGPar->right)
			{
				RightRightRotation(newNodeGPar);
			}
			else if (newNode == newNodePar->left && newNodePar == newNodeGPar->left)
			{
				LeftLeftRotation(newNodeGPar);
			}
			else if (newNode == newNodePar->left && newNodePar == newNodeGPar->right)
			{
				LeftRightRotation(newNodeGPar);
			}
			else if (newNode == newNodePar->right && newNodePar == newNodeGPar->left)
			{
				RightLeftRotation(newNodeGPar);
			}
		}
	}
}

void RedBlackTree::RightRightRotation(Node* oldRoot)
{
	Node* newRoot = oldRoot->right;

	newRoot->parent = oldRoot->parent;
	oldRoot->right = newRoot->left;
	newRoot->left = oldRoot;
	oldRoot->parent = newRoot;
	std::swap(newRoot->color, oldRoot->color);

	if (nullptr == newRoot->parent)
	{
		m_root = newRoot;
	}
	else
	{
		if (newRoot->parent->right == oldRoot)
		{
			newRoot->parent->right = newRoot;
		}
		else
		{
			newRoot->parent->left = newRoot;
		}
	}
}

void RedBlackTree::LeftLeftRotation(Node* oldRoot)
{
	Node* newRoot = oldRoot->left;

	newRoot->parent = oldRoot->parent;
	oldRoot->left = newRoot->right;
	newRoot->right = oldRoot;
	oldRoot->parent = newRoot;
	std::swap(newRoot->color, oldRoot->color);

	if (nullptr == newRoot->parent)
	{
		m_root = newRoot;
	}
	else
	{
		if (newRoot->parent->left == oldRoot)
		{
			newRoot->parent->left = newRoot;
		}
		else
		{
			newRoot->parent->right = newRoot;
		}
	}
	
}

void RedBlackTree::LeftRightRotation(Node* oldRoot)
{
	LeftLeftRotation(oldRoot->right);
	RightRightRotation(oldRoot);
}

void RedBlackTree::RightLeftRotation(Node* oldRoot)
{
	RightRightRotation(oldRoot->left);
	LeftLeftRotation(oldRoot);
}

RedBlackTree::RedBlackTree()
{
	m_root = nullptr;
}

RedBlackTree::~RedBlackTree()
{

}


void RedBlackTree::Print()
{
	int maxDepth = getDepth_(m_root);
	for (int curDepth = 1; curDepth < maxDepth + 1; ++curDepth)
	{
		PrintLayer_(curDepth, m_root);
	}
}

int RedBlackTree::getDepth_(Node* node)
{
	if (nullptr == node)
	{
		return 0;
	}

	int rDepth = getDepth_(node->right) + 1;
	int lDepth = getDepth_(node->left) + 1;

	return (rDepth > lDepth) ? rDepth : lDepth;
}

int RedBlackTree::getBlackDepth_(Node* node)
{
	if (nullptr == node)
	{
		return 1;
	}

	int rDepth = getBlackDepth_(node->right) + (node->color == Color::BLACK) ? 1 : 0;
	int lDepth = getBlackDepth_(node->left) + (node->color == Color::BLACK) ? 1 : 0;

	return (rDepth > lDepth) ? rDepth : lDepth;

}

int RedBlackTree::getBlackDepthreverse_(Node* node)
{
	if (nullptr == node)
	{
		return 1;
	}

	int rDepth = getBlackDepthreverse_(node->right) + (node->color == Color::BLACK)? 1 : 0;
	int lDepth = getBlackDepthreverse_(node->left) + (node->color == Color::BLACK) ? 1 : 0;

	return (rDepth < lDepth) ? rDepth : lDepth;
}

void RedBlackTree::PrintLayer_(int depth, Node* node)
{
	int curNodeNum = 0;
	int end = (int)pow(2, depth - 1);
	Node* tmpNode = node;
	int tmpNumber = curNodeNum;
	int counter = depth - 1;
	int mod = (int)pow(2, depth - 2);

	while (curNodeNum < end)
	{
		tmpNode = node;
		tmpNumber = curNodeNum;
		counter = depth - 1;
		while (counter && tmpNode != nullptr)
		{
			tmpNode = (tmpNumber & mod) ? tmpNode->right : tmpNode->left;
			tmpNumber = tmpNumber << 1;
			--counter;
		}

		if (tmpNode == nullptr)
		{
			//std::cout << "*" << "(0)" << " ";
			std::cout << "*" << " ";
		}
		else
		{
			char c = (tmpNode->color == Color::RED) ? 'R' : 'B';
			std::cout << tmpNode->value << "(" << c << ")" << " ";
			//std::cout << tmpNode->value << " ";
		}
		++curNodeNum;
	}
	std::cout << std::endl;
}
