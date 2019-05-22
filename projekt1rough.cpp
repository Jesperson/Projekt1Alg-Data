#include <iostream>
#include <fstream>
#include <string>

int main()
{
//Variabler

int limit_arr = 15;  //Arbiträr limit
std::string fileInfo[limit_arr]; //Ta limit_arr och lägg till i arrayen som kommer ta vara på input från filen
std::string line; //En rad från input filen
std::string fileLocation; //Exakt position för input filen, skrivs in manuellt.

//Variabler
std::cout << "What is the exact file location, including the filename?" << std::endl;
std::cin >> fileLocation;
std::ifstream inputFile(fileLocation);
    if(inputFile.is_open()){
        while (getline(inputFile, line)){
            for(int l = 0; l >= limit_arr; l++){
                std::cin >> fileInfo[l];

            }
        }
    }
    else std::cout << "Unable to open file.";
    return 0;
}





/*

OUTPUT: 2 endl;
    Station[bokstav] -> Station[Bokstav2] -> Station[Bokstav3]
    ||
    NO PATH FOUND


*/

/*

if()

*/