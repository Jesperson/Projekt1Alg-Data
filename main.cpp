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
	int V;			// Antal kanter
	list<int> *adj; // Lista för att hålla koll på länkar/vägar mellan noder
	int startingNode = 0;
	string result = "2\n";

public:
	// Const & destr
	Graph(int V)
	{
		this->V = V;
		adj = new list<int>[V];
	}
	~Graph() { delete[] adj; }
	// Lägger till en kant mellan noderna
	void addEdge(int u, int v)
	{
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	// Markerar en kant som besökt för att strukturen av vårt program ska fungera
	void visitEdge(int u, int v);

    // Kollar om en graf går att lösa och om den går att lösa, får den en startnod om det finns
    // en nod med udda antal kanter, samt kallar på funktionen som beräknar hur den ska lösas
	void checkPath(vector<string> nodes);

    // Funktionen som ska beräkna hur grafen ska lösas samt skriver in resultatet i en sträng
	void calculatePathToResult(int s, vector<string> nodes);


	void printResult();

    // Denna funktionen öppnar filen "Output.txt", om denna inte finns, skapas en fil med detta namn,
    // och resultatet från calculatePathToResult skrivs in i filen
	void printToOutput();

	// Räkna antal kanter som finns tillgängliga från nod[v]
	int countEdge(int v, bool visited[]);

	// Kolla om kanten är giltig, är kanten redan besökt har den värdet -1
	bool checkNextEdge(int u, int v);
};

/* The main function that print Eulerian Trail. It first finds an odd 
   degree vertex (if there is any) and then calls calculatePathToResult() 
   to print the path */
//
void Graph::checkPath(vector<string> nodes)
{
	int odd = 0;
	// Hittar kanter med udda gradtal/antal vägar, huvudsakligen för att räkna om grafen går att lösa
	// Om grafen är lösbar vet programmet även att den ska börja på en udda nod istället för den först inlästa noden
	for (int i = 0; i < V; i++)
	{
		if (adj[i].size() % 2 == 1)
		{
			startingNode = i;
			odd++;
		}
	}
	// Då det inte kan finnas en Euler-väg om det finns fler än 2 noder med udda antal kanter
	// kan vi redan här avgöra om programmet bör fortsätta eller inte

	// Om det finns fler än 2 noder med udda kanter, går programmet direkt till att skriva ut resultatet i "Output.txt", och avslutas strax därefter
	if (odd > 2)
	{
		string addText = "NO PATH FOUND";
		result.append(addText);
	}
	// Om det inte finns det, går programmet vidare och försöker hitta en Euler-väg i grafen.
	else
	{
		string addstart = nodes[startingNode];
		result.append(addstart);
		calculatePathToResult(startingNode, nodes);
	}
}

// Traverserar vägen, som sparar det slutgiltliga resultatet i en sträng. Vägen börjar med startingNode
// calculatePathToResult
void Graph::calculatePathToResult(int u, vector<string> nodes)
{
	// Recur for all the vertices adjacent to this vertex
	string addToResult;
	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i)
	{
		int v = *i;

		if (v != -1 && checkNextEdge(u, v))
		{
			addToResult = " -> " + nodes[v];
			result.append(addToResult);
			visitEdge(u, v);
			calculatePathToResult(v, nodes);
		}
	}
}

// Funktionen kollar om kanten mellan nod u och nod v kan vara nästa kant i EulerTour
bool Graph::checkNextEdge(int u, int v)
{
	// The edge u-v is valid in one of the following two cases:
	// Kanten mellan u och v är giltig om:

	// 1) om v är den enda noden kopplad till u
	int count = 0; // Variabel som räknar antal kopplade noder
	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i)
	{
		if (*i != -1)
			count++;
	}

	if (count == 1)
	{
		return true;
	}

	// 2) Om det finns fler kanter, så är kanten mellan u och v inte en återvändsgränd

	// Gör följande för att kolla om kant (u, v) är en återvändsgränd:
	// 2.a) räkna antalet kanter som är tillgängliga från nod u   count of vertices reachable from u
	bool visited[2000];
	memset(visited, false, V);
	int count1 = countEdge(u, visited);

	// 2.b) Ta bort kanten (u, v), och efter den är borttagen, räkna antalet kanter tillgängliga från nod u igen
	visitEdge(u, v);
	memset(visited, false, V);
	int count2 = countEdge(u, visited);

	// 2.c) Lägg tillbaka kanten till grafen
	addEdge(u, v);

	// 2.d) Om count1 är större, innebär det att kant (u, v) är en återvändsgränd
	bool isValid;
	if (count1 > count2)
	{
		isValid = false; // Om kanten (u, v) är en bro, är alltså denna vägen inte en giltig nästa kant för att lösa grafen
	}
	else
	{
		isValid = true;
	}
	return isValid;
}

// Funktionen tar bort kanten mellan u och v från grafen. Detta gör den genom att sätta dess värde i adj listan till -1
void Graph::visitEdge(int u, int v)
{
	// Iteratorn använder sig av find för att hitta v i adj listan av nod u och ersätter dess värde med -1
	list<int>::iterator iv = find(adj[u].begin(), adj[u].end(), v);
	*iv = -1;

	// Samma sak här, men istället för att hitta v i adj[u], letar den efter u i adj[v] och ersätter värdet med -1
	list<int>::iterator iu = find(adj[v].begin(), adj[v].end(), u);
	*iu = -1;
}

// Funktionen är baserad på DFS och räknar antalet giltiga kanter från nod v
int Graph::countEdge(int v, bool visited[])
{
	// Mark the current node as visited
	visited[v] = true;
	int count = 1;

	// Recur for all vertices adjacent to this vertex
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
	{
		if (*i != -1 && !visited[*i])
			count += countEdge(*i, visited);
	}

	return count;
}

void Graph::printToOutput()
{
	ofstream output;
	output.open("Output.txt");
	output << result;
	output.close();
    cout << "Results were printed to 'Output.txt'. " << endl;
}

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
		Graph graph1(n); //skapar ett objekt av Graph med n antal noder
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