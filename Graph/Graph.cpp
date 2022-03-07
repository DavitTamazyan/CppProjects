#include "Graph.h"
#define __DEBUG__TXT__
template<class LabelType>
Graph<LabelType>::Graph()
{
	m_size = 0;
	m_data = nullptr;
	m_edgesCount = 0;
	m_vertexCount = 0;
	m_map = nullptr;
	m_map_size = 0;
	m_DirectedGraph = false;
	m_myfile.open("Graphs.txt");
#ifdef __DEBUG__
	auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
#pragma warning(suppress : 4996)
	std::cout << ctime(&timenow) << std::endl;
#endif // __DEBUG__
#ifdef __DEBUG__TXT__
	auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
#pragma warning(suppress : 4996)
	m_myfile << ctime(&timenow) << std::endl;
#endif // __DEBUG__TXT__

}

template<class LabelType>
Graph<LabelType>::~Graph()
{
	if (0 != m_size)
	{
		for (int i = 0; i < m_size; ++i)
		{
			delete[] m_data[i];
		}
		delete[] m_data;
	}
	if (0 != m_map_size)
	{
		delete[] m_map;
	}
	m_myfile.close();

}

template<class LabelType>
void Graph<LabelType>::___PrintData() /// need to modify for big print data
{
	std::cout << "___________________________________________________________________" << std::endl;
	std::cout << "\t";
	for (int i = 0; i < m_size; ++i)
	{
		if (m_vertexCount > i)
		{
			std::cout << m_map[i] << "\t";
		}
		else
		{
			std::cout << "U\t";
		}
	}
	std::cout << std::endl;
	/////////////////////////////////////////////
	for (int i = 0; i < m_size; ++i)
	{
		if (m_vertexCount > i)
		{
			std::cout << m_map[i] << "\t";
		}
		else
		{
			std::cout << "U\t";
		}
		for (int j = 0; j < m_size; ++j)
		{
			std::cout << m_data[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << "___________________________________________________________________" << std::endl;
	___PrintMap();
}

template<class LabelType>
void Graph<LabelType>::___PrintDataInFile() /// need to modify for big print data
{
	m_myfile << "___________________________________________________________________" << std::endl;
	m_myfile << "\t";
	for (int i = 0; i < m_size; ++i)
	{
		if (m_vertexCount > i)
		{
			m_myfile << m_map[i] << "\t";
		}
		else
		{
			m_myfile << "U\t";
		}
	}
	m_myfile << std::endl;
	/////////////////////////////////////////////
	for (int i = 0; i < m_size; ++i)
	{
		if (m_vertexCount > i)
		{
			m_myfile << m_map[i] << "\t";
		}
		else
		{
			m_myfile << "U\t";
		}
		for (int j = 0; j < m_size; ++j)
		{
			m_myfile << m_data[i][j] << "\t";
		}
		m_myfile << std::endl;
	}
	m_myfile << std::endl;
	m_myfile << "___________________________________________________________________" << std::endl;
	___PrintMapInFile();
}

template<class LabelType>
int Graph<LabelType>::getNumVertices() const
{
	return m_vertexCount;
}

template<class LabelType>
int Graph<LabelType>::getNumEdges() const /// maybe need internal member for holding edges count
{
	return m_edgesCount;
}

template<class LabelType>
bool Graph<LabelType>::add(LabelType start, LabelType end, int edgeWeight) /// valid for undirected and for int type, need to add checker and resize function
{
#ifdef __DEBUG__
		std::cout << "called add for " << start << " <=> " << end << std::endl;
#endif
#ifdef __DEBUG__TXT__
		m_myfile << "called add for " << start << " <=> " << end << std::endl;
#endif

	int startIdx = Findbyvalue(start);
	if (-1 == startIdx)
	{
		startIdx = GetNewIndex(start);
	}
	int endIdx = Findbyvalue(end);
	if (-1 == endIdx)
	{
		endIdx = GetNewIndex(end);
	}
	m_data[startIdx][endIdx] = edgeWeight;
	if (false == m_DirectedGraph)
	{
		m_data[endIdx][startIdx] = edgeWeight;
	}
	++m_edgesCount;
#ifdef __DEBUG__
		std::cout << "add for " << start << " <=> " << end << " Done" << std::endl;
#endif
#ifdef __DEBUG__TXT__
		m_myfile << "add for " << start << " <=> " << end << " Done" << std::endl;
#endif
		return true; /// always true???
}

template<class LabelType>
bool Graph<LabelType>::remove(LabelType start, LabelType end) /// valid for undirected and for int type, need to add checker
{
	int startIdx = Findbyvalue(start);
	int endIdx = Findbyvalue(end);

	if (-1 == startIdx)
	{
		startIdx = GetNewIndex(start);
	}
	if (-1 == endIdx)
	{
		endIdx = GetNewIndex(end);
	}

	m_data[startIdx][endIdx] = 0;
	if (false == m_DirectedGraph)
	{
		m_data[endIdx][startIdx] = 0;
	}
	--m_edgesCount;
	return true;
}

template<class LabelType>
int Graph<LabelType>::getEdgeWeight(LabelType start, LabelType end) const /// valid for undirected and for int type
{
	int startIdx = Findbyvalue(start);
	int endIdx = Findbyvalue(end);

	if (-1 == startIdx || -1 == endIdx)
	{
		return -1;
	}

	return m_data[startIdx][endIdx];
	//return -1;
}

template<class LabelType>
void Graph<LabelType>::depthFirstTraversal(LabelType start)
{
	bool* isVisited = new bool[m_vertexCount] {};
	depthFirstTraversal_int(Findbyvalue(start), isVisited);
}

template<class LabelType>
void Graph<LabelType>::breadthFirstTraversal(LabelType start)
{
	bool* isVisited = new bool[m_vertexCount] {};
	std::cout << "Node = " << start << std::endl; /// I thing bad coding
	breadthFirstTraversal_int(Findbyvalue(start), isVisited);
}

template<class LabelType>
int* Graph<LabelType>::DijkstraAlg(LabelType start) /// will be error if start isn't valid node
{
	int* distArr = new int[m_map_size]; /// change to m_vertexCount for best perf. ;D
	int trgIdx = Findbyvalue(start);
	if (-1 == trgIdx)
	{
		return nullptr;
	}
	bool* isVisited = new bool[m_map_size];
	
	for (int i = 0; i < m_map_size; ++i)
	{
		distArr[i] = INT_MAX;
		isVisited[i] = false;
	}
	distArr[trgIdx] = 0;
	isVisited[trgIdx] = true;

	DijkstraNode(distArr, trgIdx, isVisited);

	/// Debug
	for (int i = 0; i < m_map_size; ++i)
	{
		std::cout << m_map[i] << "<=>" << distArr[i] << std::endl;
	}
	/// Debug end

	delete[] isVisited;

	return distArr;
}

template<class LabelType>
int* Graph<LabelType>::BellmanFordAlg(LabelType start)
{
	int* distArr = new int[m_map_size]; /// change to m_vertexCount for best perf. ;D
	int trgIdx = Findbyvalue(start);
	if (-1 == trgIdx)
	{
		return nullptr;
	}
	bool* isVisited = new bool[m_map_size];

	/// steep 1
	for (int i = 0; i < m_map_size; ++i)
	{
		distArr[i] = m_data[trgIdx][i] ? m_data[trgIdx][i] : INT_MAX;
		isVisited[i] = false;
	}
	distArr[trgIdx] = 0;
	isVisited[trgIdx] = true;
	/// steep 1 end

	/// steep 2
		for (int i = 0; i < m_vertexCount; ++i)
		{
			BellmanFordNode(distArr, i, isVisited);
		}
	//}
	/// steep 2 end

	/// steep 3
	for (int i = 0; i < m_map_size; ++i)
	{
		if (0 != m_data[trgIdx][i])
		{
			if (distArr[i] > distArr[trgIdx] + m_data[trgIdx][i])
			{
				std::cout << "Negative weight cycle detected" << std::endl;
			}
		}
	}
	/// steep 3 end

	/// Debug
	for (int i = 0; i < m_map_size; ++i)
	{
		std::cout << m_map[i] << "<=>" << distArr[i] << std::endl;
	}
	/// Debug end

	delete[] isVisited;

	return distArr;
}

template<class LabelType>
bool Graph<LabelType>::SetDirectedGraph(bool dir)
{
	m_DirectedGraph = dir;
	return m_DirectedGraph; /// why ???
}

template<class LabelType>
void Graph<LabelType>::___PrintMap()
{
	std::cout << "___________________________________________________________________" << std::endl;
	for (int i = 0; i < m_map_size; ++i)
	{
		std::cout << i << " : " << m_map[i] << std::endl;
	}
	std::cout << "___________________________________________________________________" << std::endl;
}

template<class LabelType>
void Graph<LabelType>::___PrintMapInFile()
{
	m_myfile << "___________________________________________________________________" << std::endl;
	for (int i = 0; i < m_map_size; ++i)
	{
		m_myfile << i << " : " << m_map[i] << std::endl;
	}
	m_myfile << "___________________________________________________________________" << std::endl;
}

template<class LabelType>
int Graph<LabelType>::Findbyvalue(LabelType val) const
{
#ifdef __DEBUG__
		std::cout << "Called Findbyvalue for " << val << std::endl;
#endif
#ifdef __DEBUG__TXT__
		m_myfile << "Called Findbyvalue for " << val << std::endl;
#endif // __DEBUG__TXT__
		if (m_map_size == 0)
		{
			return -1;
		}

	int index = 0;
	while (m_map_size > index && val != m_map[index])
	{
		++index;
	}
	return (index < m_size) ? index : -1; /// bad coding
}

template<class LabelType>
int Graph<LabelType>::GetNewIndex(LabelType val)
{
#ifdef __DEBUG__
		std::cout << "Called GetNewIndex for " << val << std::endl;
#endif
#ifdef __DEBUG__TXT__
		m_myfile << "Called GetNewIndex for " << val << std::endl;
#endif
	if (m_vertexCount >= m_map_size)
	{
		ResizeMap();
		ResizeData();
	}
	++m_vertexCount; /// bad coding
	m_map[m_vertexCount - 1] = val;
	return m_vertexCount - 1;
}

template<class LabelType>
void Graph<LabelType>::ResizeMap()
{
#ifdef __DEBUG__
		std::cout << "Called ResizeMap" << std::endl;
#endif
#ifdef __DEBUG__TXT__
		m_myfile << "Called ResizeMap" << std::endl;
#endif
		if (0 == m_map_size)
		{
			m_map = new LabelType[1];
			++m_map_size;
#ifdef __DEBUG__
				std::cout << "ResizeMap Done" << std::endl;
#endif
#ifdef __DEBUG__TXT__
				m_myfile << "ResizeMap Done" << std::endl;
#endif
				return;
		}
	int newSize = 2 * m_map_size;
	LabelType* tmp = new LabelType[newSize];
	for (int i = 0; i < m_map_size; ++i)
	{
		tmp[i] = std::move(m_map[i]);
	}
	for (int i = m_map_size; i < newSize; ++i)
	{
		tmp[i] = {};
	}
	delete[] m_map;
	m_map = tmp;
	m_map_size *= 2;
	tmp = nullptr;
#ifdef __DEBUG__
		std::cout << "ResizeMap Done" << std::endl;
#endif
#ifdef __DEBUG__TXT__
		m_myfile << "ResizeMap Done" << std::endl;
#endif
}

template<class LabelType>
void Graph<LabelType>::ResizeData()
{
#ifdef __DEBUG__
	std::cout << "Called ResizeData" << std::endl;
#endif // __DEBUG__
#ifdef __DEBUG__TXT__
	m_myfile << "Called ResizeData" << std::endl;
#endif // __DEBUG__TXT__
	if (0 == m_size) /// bad coding
	{
		m_size = 1;
		m_data = new int* [m_size];
		m_data[0] = new int[m_size];
		m_data[0][0] = 0;
#ifdef __DEBUG__
		std::cout << "ResizeData Done" << std::endl;
#endif // __DEBUG__
#ifdef __DEBUG__TXT__
		m_myfile << "ResizeData Done" << std::endl;
#endif // __DEBUG__TXT__
		return;
	}

	int newSize = 2 * m_size;
	int** tmp = new int* [newSize];
	for (int i = 0; i < m_size; ++i)
	{
		tmp[i] = new int[newSize];
		for (int j = 0; j < m_size; ++j)
		{
			tmp[i][j] = m_data[i][j];
		}
		for (int j = m_size; j < newSize; ++j)
		{
			tmp[i][j] = 0;
		}
	}
	for (int i = m_size; i < newSize; ++i)
	{
		tmp[i] = new int[newSize];
		for (int j = 0; j < newSize; ++j)
		{
			tmp[i][j] = 0;
		}
	}
	delete[] m_data;
	m_data = tmp;
	tmp = nullptr;
	m_size = newSize;
#ifdef __DEBUG__
	std::cout << "ResizeData Done" << std::endl;
#endif // __DEBUG__
#ifdef __DEBUG__TXT__
	m_myfile << "ResizeData Done" << std::endl;
#endif // __DEBUG__TXT__
}

template<class LabelType>
void Graph<LabelType>::depthFirstTraversal_int(int index, bool*& isVisited)
{
	std::cout << "Node = " << m_map[index] << std::endl;
	isVisited[index] = true;
	for (int i = 0; i < m_size; ++i)
	{
		if (m_data[index][i] != 0 && !isVisited[i]) /// check != 0 maybe need to use infinity
		{
			depthFirstTraversal_int(i, isVisited);
		}
	}
}

template<class LabelType>
void Graph<LabelType>::breadthFirstTraversal_int(int index, bool*& isVisited) /// change impl
{
	isVisited[index] = true;
	for (int i = 0; i < m_size; ++i)
	{
		if (m_data[index][i] != 0 && !isVisited[i]) 
		{
			std::cout << "Node = " << m_map[i] << std::endl; /// I thing bad coding
		}
	}
	for (int i = 0; i < m_size; ++i)
	{
		if (m_data[index][i] != 0 && !isVisited[i]) /// check != 0 maybe need to use infinity
		{
			breadthFirstTraversal_int(i, isVisited);
		}
	}
}

template<class LabelType>
void Graph<LabelType>::DijkstraNode(int* distArr, int NodeIndex, bool*& isVisited)
{
	std::cout << "Called for " << m_map[NodeIndex] << std::endl;
	isVisited[NodeIndex] = true;
	for (int i = 0; i < m_map_size; ++i)
	{
		if (0 != m_data[NodeIndex][i] && NodeIndex != i)
		{
			if (m_data[NodeIndex][i] < 0)
			{
				throw std::invalid_argument("received negative value");
			}
			if (distArr[NodeIndex] + m_data[NodeIndex][i] < distArr[i])
			{
				distArr[i] = m_data[NodeIndex][i] + distArr[NodeIndex];
			}
			if (true != isVisited[i])
			{
				DijkstraNode(distArr, i, isVisited);
			}
		}
	}
}

template<class LabelType>
void Graph<LabelType>::BellmanFordNode(int* distArr, int NodeIndex, bool*& isVisited) /// isVisited isn't used
{
	std::cout << "Called for " << m_map[NodeIndex] << std::endl;
	for (int i = 0; i < m_map_size; ++i)
	{
		if (0 != m_data[NodeIndex][i])
		{
			if (distArr[i] > distArr[NodeIndex] + m_data[NodeIndex][i])
			{
				distArr[i] = distArr[NodeIndex] + m_data[NodeIndex][i];
			}
		}
	}
}