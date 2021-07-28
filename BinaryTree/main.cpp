#include"BinaryTree.h"
#include"vector"
int main()
{
	BinaryTree tree;
	std::vector<int> data;
	int randNum = 0;
	int counter = 0;

	for (int i = 0; i < 128; ++i)
	{
		randNum = rand() % 250;
		data.push_back(randNum);
		tree.addNode(randNum);   tree.Print(); std::cout << "________________________________________________" << std::endl;
	}

	for (int i = 0; i < 128; ++i)
	{
		randNum = data[i];
		counter += tree.search(randNum);
	}
	if (counter == 128)
	{
		std::cout << "Pass" << std::endl;
	}
	else
	{
		std::cout << "Fail : " << counter << " / 128" << std::endl;
	}
}
