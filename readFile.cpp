#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
int main(int argc, char *argv[])
{

   ifstream myFile;
   string fileName = argv[1];
   vector<string> nodes;
   vector<vector<string>> connected;
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
         else if (n == -1)
         {
            cout << "First line found" << endl;
            n++;
            continue;
         }
         else
         {
            cout << line + " ";
            nodes[n].push_back(line[0]);
            cout << nodes[n][0] << endl;
            n++;
         }
      };

      switchFunc(nodeX, nodeY){
         for(int n = 0; n <= nodes.size(); n++){
            connected[x][n] = nodes[y];
            *nodes[x] -> nodes[y];
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