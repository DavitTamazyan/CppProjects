#include "PriorityQueue.h"

int main()
{
	PriorityQueue queue1;

	for (int i = 0; i < 8; ++i)
	{
		queue1.AddElement({ rand() % 100, rand() % 10 });
	}

	queue1.PrintData();
}
