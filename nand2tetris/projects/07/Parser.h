//
// Created by sergi on 8/27/2021.
//

#ifndef INC_07_PARSER_H
#define INC_07_PARSER_H

#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

enum class INSTRUCTION_TYPE {C_ARITHMETIC, C_PUSH, C_POP, C_LABEL,
        C_GOTO, C_IF, C_FUNCTION, C_RETURN, C_CALL, C_PSEUDO};

class Parser {
public:
    explicit Parser(const std::string& filename);
    bool hasMoreLines() const;
    void advance();
    std::string arg1() const;
    int arg2() const;
    INSTRUCTION_TYPE currentInstructionType() const;
    std::string currentInstruction() const;
private:
    void decideInstructionType();
    void load_table();
    INSTRUCTION_TYPE current_instruction_type;
    std::string current_instruction;
    std::fstream file_stream;
    std::unordered_map<std::string, INSTRUCTION_TYPE> symbol_table;
};


#endif //INC_07_PARSER_H
