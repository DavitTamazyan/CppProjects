#pragma once
#include<iostream>

class Heap
{
public:
	Heap(int size);

	~Heap();

	void AddElement(int key);

	void PrintData();

	int getMini();

	int extractMini();

	bool checker();

	void resize();

private:
	void heapify(int index);

	int GetParInd(int index);

	int GetRightInd(int index);

	int GetLeftInd(int index);

	bool checker_(int index);

private:
	int m_size;
	int* m_data;
	int m_dataCount;
};

