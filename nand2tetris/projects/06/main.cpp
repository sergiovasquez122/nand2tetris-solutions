#include <iostream>
#include "Parser.h"
#include "Code.h"

bool getLine(std::string& line){
    std::getline(std::cin, line);
    return !line.empty();
}

int main() {
    Code code;
    std::string userInput;
    while(getLine(userInput)){
        std::string c = code.comp(userInput);
        std::cout << c << std::endl;
    }
}
