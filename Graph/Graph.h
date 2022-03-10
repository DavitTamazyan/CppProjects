#pragma once
#include"GraphInterface.h"
#include<iostream>
#include<fstream>
#include<chrono>
#include<ctime>
#include<stack>

template<class LabelType>
class Graph : public GraphInterface<LabelType>
{
public:
	/// Ctor & Dtor
	Graph();
	~Graph();
	/// Debug
	void ___PrintData();
	void ___PrintDataInFile();
	/// Info about Graph
	virtual int getNumVertices() const override;
	virtual int getNumEdges() const override;
	virtual int getEdgeWeight(LabelType start, LabelType end) const override;
	/// Add & Remove
	virtual bool add(LabelType start, LabelType end, int edgeWeight) override;
	virtual bool remove(LabelType start, LabelType end) override;
	/// Traversals
	virtual void depthFirstTraversal(LabelType start) override;
	virtual void breadthFirstTraversal(LabelType start) override;
	/// shortest-path algorithms
	virtual int* DijkstraAlg(LabelType start);
	virtual int* BellmanFordAlg(LabelType start);
	/// other Algorithms
	virtual void TopologicalSort(LabelType start); /// return type ???
	virtual void MinimumSpanningTree(LabelType start); /// return type ??? Kruskal’s Algorithm
	/// Set internal things
	virtual bool SetDirectedGraph(bool dir);
private:
	void ___PrintMap();
	void ___PrintMapInFile();
	int Findbyvalue(LabelType val) const;
	int GetNewIndex(LabelType val);
	void ResizeMap();
	void ResizeData();
	void depthFirstTraversal_int(int index, bool*& isVisited);
	void breadthFirstTraversal_int(int index, bool*& isVisited);
	void DijkstraNode(int* distArr, int NodeIndex, bool*& isVisited); /// bad name
	void BellmanFordNode(int* distArr, int NodeIndex, bool*& isVisited); /// also bad name
	void TopologicalSortRec(std::stack<LabelType>& path, int index, bool*& isVisited);
	void MinimumSpanningTreeRec(std::stack<LabelType>& path, int index, bool*& isVisited);
private:
	int m_size;
	int** m_data;
	int m_edgesCount;
	int m_vertexCount;
	LabelType* m_map;
	int m_map_size; 
	mutable std::ofstream m_myfile;
	bool m_DirectedGraph;
};