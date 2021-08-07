#include "HashTable.h"

HashTable::HashTable(int size)
{
	m_size = size;
	m_data = new std::list<int>[size];
}

HashTable::~HashTable()
{
	delete[] m_data;
}

void HashTable::Insert(int key)
{
	int index = HashFunction(key);
	m_data[index].push_front(key);
}

void HashTable::Delete(int key)
{
	int index = HashFunction(key);
	std::list<int>::iterator it = m_data[index].begin();
	while (it != m_data[index].end())
	{
		if (*it == key)
		{
			m_data[index].erase(it);
			break;
		}
		++it;
	}
}

void HashTable::DisplayHash()
{
	std::cout << "Start" << std::endl;
	std::list<int>::iterator tmp;
	for (int i = 0; i < m_size; ++i)
	{
		tmp = m_data[i].begin();
		while (!m_data[i].empty() && tmp != m_data[i].end() )
		{
			std::cout << *tmp++ << "->";
		}
		std::cout << std::endl;
	}
	std::cout << "End" << std::endl;
}

int HashTable::HashFunction(int key)
{
	return key % m_size;
}
