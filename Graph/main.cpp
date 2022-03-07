#include<iostream>
//#include"Graph.h"
#include"Graph.cpp" /// Linker error for above code
/*--------------------------------------------------------------------------*/
#include<vector>
#include<string>

void AddRandomStrings(Graph<std::string>&, int, int, int);
void AddRandomCities(Graph<std::string>&);

int main()
{
	Graph<int> myGraph{};
	myGraph.SetDirectedGraph(true);
	myGraph.add(0, 1, -1);
	myGraph.add(1, 2, 3);
	myGraph.add(0, 2, 4);
	myGraph.add(1, 3, 2);
	myGraph.add(3, 1, 1);
	myGraph.add(3, 2, 5);
	myGraph.add(1, 4, 2);
	myGraph.add(4, 3, -3);
	try
	{
		//myGraph.DijkstraAlg(1);
		myGraph.BellmanFordAlg(0);
	}
	catch (...)
	{
		std::cout << "extension" << std::endl;
	}

	/// /// ///
	myGraph.___PrintDataInFile();
}

/*--------------------------------------------------------------------------*/
void AddRandomStrings(Graph<std::string>& myGraph,
	int word_count = 20,
	int word_max_size = 8,
	int word_min_size = 3
)
{
	std::vector<char> alphabet;
	int rand_word_size = 0;
	int randletter = 0;
	for (char i = 'A'; i < 'Z' + 1; ++i)
	{
		alphabet.push_back(i);
	}
	for (char i = 'a'; i < 'z' + 1; ++i)
	{
		alphabet.push_back(i);
	}
	for (int i = 0; i < word_count; ++i)
	{
		rand_word_size = word_min_size + (rand() % (word_max_size - word_min_size));
		std::string newWord = "";
		std::string newWord1 = "";
		for (int i = 0; i < rand_word_size; ++i)
		{
			newWord.push_back(alphabet[rand() % 52]);
			newWord1.push_back(alphabet[rand() % 52]);
		}
		myGraph.add(newWord, newWord1, rand() % 10);
	}
}

void AddRandomCities(Graph<std::string>& map)
{
	map.add("Moscow", "Yerevan", 2234);
	map.add("Moscow", "Kyiv", 874);
	map.add("Warsav", "Kyiv", 783);
	map.add("Los Angeles", "Kyiv", 10124);
	map.add("Los Angeles", "Tokyo", 8814);
	map.add("Tokyo", "Yerevan", 7922);
	map.add("Tokyo", "Beijing", 2101);
	map.add("Tokyo", "Beijing", 2101);
	map.add("Beijing", "Hong Kong", 1966);
}
