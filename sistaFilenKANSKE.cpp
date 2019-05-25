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
  int V;          // Antal kanter
  list<int> *adj; // Lista för att hålla koll på länkar
  int startingNode = 0;
  string result = "2\n";
  bool isPossible;

public:
  // Const & destr
  Graph(int V)
  {
    this->V = V;
    adj = new list<int>[V];
  }
  ~Graph() { delete[] adj; }
  // Lägg till kant
  void addEdge(int u, int v)
  {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  void rmvEdge(int u, int v);

  // Skriv output till variabel (outputResult)
  void printEulerTour(vector<string> nodes);
  void printEulerUtil(int s, vector<string> nodes);
  void printResult();
  void printToOutput();

  // Räkna antal kanter som finns tillgängliga från en nod
  int countEdge(int v, bool visited[]);

  // Kolla om kanten funkar (om den inte redan är "använd" aka -1)
  bool isValidNextEdge(int u, int v);
};

/* The main function that print Eulerian Trail. It first finds an odd 
   degree vertex (if there is any) and then calls printEulerUtil() 
   to print the path */
//
void Graph::printEulerTour(vector<string> nodes)
{
  int odd = 0;
  // Hitta en kant med udda gradtal
  for (int i = 0; i < V; i++)
  {
    if (adj[i].size() % 2 == 1)
    {
      startingNode = i;
      odd++;
      //cout << "Starting node is: " << startingNode << "and adj[i] is: " << adj[i].size() << endl;
    }
  }
  if (odd > 2)
  {
    isPossible = false;
    printToOutput();
  }
  else
  {
    isPossible = true;
    string addstart = nodes[startingNode];
    result.append(addstart);
    // Print tour starting from oddv
    printEulerUtil(startingNode, nodes);
  }
}

// Skriver (INTE GJORD ÄN) nodkoppling
void Graph::printEulerUtil(int u, vector<string> nodes)
{
  // Recur for all the vertices adjacent to this vertex
  string adding;
  list<int>::iterator i;
  for (i = adj[u].begin(); i != adj[u].end(); ++i)
  {
    int v = *i;

    // If edge u-v is not removed and it's a a valid next edge
    if (v != -1 && isValidNextEdge(u, v))
    {
      //cout << "Trying to output the result string after assigning (or adding) the noder[u] name to the string." << endl;
      adding = " -> " + nodes[v];
      result.append(adding);
      //cout << " -> " << nodes[v];
      //cout << nodes[1];
      //cout << nodes[u] << "-" << nodes[v] << "  ";
      rmvEdge(u, v);
      printEulerUtil(v, nodes);
    }
  }
}
void Graph::printResult()
{
  cout << result;
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

void Graph::printToOutput()
{
  ofstream output;
  output.open("Output.txt");
  if (isPossible == false){
    output << "2\nNO PATH FOUND";
  }
  else if(isPossible == true){
    output << result;
  }
  output.close();
}

int compareStringToVector(string comparison, vector<string> vectorWithNodes, int n);
int main(int argc, char *argv[])
{
  vector<string> nodes;
  ifstream myFile;
  string fileName = argv[1];
  list<int> nodesInt;

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
        emptyLineFound = true;
      }

      else if (n == -1)
      {
        n++;
        continue;
      }
      else
      {
        nodes.push_back(line);
        nodesInt.push_back(n);
        n++;
      }
    }
    //changes input method to handle ex. Alpha'\t'Gamma'\t'2
    Graph graph1(n);
    int columnInFile = 0; //stående, hjälper datorn hålla koll vilken del av filen den jobbar med, och hanterar informationen därefter.
    int nodeX = 0;
    int nodeY = 0;
    while (myFile >> line)
    {
      if (columnInFile == 0)
      {

        nodeX = compareStringToVector(line, nodes, n);
        //cout << "Name of node is: " << line << ", ";
        columnInFile = 1;
      }
      else if (columnInFile == 1)
      {
        nodeY = compareStringToVector(line, nodes, n);
        //cout << " and the node it should connect to is: " << line << ". " << endl;
        columnInFile = 2;
      }
      else if (columnInFile == 2)
      {
        graph1.addEdge(nodeX, nodeY);
        columnInFile = 0;
        nodeX = 0;
        nodeY = 0;
      }
    }
    //fix this
    graph1.printEulerTour(nodes);
    graph1.printResult();
    graph1.printToOutput();
  }
  else
  {
    cout << "File not found.";
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