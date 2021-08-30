#include <iostream>
#include "Parser.h"
#include "CodeWriter.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "usage: ./out file.vm" << std::endl;
    }
    Parser parser(argv[1]);
    CodeWriter writer(argv[1]);
    while (parser.hasMoreLines()) {
        parser.advance();
        if(parser.currentInstructionType() == INSTRUCTION_TYPE::C_PSEUDO){
            continue;
        }
        if(parser.currentInstructionType() == INSTRUCTION_TYPE::C_PUSH){
            std::string first_arg = parser.arg1();
            int second_arg = parser.arg2();
            writer.writePush(first_arg, second_arg);
        } else if(parser.currentInstructionType() == INSTRUCTION_TYPE::C_POP){
            std::string first_arg = parser.arg1();
            int second_arg = parser.arg2();
            writer.writePop(first_arg, second_arg);
        } else if(parser.currentInstructionType() == INSTRUCTION_TYPE::C_ARITHMETIC){
            std::string first_arg = parser.arg1();
            writer.writeArithmetic(first_arg);
        } else if(parser.currentInstructionType() == INSTRUCTION_TYPE::C_IF){
            std::string first_arg = parser.arg1();
            writer.writeIf(first_arg);
        } else if(parser.currentInstructionType() == INSTRUCTION_TYPE::C_LABEL){
            std::string first_arg = parser.arg1();
            writer.writeLabel(first_arg);
        } else if(parser.currentInstructionType() == INSTRUCTION_TYPE::C_GOTO){
            std::string first_arg = parser.arg1();
            writer.writeGoto(first_arg);
        } else if(parser.currentInstructionType() == INSTRUCTION_TYPE::C_FUNCTION){
            std::string first_arg = parser.arg1();
            int second_arg = parser.arg2();

        } else if(parser.currentInstructionType() == INSTRUCTION_TYPE::C_CALL){
            std::string first_arg = parser.arg1();
            int second_arg = parser.arg2();

        } else if(parser.currentInstructionType() == INSTRUCTION_TYPE::C_RETURN){

        } else{
            throw std::runtime_error("unexpected argument: ");
        }
    }
   writer.close();
}