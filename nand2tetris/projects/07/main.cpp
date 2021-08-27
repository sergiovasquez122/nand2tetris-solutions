#include <iostream>
#include "Parser.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "usage: ./out file.vm" << std::endl;
    }
    Parser parser(argv[1]);

    while (parser.hasMoreLines()) {
        parser.advance();
        if(parser.currentInstructionType() == INSTRUCTION_TYPE::C_PSEUDO){
            continue;
        }
        std::cout << "current instruction: " << parser.currentInstruction() << std::endl;
    }
}