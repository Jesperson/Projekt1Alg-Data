#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>

using namespace std;

class representGraph
{
private:
	int odd = 0;
	int n;
	int o = 0;
	int e = 0;
	list<int> *adjacencyMatrix;
	list<int> edges;
	string result;
	int oddNodes[2];

public:
	representGraph(int n)
	{
		this->n = n;
		adjacencyMatrix = new list<int>[n];
	}
	~representGraph() { delete[] adjacencyMatrix; }

	void connectNodes(int x, int y);
	void BFSFunction(int n); //DFS was the easiest algorithm to implement a graph, and that's why we decided to use this.
	bool checkAllConnections();
	bool pathAvailable(); //add int list as parameter here <3
	void outputResultToFile(string result, bool possible);
	void test(representGraph &g);
};

//Connect Nodes (Add V)
void representGraph::connectNodes(int x, int y)
{
	cout << "Connecting node: " << x << " with node " << y << endl;
	adjacencyMatrix[x].push_back(y);
	e++;
}

//BFS Func
void representGraph::BFSFunction(int n) //change this to know that a road was used, not a node.
{
	bool *visited = new bool[n];
	for (int i = 0; i < n; i++)
		visited[i] = false;

	list<int> qV;  //Queue Vertex List

	visited[n] = true;
	qV.push_back(n);
	list<int>::iterator i;

	while(!qV.empty())
	{
		n = qV.front();
		//Lägg till output till result här <<<<<<<<<<<<<
		qV.pop_front();

		for (i = adjacencyMatrix[n].begin(); i != adjacencyMatrix[n].end(); i++)
		{
			if (!visited[*i])
			{
				visited[*i] = true;
				qV.push_back(*i);
			}
		}
	}
}
bool representGraph::checkAllConnections()
{
	cout << "Made it to the connection func. " << endl;
	bool connected = true;
	int visited[e];
	int i;
	for (i = 0; i < e; i++)
	{
		visited[i] = 0;
	}
	cout << e << endl;
	/*for (i = 0; i < n; i++){
		cout 
	}*/
	for (i = 0; i < n; i++)
	{
		if (adjacencyMatrix[i].size() != 0)
		{
			break;
		}
	}
	if (i == n)
	{
		connected = true;
	}
	cout << "Rad 97";
	BFSFunction(n);

	for (i = 0; i < n; i++)
	{
		if (visited[i] == false && adjacencyMatrix[i].size() > 0)
		{
			cout << "Node nr: " << i << " was not connected." << endl;
			connected = false;
		}
	}
	cout << "result from connection func: " << connected << endl;
	return connected;
}

bool representGraph::pathAvailable()
{ //add list as parameter here <3

	int possible = -1;
	//checks if all non-isolated nodes are connected to eachother, aka not 2 graphs or similar problems
	if (checkAllConnections() == false)
	{
		possible = 0;
	}

	//checks for the number of odd nodes, using the size of the list of nodes connected to a certain node
	for (int i = 0; i < o; i++)
	{
		if (adjacencyMatrix[i].size() % 2 == 1)
		{
			oddNodes[0] = i;
		}
	}
	//checks if the graph has more than 2 odd nodes, it is impossible to solve.
	if (odd > 2)
	{
		possible = 0;
		result = "2\nNO PATH FOUND";
		outputResultToFile(result, possible);
		cout << result;
	}
	return possible;
}
void representGraph::outputResultToFile(string result, bool possible)
{
	cout << "made it into the output." << endl;
	ofstream outputFile;
	outputFile.open("Output.txt");
	outputFile << result;
	outputFile.close();
}
void representGraph::test(representGraph &g)
{
	int res = g.pathAvailable();
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
				cout << "Name of node is: " << line << ", ";
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
		graph1.test(graph1);
	}
	else
	{
		cout << "File not found.";
	}

	cout << "From vector: ";
	for (int i = 0; i < n; i++)
	{
		cout << nodes[i] << " ";
	}
	list<int>::iterator l;
	cout << endl
		 << "From list: ";
	for (l = nodesInt.begin(); l != nodesInt.end(); l++)
	{
		cout << *l << " ";
	}
	cout << "From adjacencylist: ";
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
