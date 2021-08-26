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
    size_t jump_idx = current_instruction.find(';');
    size_t dest_idx = current_instruction.find('=');

    bool jump_exists = (jump_idx != std::string::npos);
    bool dest_exists = (dest_idx != std::string::npos);

    // if both tokens ';' and '=' don't exist it is only a comp instruction
    if(!dest_exists && !jump_exists){
        return current_instruction;
    }
    // instruction is of the form 'dest=comp'
    if(dest_exists && !jump_exists){
        return current_instruction.substr(dest_idx + 1);
    }
    // instruction is of the form 'comp;jump'
    if(jump_exists){
        return current_instruction.substr(0, jump_idx);
    }
    // only comp
    return current_instruction;
}

std::string Parser::dest() const {
    size_t idx = current_instruction.find('=');
    if(idx == std::string::npos){
        return "null";
    }
    return current_instruction.substr(0, idx);
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
