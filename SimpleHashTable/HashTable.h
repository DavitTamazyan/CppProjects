#pragma once
#include<iostream>
#include<list>

class HashTable
{
public:
	HashTable(int size);

	~HashTable();

	void Insert(int key);

	void Delete(int key);

	void DisplayHash();

private:
	int HashFunction(int key);
private:
	std::list<int>* m_data;
	int m_size;
};

