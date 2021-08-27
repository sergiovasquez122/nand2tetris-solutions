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

}

std::string Parser::arg1() const {
    return std::__cxx11::string();
}
