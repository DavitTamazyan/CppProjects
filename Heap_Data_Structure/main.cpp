#include "Heap.h"

int main()
{
	int heapSize = 1000;
	Heap heap1(heapSize);
	int randnumber = 0;
	bool result = true;

	for (int i = 0; i < heapSize; ++i)
	{
		//std::cout << "_________________________" << std::endl;
		randnumber = rand() % 10;
		heap1.AddElement(randnumber);
		result &= heap1.checker();
		//heap1.PrintData();
		if (!heap1.checker())
		{
			std::cout << "Error" << std::endl;
		}
		//std::cout << "_________________________" << std::endl;
	}
	heap1.heapSort();
	heap1.PrintData();
	//std::cout << "heapifyCount  = " << heap1.heapifyCount << std::endl;
	std::cout << "NLogn = " << heapSize * log2(heapSize) << std::endl;
	std::cout << "heap1.checker() = " << heap1.checker() << std::endl;
	result &= heap1.checker();
	//for (int i = 0; i < heapSize; ++i)
	//{
	//	std::cout << "_________________________" << std::endl;
	//	heap1.extractMini();
	//	result &= heap1.checker();
	//	heap1.PrintData();
	//	if (!heap1.checker())
	//	{
	//		std::cout << "Error" << std::endl;
	//	}
	//	std::cout << "_________________________" << std::endl;
	//}
	if (result)
	{
		std::cout << "Pass" << std::endl;
	}
	else
	{
		std::cout << "Fail" << std::endl;
	}

}