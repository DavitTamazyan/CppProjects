#include "HashTable.h"
#include<vector>

int main()
{
	int tablesize = 30;
	int elemSize = 200;
	HashTable tab(tablesize);
	std::vector<int> data;
	int data_tmp;
	for (int i = 0; i < elemSize; ++i)
	{
		data_tmp = rand() % 30;
		tab.Insert(data_tmp);
		data.push_back(data_tmp);
	}
	tab.DisplayHash();

	for (int i = 0; i < elemSize; ++i)
	{
		tab.Delete(data[i]);
	}
	
	tab.DisplayHash();
}
