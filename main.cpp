#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <Graph.hpp>

using namespace std;


int compareStringToVector(string comparison, vector<string> vectorWithNodes, int n);
int main(int argc, char *argv[])
{
	vector<string> nodes; // Vektor med nodernas namn
	ifstream myFile;
	string fileName = argv[1];
	list<int> nodesInt; // Lista av nodindex

	string line; // Input läst från .txt fil
	bool emptyLineFound = false;
	int n = 0; // Antal noder

	myFile.open(fileName);
	if (myFile.is_open())
	{
		while (emptyLineFound == false)
		{
			getline(myFile, line);
			if (line.size() == 0)
			{
				emptyLineFound = true;
			}

			else if (line == "UNDIRECTED" || line == "DIRECTED")
			{
				continue;
			}
			else
			{
				nodes.push_back(line);
				nodesInt.push_back(n);
				n++;
			}
		}
		//Ändrar input läsning samt hantering, för att hantera i formatet: "nod1"\t"nod2"\t"siffra" ex. Alpha'\t'Gamma'\t'2
		Graph graph1(n);	  //skapar ett objekt av Graph med n antal noder
		int columnInFile = 0; // Med hjälp av if-satser hanterar programmet inputen olika baserat på vilken kolumn den läser ifrån.
		int nodeX = 0;
		int nodeY = 0;
		while (myFile >> line)
		{
			// Om informationen läses från kolumn 1, innebär det att det ska gå en kant från denna noden
			if (columnInFile == 0)
			{
				nodeX = compareStringToVector(line, nodes, n);
				columnInFile = 1;
			}
			// Om informationen läses från kolumn 2, innebär det att noden från kolumn 1 ska kopplas med en kant till denna noden
			else if (columnInFile == 1)
			{
				nodeY = compareStringToVector(line, nodes, n);
				columnInFile = 2;
			}
			// Då informationen i kolumn 3 är orelevant för vår implementation så kopplas noderna ihop
			// här, samt återställer variablarna som används i föregående if-satser
			else if (columnInFile == 2)
			{
				graph1.addEdge(nodeX, nodeY);
				columnInFile = 0;
				nodeX = 0;
				nodeY = 0;
			}
		}
		graph1.checkPath(nodes);
		graph1.printToOutput();
	}
	else
	{
		cout << "File not found.";
	}

	myFile.close();
	return 0;
}
// Jämför en sträng med samtliga element i en vektor för att få nodindex
int compareStringToVector(string comparison, vector<string> vectorWithNodes, int n)
{
	int nodeIndex = -1;
	for (int y = 0; y < n; y++)
	{
		if (vectorWithNodes[y] == comparison)
		{
			nodeIndex = y;
		}
	}
	if (nodeIndex == -1)
	{
		cout << "Something went wrong chief... sorry boot dat." << endl;
	}
	return nodeIndex;
}