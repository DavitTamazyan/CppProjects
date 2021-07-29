#include "Heap.h"

Heap::Heap(int size)
{
	m_dataCount = 0;
	m_size = size + 1;
	m_data = new int[m_size];
	for (int i = 0; i < m_size; ++i)
	{
		m_data[i] = -1;
	}
}

Heap::~Heap()
{
	delete[] m_data;
}

void Heap::AddElement(int key)
{
	std::cout << "Adding element : " << key << std::endl;
	if (m_size - 1 == m_dataCount)
	{
		resize();
	}
	m_data[++m_dataCount] = key;
	heapify(m_dataCount);
}

void Heap::PrintData()
{
	for (int i = 1; i < m_size; ++i)
	{
		std::cout << m_data[i] << " ";
		if (!(i & i + 1))
		{
			std::cout << std::endl;
		}
	}
}

int Heap::getMini()
{
	return m_data[1];
}

int Heap::extractMini()
{
	std::cout << "Extract Minimum" << std::endl;
	int result = getMini();
	std::swap(m_data[1], m_data[m_dataCount]);
	m_data[m_dataCount--] = -1;
	heapify(1);
	return 0;
}

bool Heap::checker()
{
	return checker_(1);
}

void Heap::resize() /// need to fix bugs
{
	m_data;
	int* tmp = new int[2 * m_size];
	for (int i = 0; i < m_size; ++i)
	{
		tmp[i] = m_data[i];
	}
	for (int i = m_size; i < 2 * m_size; ++i)
	{
		tmp[i] = -1;
	}
	m_size *= 2;
	delete[] m_data;
	m_data = nullptr;
	m_data = tmp;
	tmp = nullptr;
}

bool Heap::checker_(int index)
{
	int ParInd = GetParInd(index);
	int Right = GetRightInd(index);
	int Left = GetLeftInd(index);
	bool result = true;

	if (index > m_dataCount)
	{
		return result;
	}
	if (Right < m_dataCount)
	{
		result &= (m_data[index] <= m_data[Right]);
	}
	if (Left < m_dataCount)
	{
		result &= (m_data[index] <= m_data[Left]);
	}
	return result && checker_(Right) && checker_(Left);
}

void Heap::heapify(int index)
{
	++heapifyCount;
	//std::cout << "Called heapify for : " << m_data[index] << std::endl;
	int ParInd = GetParInd(index);
	int Right = GetRightInd(index);
	int Left = GetLeftInd(index);
	if (m_data[ParInd] > m_data[index])
	{
		std::swap(m_data[ParInd], m_data[index]);
		heapify(ParInd);
		heapify(index);
		return;
	}
	else if (Right <= m_dataCount && m_data[Right] < m_data[index])
	{
		std::swap(m_data[Right], m_data[index]);
		heapify(Right);
		heapify(index);
		return;
	} 
	else if (Left <= m_dataCount && m_data[Left] < m_data[index])
	{
		std::swap(m_data[Left], m_data[index]);
		heapify(Left);
		heapify(index);
		return;
	}
}

void Heap::heapSort()
{
	int tmp = m_dataCount;
	for (int i = 1; i < tmp; ++i)
	{
		std::swap(m_data[1], m_data[m_dataCount]);
		--m_dataCount;
		heapify(1);
	}
	m_dataCount = tmp;
	for (int i = 0; i < m_dataCount / 2; ++i)
	{
		std::swap(m_data[i], m_data[m_dataCount - i]);
	}
}

int Heap::GetParInd(int index)
{
	return index / 2;
}

int Heap::GetRightInd(int index)
{
	return index * 2 + 1;
}

int Heap::GetLeftInd(int index)
{
	return index * 2;
}

