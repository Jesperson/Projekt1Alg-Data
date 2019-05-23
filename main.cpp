#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
int readFile(){};

using namespace std;
int main(int argc, char *argv[])
{

   ifstream myFile;
   string fileName = argv[1];
   vector<string> node;
   string line;
   int n = -1;

   myFile.open(argv[1]);
   if (myFile.is_open())
   {

      cout << "opened the file" << endl;

      while (getline(myFile, line))
      {
         //myFile >> node[n];

         //node[n] = line;
         if (line.size() == 0)
         {
            cout << "found empty line, breaking." << endl;
            break;
         }
         else if (n == -1){
            cout << "First line found" << endl;
            n++;
            continue;
         }
         else
         {
            cout << line + " ";
            node.push_back(line);
            cout << node[n] << endl;
            n++;
         }
      }
   }
   else
   {
      cout << "File not found.";
   }
   myFile.close();
   return 0;
}

//nodeEdge kollar hur många noder som har udda kanter
void checkEuler(){
    if(int nodeEdge >= 2){
        std::cout << "No path available."
    };

}


/*
    -Input från en fil, dynamisk char/string array? alternativt vektor/er.
    -Kolla input och designera noder från filen
    -Länka noderna i ordningen som visas i filen, eg a -> b, alfa -> beta (verkar inte stå i samma nod-system)
    -Implementera algoritm för att kolla om det finns en hamiltoncykel tillgänglig
    -Start och slutpos avgörs av func
*/

/*
    -----Output fil-----
    std::ofstream outfile ("outputText.txt");

    outfile << "my text here!" << std::endl;

    outfile.close();
*/

/*
        EN GRAF INNEHÅLLER MINST 1 EULERVÄG OM HÖGST 2 AV GRAFENS HÖRN ÄR UDDA HÖRN

*/