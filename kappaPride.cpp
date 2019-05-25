#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string.h>

using namespace std;

// This class represents a directed graph using
// adjacency list representation
class Graph
{
	int V;					// Antal kanter
	list<int> *adj; // Lista för att hålla koll på länkar
public:
	// Const & destr
	Graph(int V)
	{
		this->V = V;
		adj = new list<int>[V];
	}
	~Graph() { delete[] adj; }
	string result = "2\n";
	vector<string> nodes;
	// Lägg till kant
	void addEdge(int u, int v)
	{
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	void rmvEdge(int u, int v);

	// Skriv output till variabel (outputResult)
	void printEulerTour();
	void printEulerUtil(int s, vector<string> nodes, string resultat);

	// Räkna antal kanter som finns tillgängliga från en nod
	int countEdge(int v, bool visited[]);

	// Kolla om kanten funkar (om den inte redan är "använd" aka -1)
	bool isValidNextEdge(int u, int v);
};

/* The main function that print Eulerian Trail. It first finds an odd 
   degree vertex (if there is any) and then calls printEulerUtil() 
   to print the path */
//
void Graph::printEulerTour()
{
	// Hitta en kant med udda gradtal
	string result;
	int u = 0;
	for (int i = 0; i < V; i++)
		if (adj[i].size() % 2 == 1)
		{
			u = i;
			cout << "Starting node is: " << u << "and adj[i] is: " << adj[i].size() << endl;
			break;
		}

	// Print tour starting from oddv
	printEulerUtil(u, nodes, result);
	cout << endl;
}

// Skriver (INTE GJORD ÄN) nodkoppling
void Graph::printEulerUtil(int u, vector<string> nodes, string result)
{
	vector<string> noder;
	string resultat;
	// Recur for all the vertices adjacent to this vertex
	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i)
	{
		int v = *i;

		// If edge u-v is not removed and it's a a valid next edge
		if (v != -1 && isValidNextEdge(u, v))
		{
			//cout << "Trying to output the result string after assigning (or adding) the noder[u] name to the string." << endl;
			//resultat = resultat + noder[u] + " " + " -> " + noder[v];
			//cout << result;
			//cout << noder[1];
			//cout << resultat;
			cout << u << "-" << v << "  ";
			rmvEdge(u, v);
			printEulerUtil(v, noder, result);
		}
	}
}

// The function to check if edge u-v can be considered as next edge in
// Euler Tout
bool Graph::isValidNextEdge(int u, int v)
{
	// The edge u-v is valid in one of the following two cases:

	// 1) If v is the only adjacent vertex of u
	int count = 0; // To store count of adjacent vertices
	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i)
		if (*i != -1)
			count++;
	if (count == 1)
		return true;

	// 2) If there are multiple adjacents, then u-v is not a bridge
	// Do following steps to check if u-v is a bridge

	// 2.a) count of vertices reachable from u
	bool visited[V];
	memset(visited, false, V);
	int count1 = countEdge(u, visited);

	// 2.b) Remove edge (u, v) and after removing the edge, count
	// vertices reachable from u
	rmvEdge(u, v);
	memset(visited, false, V);
	int count2 = countEdge(u, visited);

	// 2.c) Add the edge back to the graph
	addEdge(u, v);

	// 2.d) If count1 is greater, then edge (u, v) is a bridge
	return (count1 > count2) ? false : true;
}

// This function removes edge u-v from graph.  It removes the edge by
// replacing adjcent vertex value with -1.
void Graph::rmvEdge(int u, int v)
{
	// Find v in adjacency list of u and replace it with -1
	list<int>::iterator iv = find(adj[u].begin(), adj[u].end(), v);
	*iv = -1;

	// Find u in adjacency list of v and replace it with -1
	list<int>::iterator iu = find(adj[v].begin(), adj[v].end(), u);
	*iu = -1;
}

// A DFS based function to count reachable vertices from v
int Graph::countEdge(int v, bool visited[])
{
	// Mark the current node as visited
	visited[v] = true;
	int count = 1;

	// Recur for all vertices adjacent to this vertex
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (*i != -1 && !visited[*i])
			count += countEdge(*i, visited);

	return count;
}

void printToOutput(string result)
{
	ofstream output;
	output.open("Output.txt");
	output << result;
	output.close();
}

int compareStringToVector(string comparison, vector<string> vectorWithNodes, int n);
int main(int argc, char *argv[])
{
	vector<string> nodes;
	ifstream myFile;
	string fileName = argv[1];
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
		Graph graph1(n);
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
				graph1.addEdge(nodeX, nodeY); //revert these!!!
				//cout << line << endl;
				columnInFile = 0;
				nodeX = 0;
				nodeY = 0;
			}
		}
		//fix this
		graph1.printEulerTour();
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