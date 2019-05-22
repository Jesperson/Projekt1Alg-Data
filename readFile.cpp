#include<iostream>
#include<fstream>

int readFile() {

 std::ifstream myFile;
 myFile.open("text.txt");
 char output[100];
 if (myFile.is_open()) {
 while (!myFile.eof()) {


    myFile >> output;
    std::cout << output;


 }
}
myFile.close();
return 0;
}