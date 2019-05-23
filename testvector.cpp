#include <iostream>
#include <vector>

int nodAntal(){};
int readFile(int n, std::string fileName){};
int writeFile(){};

int main(std::string fileName)
{
    std::vector<std::vector<char>> nodes;

}

 //Läser noderna separat
int readFile(int n, std::string argv[1])
    {
        std::string line;
        std::vector<std::string> myVector;

        std::istringstream iss(line);
        while (getline(f, line))
        {
            if (!line.size())
                break;
            myVector.push_back(std::move(line));
        }
    }

    int writeFile()
    {
        std::ofstream outputFile("Output.txt");
        for (int n = 0; n <= limit_arr; n++)
        {
            outputFile << nodes[i] << "->" << &nodes[i]
        }
    }