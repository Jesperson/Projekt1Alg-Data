#include <iostream>
#include <fstream>
#include <string>

int readFile(){}

int main(){
std::string fileName = argv[1];
int contentSize = 10;
char(*ary)[10] = new char[contentSize][10];

}

int readFile() {

 std::ifstream myFile;
 myFile.open(argv[1]);
 char input[100];
 if (myFile.is_open()) {
 while (!myFile.eof()) {

    myFile >> input;
    std::cout << input;

 }
}
myFile.close();
return 0;
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
    std::ofstream outfile ("test.txt");

    outfile << "my text here!" << std::endl;

    outfile.close();
*/