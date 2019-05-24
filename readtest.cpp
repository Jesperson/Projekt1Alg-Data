#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>

using namespace std;

class representGraph
{
private:
	int n;
	list<int> *adjacencyMatrix;

public:
	representGraph(int n)
	{
		this->n = n;
		adjacencyMatrix = new list<int>[n];
	}
	~representGraph() { delete[] adjacencyMatrix; }

	void connectNodes(int x, int y);
	void DFSUtil(int n, bool visited[]); //DFS was the easiest algorithm to implement a graph, and that's why we decided to use this.
	bool checkAllConnections();
	int pathAvailable();
};

void representGraph::connectNodes(int x, int y)
{
	adjacencyMatrix[x].push_back(y);
	adjacencyMatrix[y].push_back(x);
}

void representGraph::DFSUtil(int nodeX, bool visited[])
{
	visited[nodeX] = true;

	list<int>::iterator i;
	for (i = adjacencyMatrix[nodeX].begin(); i != adjacencyMatrix[nodeX].end(); i++){
		if (!visited[*i]){
			DFSUtil(*i, visited);
		}
	}
}

int main(int argc, char *argv[])
{

	ifstream myFile;
	string fileName = argv[1];
	vector<string> nodes;
	list<int> nodesInt;
	//list<vector<string>> connected;

	string line;
	bool emptyLineFound = false;
	int n = -1;
	//test(nodes);
	myFile.open(argv[1]);
	if (myFile.is_open())
	{

		cout << "opened the file" << endl;

		while (emptyLineFound == false)
		{
			getline(myFile, line);
			if (line.size() == 0)
			{
				cout << "found empty line" << endl;
				emptyLineFound = true;
			}

			else if (n == -1)
			{
				cout << "First line found" << endl;
				n++;
				continue;
			}
			else
			{
				nodes.push_back(line);
				nodesInt.push_back(n);
				cout << nodes[n] << endl;
				n++;
			}
		}
		//change input method to handle ex. Alpha'\t'Gamma'\t'2
		cout << endl;
		int columnInFile = 0; //stående, hjälper datorn hålla koll vilken del av filen den jobbar med, och hanterar informationen därefter.
		int nodeX = 0;
		int nodeY = 0;
		while (myFile >> line)
		{
			if (columnInFile == 0)
			{

				nodeX = compareStringToVector(line, nodes, n);
				cout << "comparing string to vector. Name of node is: " << line << ", ";
				columnInFile = 1;
			}
			else if (columnInFile == 1)
			{
				nodeY = compareStringToVector(line, nodes, n);
				cout << " and the node it should connect to is: " << line << ". " << endl;
				columnInFile = 2;
			}
			else if (columnInFile == 2)
			{
				sadaf
				//cout << line << endl;
				columnInFile = 0;
				nodeX = 0;
				nodeY = 0;
			}
		}
	}
	else
	{
		cout << "File not found.";
	}
	for (int i = 0; i < n; i++)
	{
		cout << nodes[i] << " ";
	}

	myFile.close();
	return 0;
}
int compareStringToVector(string comparison, vector<string> vectorWithNodes, int n);
int compareStringToVector(string comparison, vector<string> vectorWithNodes, int n)
{
	int caseNr = -1;
	for (int y = 0; y < n; y++)
	{
		if (vectorWithNodes[y] == comparison)
		{
			caseNr = y;
		}
	}
	if (caseNr == -1)
	{
		cout << "Something went wrong chief... sorry boot dat." << endl;
	}
	return caseNr;
}
