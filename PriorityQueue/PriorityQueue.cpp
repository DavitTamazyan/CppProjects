#include "PriorityQueue.h"

PriorityQueue::PriorityQueue()
{
	m_dataCount = 0;
	m_size = 8 + 1;
	m_data = new node[m_size];
	for (int i = 0; i < m_size; ++i)
	{
		m_data[i].priority = -1;
	}
}

PriorityQueue::PriorityQueue(int size)
{
	m_dataCount = 0;
	m_size = size + 1;
	m_data = new node[m_size];
	for (int i = 0; i < m_size; ++i)
	{
		m_data[i].priority = -1;
	}
}

PriorityQueue::~PriorityQueue()
{
	delete[] m_data;
}

void PriorityQueue::AddElement(node data)
{
	std::cout << "Adding element : " << data.data << " with priority : " << data.priority << std::endl;
	if (m_size - 1 == m_dataCount)
	{
		resize();
	}
	m_data[++m_dataCount] = data;
	heapify(m_dataCount);
}

void PriorityQueue::PrintData()
{
	for (int i = 1; i < m_size; ++i)
	{
		std::cout << m_data[i].data << "(" << m_data[i].priority << ")" << " ";
		if (!(i & i + 1))
		{
			std::cout << std::endl;
		}
	}
}

int PriorityQueue::getMini()
{
	return m_data[1].data;
}

int PriorityQueue::extractMini()
{
	std::cout << "Extract Minimum" << std::endl;
	int result = getMini();
	std::swap(m_data[1], m_data[m_dataCount]);
	m_data[m_dataCount--].priority = -1;
	heapify(1);
	return 0;
}

bool PriorityQueue::checker()
{
	return checker_(1);
}

void PriorityQueue::resize() /// need to fix bugs
{
	m_data;
	node* tmp = new node[2 * m_size];
	for (int i = 0; i < m_size; ++i)
	{
		tmp[i] = m_data[i];
	}
	for (int i = m_size; i < 2 * m_size; ++i)
	{
		tmp[i].priority = -1;
	}
	m_size *= 2;
	delete[] m_data;
	m_data = nullptr;
	m_data = tmp;
	tmp = nullptr;
}

bool PriorityQueue::checker_(int index)
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
		result &= (m_data[index].priority <= m_data[Right].priority);
	}
	if (Left < m_dataCount)
	{
		result &= (m_data[index].priority <= m_data[Left].priority);
	}
	return result && checker_(Right) && checker_(Left);
}

void PriorityQueue::heapify(int index)
{
	//std::cout << "Called heapify for : " << m_data[index] << std::endl;
	int ParInd = GetParInd(index);
	int Right = GetRightInd(index);
	int Left = GetLeftInd(index);
	if (m_data[ParInd].priority > m_data[index].priority)
	{
		std::swap(m_data[ParInd], m_data[index]);
		heapify(ParInd);
		heapify(index);
		return;
	}
	else if (Right <= m_dataCount && m_data[Right].priority < m_data[index].priority)
	{
		std::swap(m_data[Right], m_data[index]);
		heapify(Right);
		heapify(index);
		return;
	}
	else if (Left <= m_dataCount && m_data[Left].priority < m_data[index].priority)
	{
		std::swap(m_data[Left], m_data[index]);
		heapify(Left);
		heapify(index);
		return;
	}
}

int PriorityQueue::GetParInd(int index)
{
	return index / 2;
}

int PriorityQueue::GetRightInd(int index)
{
	return index * 2 + 1;
}

int PriorityQueue::GetLeftInd(int index)
{
	return index * 2;
}

