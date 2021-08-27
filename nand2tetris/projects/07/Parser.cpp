//
// Created by sergi on 8/27/2021.
//

#include "Parser.h"

/**
 * Are there more lines in the input?
 */
bool Parser::hasMoreLines() const {
    return !file_stream.eof();
}

std::string Parser::currentInstruction() const {
    return current_instruction;
}

INSTRUCTION_TYPE Parser::currentInstructionType() const {
    return current_instruction_type;
}

/**
 * Returns the second argument of the current command.
 *
 * Should be called only if the current command
 * is C_PUSH, C_POP, C_FUNCTION, or C_CALL
 */
int Parser::arg2() const {
    size_t idx = current_instruction.find_last_of(' ');
    std::string string_representation{current_instruction.substr(idx + 1)};
    return std::stoi(string_representation);
}

/**
 * Reads the next command from the input
 * and makes it the current command.
 *
 * This routine should be called only if
 * hasMoreLines is true.
 *
 * Initially there is no more commands.
 */
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

/**
 * Returns the first argument of the current command.
 *
 * In the case of C_ARITHMETIC, the command itself
 * {add, sub, etc.} is returned
 *
 * Should not be called if the current command is
 * C_RETURN
 */
std::string Parser::arg1() const {
    // we can return the entire line directly
    if(current_instruction_type == INSTRUCTION_TYPE::C_ARITHMETIC){
        return current_instruction;
    }
    size_t first_space_idx = current_instruction.find_first_of(' ');
    size_t last_space_idx = current_instruction.find_last_of(' ');
    return current_instruction.substr(first_space_idx + 1, last_space_idx - first_space_idx);
}

void Parser::decideInstructionType() {
        if(currentInstruction().empty()){
            current_instruction_type = INSTRUCTION_TYPE::C_PSEUDO;
        }

}

Parser::Parser(const std::string &filename) : file_stream(filename), current_instruction_type(INSTRUCTION_TYPE::C_PSEUDO)
{
}
