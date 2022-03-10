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
	Graph<std::string> myGraph{};
	myGraph.SetDirectedGraph(false);
	myGraph.add("A", "B", 4);
	myGraph.add("B", "C", 5);
	myGraph.add("C", "D", 2);
	myGraph.add("D", "A", 1);
	//myGraph.add("i", "a", 2);
	//myGraph.add("a", "b", 6);
	//myGraph.add("a", "f", 4);
	//myGraph.add("g", "f", 2);
	//myGraph.add("b", "e", 9);
	//myGraph.add("g", "e", 8);
	//myGraph.add("g", "d", 5);
	//myGraph.add("e", "c", 3);
	//myGraph.add("b", "c", 7);
	//myGraph.add("d", "c", 4);
	//myGraph.add("d", "h", 1);
	try
	{
		myGraph.MinimumSpanningTree("A");
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