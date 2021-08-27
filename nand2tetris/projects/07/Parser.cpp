//
// Created by sergi on 8/27/2021.
//

#include "Parser.h"

bool Parser::hasMoreLines() const {
    return !file_stream.eof();
}

std::string Parser::currentInstruction() const {
    return current_instruction;
}

INSTRUCTION_TYPE Parser::currentInstructionType() const {
    return current_instruction_type;
}

int Parser::arg2() const {
    return 0;
}

void Parser::advance() {
    current_instruction.clear();
    do {
        std::string line;
        std::string token;
        std::getline(file_stream, line);
        std::stringstream ss(line);
        // we check to see if the token is a comment or is a line full of white space
        ss >> token;
        if(token.empty() || token.at(0) == '/'){
            continue;
        }
        current_instruction = line;
    } while (hasMoreLines() && current_instruction.empty());
    decideInstructionType();
}

std::string Parser::arg1() const {
    return std::__cxx11::string();
}

void Parser::decideInstructionType() {
        if(currentInstruction().empty()){
            current_instruction_type = INSTRUCTION_TYPE::C_PSEUDO;
        }
}
