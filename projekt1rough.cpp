#include<iostream> 
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
    int n;    // No. of vertices 
  
    // Pointer to an array containing adjacency 
    // lists 
    list<int> *adj;    
public: 
    Graph(int n);  // Constructor 
  
    // function to add an edge to graph 
    void addEdge(int v, int w);  
  
    // prints BFS traversal from a given source s 
    void BFS(int s);   

    void printEulerTour();

    void printEulerUtil(int u);

    bool isValidNextEdge(int u, int v);

    void rmvEdge(int u, int v);
}; 
void Graph::printEulerTour() 
{ 
  // Find a vertex with odd degree 
  int u = 0; 
  for (int i = 0; i < V; i++) 
      if (adj[i].size() & 1) 
        {   u = i; break;  } 
  
  // Print tour starting from oddv 
  printEulerUtil(u); 
  cout << endl; 
} 
  
void Graph::printEulerUtil(int u) 
{ 
  // Recur for all the vertices adjacent to this vertex 
  list<int>::iterator i; 
  for (i = adj[u].begin(); i != adj[u].end(); ++i) 
  { 
      int v = *i; 
  
      // If edge u-v is not removed and it's a a valid next edge 
      if (v != -1 && isValidNextEdge(u, v)) 
      { 
          cout << u << "-" << v << "  "; 
          rmvEdge(u, v); 
          printEulerUtil(v); 
      } 
  } 
} 

bool Graph::isValidNextEdge(int u, int v) 
{ 
  // The edge u-v is valid in one of the following two cases: 
  
  // 1) If v is the only adjacent vertex of u 
  int count = 0;  // To store count of adjacent vertices 
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
  int count2 = DFSCount(u, visited); 
  
  // 2.c) Add the edge back to the graph 
  addEdge(u, v); 
  
  // 2.d) If count1 is greater, then edge (u, v) is a bridge 
  return (count1 > count2)? false: true; 
} 

void Graph::rmvEdge(int u, int v) 
{ 
  // Find v in adjacency list of u and replace it with -1 
  list<int>::iterator iv = find(adj[u].begin(), adj[u].end(), v); 
  *iv = -1; 
  
  // Find u in adjacency list of v and replace it with -1 
  list<int>::iterator iu = find(adj[v].begin(), adj[v].end(), u); 
  *iu = -1; 
} 

Graph::Graph(int n) 
{ 
    this->n = n; 
    adj = new list<int>[n]; 
} 
  
void Graph::addEdge(int v, int w) 
{ 
    adj[v].push_back(w); // Add w to v’s list. 
    adj[w].push_back(v);
} 
  
void Graph::BFS(int s) 
{ 
    // Mark all the vertices as not visited 
    bool *visited = new bool[n]; 
    for(int i = 0; i < n; i++) 
        visited[i] = false; 
  
    // Create a queue for BFS 
    list<int> queue; 
  
    // Mark the current node as visited and enqueue it 
    visited[s] = true; 
    queue.push_back(s); 
  
    // 'i' will be used to get all adjacent 
    // vertices of a vertex 
    list<int>::iterator i; 
  
    while(!queue.empty()) 
    { 
        // Dequeue a vertex from queue and print it 
        s = queue.front(); 
        cout << s << " "; 
        //queue.push_back(s);
        queue.pop_front(); 
  
        // Get all adjacent vertices of the dequeued 
        // vertex s. If a adjacent has not been visited,  
        // then mark it visited and enqueue it 
        for (i = adj[s].begin(); i != adj[s].end(); ++i) 
        { 
            if (!visited[*i]) 
            { 
                visited[*i] = true; 
                queue.push_back(*i); 
            } 
        } 
    } 
} 
  
// Driver program to test methods of graph class 
//******************************************************************************************************
// *****************************************************************************************************
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
		graph1.BFS(3);
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