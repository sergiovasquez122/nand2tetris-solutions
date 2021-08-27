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
        std::cout << "[current instruction:] " << parser.currentInstruction() << " [current instruction type:] " << parser.currentInstructionType() << std::endl;
        if(parser.currentInstructionType() == INSTRUCTION_TYPE::C_PUSH){
            std::string first_arg = parser.arg1();
            int second_arg = parser.arg2();
            std::cout << "first arg: " << first_arg << " second_arg: " << second_arg << std::endl;
            std::cout << "first arg size: " << first_arg.size() << std::endl;
        } else if(parser.currentInstructionType() == INSTRUCTION_TYPE::C_POP){
            std::string first_arg = parser.arg1();
            int second_arg = parser.arg2();
            std::cout << "first arg: " << first_arg << " second_arg: " << second_arg << std::endl;
            std::cout << "first arg size: " << first_arg.size() << std::endl;
        } else if(parser.currentInstructionType() == INSTRUCTION_TYPE::C_ARITHMETIC){
            std::string first_arg = parser.arg1();
            std::cout << "first arg: " << first_arg << std::endl;
        }
    }
}