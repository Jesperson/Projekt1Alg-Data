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
	void DFSFunction(int n, bool visited[]); //DFS was the easiest algorithm to implement a graph, and that's why we decided to use this.
	bool checkAllConnections();
	int pathAvailable();
};

void representGraph::connectNodes(int x, int y)
{
	adjacencyMatrix[x].push_back(y);
	adjacencyMatrix[y].push_back(x);
}

void representGraph::DFSFunction(int nodeX, bool visited[])
{
	visited[nodeX] = true;

	list<int>::iterator i;
	for (i = adjacencyMatrix[nodeX].begin(); i != adjacencyMatrix[nodeX].end(); i++){
		if (!visited[*i]){
			DFSFunction(*i, visited);
		}
	}
}
bool representGraph::checkAllConnections(){
	bool connected;
	bool visited[n];
	int i;
	for (i = 0; i < n; i++){
		visited[i] = false;
	}

	for (i = 0; i < n; i++){
		if (adjacencyMatrix[i].size() != 0){
			break;
		}
	}
	if (i == n){
		connected = true;
	}

	DFSFunction(i, visited);

	for (i = 0; i < n; i++){
		if (visited[i] == false && adjacencyMatrix[i].size() > 0){
			connected = false;
		}
	}
	return connected;
}

int representGraph::pathAvailable(){

	int possible = -1;
	//checks if all non-isolated nodes are connected to eachother, aka not 2 graphs or similar problems
	if(checkAllConnections() == false){
		possible = 0;
	}
	
	//checks for the number of odd nodes, using the size of the list of nodes connected to a certain node
	int odd = 0;
	for (int i = 0; i < n; i++){
		if (adjacencyMatrix[i].size() % 2 == 1){
			odd++;
		}
	}
	//checks if the graph has more than 2 odd nodes, it is impossible to solve.
	if (odd > 2){
		possible = 0;
	}
	return possible;
}
int compareStringToVector(string comparison, vector<string> vectorWithNodes, int n);
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
		representGraph graph1(n);
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
				graph1.connectNodes(nodeX, nodeY);
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
