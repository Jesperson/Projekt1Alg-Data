#include <iostream>
#include <vector>
#include <list>

int nodAntal(){};
int readFile(int n, std::string fileName){};

int main(std::string fileName)
{
    std::vector<int> nodes(int limit_arr);
};

int readFile(int n, std::string argv[1])
{
    int limit_arr;
    std::ifstream fileInput;
    fileInput.open(argv[1]);
    if (fileInput.is_open())
    {
        while (!fileInput.eof())
        {

            fileInput >> nodes(limit_arr);
            std::cout << input;
        };
    }
    fileInput.close();
    return 0;
}