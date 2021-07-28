#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
	m_root = nullptr;
}

BinaryTree::~BinaryTree()
{
}

void BinaryTree::addNode(int val)
{
	std::cout << "Adding element : " << val << std::endl;
	addNode_(val, m_root);
}

bool BinaryTree::search(int key)
{
	return search_(m_root, key);
}

bool BinaryTree::remove(int key)
{
	return remove_(m_root, key);
}

int BinaryTree::getDepth()
{
	return getDepth_(m_root);
}

void BinaryTree::printInorder()
{
	printInorder_(m_root);
}

void BinaryTree::printPreorder()
{
	printPreorder_(m_root);
}

void BinaryTree::printPostorder()
{
	printPostorder_(m_root);
}

void BinaryTree::Print()
{
	int maxDepth = getDepth();
	for (int curDepth = 1; curDepth < maxDepth + 1; ++curDepth)
	{
		PrintLayer_(curDepth, m_root);
	}
}

void BinaryTree::addNode_(int val, Node*& node)
{
	if (nullptr == node)
	{
		node = new Node();
		node->data = val;
		node->left = nullptr;
		node->right = nullptr;
		node->height = 1;
		return;
	}
	addNode_(val, (node->data > val) ? node->left : node->right);
	node->updateHeight();

	int balansFactor = getHeight_(node->left) - getHeight_(node->right); /// or it's not balanc factor :)

	if (balansFactor > 1 || balansFactor < -1)
	{
		rotate_(node);
	}
}

bool BinaryTree::remove_(Node*& node, int key)
{
	if (node == nullptr)
	{
		return false;
	}
	if (node->data == key)
	{
		smoothing_(node);
		return true;
	}
	if (key > node->data)
	{
		return remove_(node->right, key);
	}
	else
	{
		return remove_(node->left, key);
	}
}

int BinaryTree::getHeight(Node* node)
{
	return (nullptr == node) ? 1 : node->height;
}

void BinaryTree::smoothing_(Node*& node)
{
	if (nullptr != node->left)
	{
		node->data = node->left->data;
		smoothing_(node->left);
	}
	else
	{
		delete node;
		node = nullptr;
	}
}

bool BinaryTree::search_(Node*& node, int key)
{
	if (node == nullptr)
	{
		return false;
	}
	if (node->data == key)
	{
		return true;
	}
	if (key > node->data)
	{
		return search_(node->right, key);
	}
	else
	{
		return search_(node->left, key);
	}
}

int BinaryTree::getDepth_(Node* node)
{
	if (nullptr == node)
	{
		return 0;
	}

	int rDepth = getDepth_(node->right) + 1;
	int lDepth = getDepth_(node->left) + 1;
	
	return (rDepth > lDepth) ? rDepth : lDepth;
}

int BinaryTree::getHeight_(Node* node)
{
	return (nullptr == node) ? 0 : node->height;
}

void BinaryTree::rotate_(Node*& node)
{
	std::cout << "Called rotate" << std::endl;
	std::cout << "Before rotate" << std::endl;
	Print();
	std::cout << "               ||               " << std::endl;
	std::cout << "               \\/               " << std::endl;

	if (node->right != nullptr && node->left != nullptr)
	{
		if (node->right->height > node->left->height)
		{
			std::cout << "Right2 Rotate for element " << node->data << std::endl;
			Rightrotate2_(node);
		}
		else
		{
			std::cout << "Left2 Rotate for element " << node->data << std::endl;
			Leftrotate2_(node);
		}
		return;
	}

	if (node->right != nullptr && node->right->right != nullptr)
	{
		std::cout << "Right Rotate for element " << node->data << std::endl;
		Rightrotate_(node);
		return;
	}

	if (node->left != nullptr && node->left->left != nullptr)
	{
		std::cout << "Left Rotate for element " << node->data << std::endl;
		Leftrotate_(node);
		return;
	}

	if (node->right != nullptr && node->right->left != nullptr)
	{
		std::cout << "Right Left Rotate for element " << node->data << std::endl;
		RightLeftrotate_(node);
		return;
	}

	if (node->left != nullptr && node->left->right != nullptr)
	{
		std::cout << "Left Right Rotate for element " << node->data << std::endl;
		LeftRightrotate_(node);
		return;
	}
		std::cout << "NO Rotate" << std::endl;
}

void BinaryTree::Rightrotate2_(Node*& node)
{
	Node* tmp = node->right->left;
	Node* result = node->right;

	node->right->left = node;
	node = result;

	node->left->right = tmp;

	node->right->updateHeight();
	node->left->updateHeight();
	node->updateHeight();
}

void BinaryTree::Rightrotate_(Node*& node) /// need to optimize or change in left
{
	node->left = new Node();
	node->left->data = node->data;
	node->left->left = nullptr;
	node->left->right = nullptr;
	node->left->height = 1;
	
	node->data = node->right->data;
	Node* tmp = node->right->right;
	delete node->right;
	node->right = tmp;

	node->right->updateHeight();
	node->left->updateHeight();
	node->updateHeight();
}

void BinaryTree::Leftrotate2_(Node*& node)
{
	Node* tmp = node->left->right;
	Node* result = node->left;

	node->left->right = node;
	node = result;

	node->right->left = tmp;

	node->right->updateHeight();
	node->left->updateHeight();
	node->updateHeight();
}

void BinaryTree::Leftrotate_(Node*& node)
{
	node->right = new Node();
	node->right->data = node->data;
	node->right->right = nullptr;
	node->right->left = nullptr;
	node->right->height = 1;

	node->data = node->left->data;

	node->left->data = node->left->left->data;
	
	delete[] node->left->left;

	node->left->left = nullptr;

	node->right->updateHeight();
	node->left->updateHeight();
	node->updateHeight();
}

void BinaryTree::RightLeftrotate_(Node*& node)
{
	node->right->right = node->right->left;
	node->right->left = nullptr;

	node->right->right->right = node->right;
	node->right = node->right->right;
	node->right->right->right = nullptr;

	node->right->right->updateHeight();
	node->right->updateHeight();
	node->updateHeight();

	Rightrotate_(node); /// or add while with refresh balanc factor
}

void BinaryTree::LeftRightrotate_(Node*& node)
{
	node->left->left = node->left->right;
	node->left->right= nullptr;

	node->left->left->left = node->left;
	node->left = node->left->left;
	node->left->left->left = nullptr;

	node->left->left->updateHeight();
	node->left->updateHeight();
	node->updateHeight();

	Leftrotate_(node); /// or add while with refresh balanc factor
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

void BinaryTree::PrintLayer_(int depth, Node* node)
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
			tmpNode = (tmpNumber & mod)? tmpNode->right : tmpNode->left;
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
			//std::cout << tmpNode->data << "(" << tmpNode->height << ")" << " ";
			std::cout << tmpNode->data << " ";
		}
		++curNodeNum;
	}
	std::cout << std::endl;
}