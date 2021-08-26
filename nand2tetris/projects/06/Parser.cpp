//
// Created by sergi on 8/26/2021.
//

#include "Parser.h"

std::string Parser::jump() const {
    size_t idx = current_instruction.find(';');
    if(idx == std::string::npos){
        return "null";
    }
    return current_instruction.substr(idx + 1);
}

std::string Parser::comp() const {
    return std::__cxx11::string();
}

std::string Parser::dest() const {
    return std::__cxx11::string();
}

Parser::Parser(const std::string &filename) : file_stream(filename)
{
}

bool Parser::hasMoreLines() const {
    return !file_stream.eof();
}

void Parser::advance() {

}

std::string Parser::symbol() const {
    if(current_instruction_type == instructionType::A_INSTRUCTION){
        return current_instruction.substr(1); // everything after @
    }
    // instruction must then be an L_instruction (xxx)
    std::string l_instruction = current_instruction.substr(1);
    l_instruction.pop_back(); // remove the ) character
    return l_instruction;
}
