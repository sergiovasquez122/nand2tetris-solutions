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
    return current_instruction.substr(first_space_idx + 1, last_space_idx - first_space_idx - 1);
}



void Parser::decideInstructionType() {
    if(currentInstruction().empty()){
        current_instruction_type = INSTRUCTION_TYPE::C_PSEUDO;
    } else{
        std::string instruction = current_instruction;
        size_t idx = current_instruction.find_first_of(' ');
        if(idx != std::string::npos){
            instruction = current_instruction.substr(0, idx);
        }
        current_instruction_type = symbol_table.at(instruction);
    }
}

Parser::Parser(const std::string &filename) : file_stream(filename), current_instruction_type(INSTRUCTION_TYPE::C_PSEUDO)
{
    load_table();
}

void Parser::load_table() {
    symbol_table.insert({"push", INSTRUCTION_TYPE::C_PUSH});
    symbol_table.insert({"pop", INSTRUCTION_TYPE::C_POP});
    // arithmetic and logical operations
    symbol_table.insert({"add", INSTRUCTION_TYPE::C_ARITHMETIC});
    symbol_table.insert({"sub", INSTRUCTION_TYPE::C_ARITHMETIC});
    symbol_table.insert({"neg", INSTRUCTION_TYPE::C_ARITHMETIC});
    symbol_table.insert({"eq", INSTRUCTION_TYPE::C_ARITHMETIC});
    symbol_table.insert({"gt", INSTRUCTION_TYPE::C_ARITHMETIC});
    symbol_table.insert({"lt", INSTRUCTION_TYPE::C_ARITHMETIC});
    symbol_table.insert({"and", INSTRUCTION_TYPE::C_ARITHMETIC});
    symbol_table.insert({"or", INSTRUCTION_TYPE::C_ARITHMETIC});
    symbol_table.insert({"not", INSTRUCTION_TYPE::C_ARITHMETIC});
    // instructions related to branching
    symbol_table.insert({"label", INSTRUCTION_TYPE::C_LABEL});
    symbol_table.insert({"goto", INSTRUCTION_TYPE::C_GOTO});
    symbol_table.insert({"if-goto", INSTRUCTION_TYPE::C_IF});
    // instructions related to function calls.
    symbol_table.insert({"return", INSTRUCTION_TYPE::C_RETURN});
    symbol_table.insert({"call", INSTRUCTION_TYPE::C_CALL});
    symbol_table.insert({"function", INSTRUCTION_TYPE::C_FUNCTION});
}

std::ostream &operator<<(std::ostream &out, const INSTRUCTION_TYPE &instructionType) {
    switch(instructionType)
    {
        case INSTRUCTION_TYPE::C_ARITHMETIC: out << "C_ARITHMETIC"; break;
        case INSTRUCTION_TYPE::C_PUSH: out << "C_PUSH"; break;
        case INSTRUCTION_TYPE::C_POP: out << "C_POP"; break;
        case INSTRUCTION_TYPE::C_LABEL:
            out << "C_LABEL";
            break;
        case INSTRUCTION_TYPE::C_GOTO:
            out << "C_GOTO";
            break;
        case INSTRUCTION_TYPE::C_IF:
            out << "C_IF";
            break;
        case INSTRUCTION_TYPE::C_FUNCTION:
            out << "C_FUNCTION";
            break;
        case INSTRUCTION_TYPE::C_RETURN:
            out << "C_RETURN";
            break;
        case INSTRUCTION_TYPE::C_CALL:
            out << "C_CALL";
            break;
        case INSTRUCTION_TYPE::C_PSEUDO:
            out << "C_PSEUDO";
            break;
    }
    return out;
}