#include<iostream>
#include<fstream>

int readFile() {

 std::ifstream myFile;
 myFile.open("text.txt");
 char content[100];
 if (myFile.is_open()) {
 while (!myFile.eof()) {


    myFile >> content;
    std::cout << content;


 }
}
myFile.close();
return 0;
}