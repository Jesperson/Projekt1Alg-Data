#include<iostream>
#include<fstream>

int readFile() {

 std::ifstream myFile;
 std::string fileName = argv[1];
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