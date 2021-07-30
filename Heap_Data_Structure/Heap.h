#pragma once
#include<iostream>

class PriorityQueue {
public:
	struct node
	{
		int data;
		int priority;
		node()
		{
			data = 0;
			priority = -1;
		}
		node(int _data, int _priority)
		{
			data = _data;
			priority = _priority;
		}
		node& operator=(const node& rhs)
		{
			this->data = rhs.data;
			this->priority = rhs.priority;
			return *this;
		}
	};

	PriorityQueue();

	PriorityQueue(int size);

	~PriorityQueue();
	
	void AddElement(node data);
	
	void PrintData();
	
	int getMini();
	
	int extractMini();
	
	bool checker();

	bool Sortchecker();
	
	void heapSort();

	void resize();

private:
	void heapify(int index);

	int GetParInd(int index);

	int GetRightInd(int index);

	int GetLeftInd(int index);

	bool checker_(int index);

private:
	int m_size;
	node* m_data;
	int m_dataCount;
};

