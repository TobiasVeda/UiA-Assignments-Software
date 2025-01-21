#include <iostream>
#include <string>

int main() {
    std::string input1;
    std::string input2;

    std::cout <<"Input string 1" <<std::endl;
    std::getline(std::cin,input1);

    std::cout <<"Input string 2" <<std::endl;
    std::getline(std::cin,input2);

    if (input1 == input2){
        std::cout <<"The strings are equal" <<std::endl;
    } else{
        std::cout <<"The strings are not equal" <<std::endl;
    }
    if (input1.find(input2) != std::string::npos){
        std::cout <<"Last string is substring of first string" <<std::endl;
    } else if (input2.find(input1) != std::string::npos){
        std::cout <<"First string is substring of last string" <<std::endl;
    } else if (input1.find(input2) == std::string::npos){
        std::cout <<"There are no substrings" <<std::endl;
    } else if (input2.find(input1) == std::string::npos){
        std::cout <<"There are no substrings" <<std::endl;
    } else{
        std::cout <<"¯\\_(ツ)_/¯" <<std::endl;
    }
}
