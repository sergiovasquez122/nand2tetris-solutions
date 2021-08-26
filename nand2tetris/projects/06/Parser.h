//
// Created by sergi on 8/26/2021.
//

#ifndef INC_06_PARSER_H
#define INC_06_PARSER_H
#include <string>
#include <fstream>
#include <sstream>
enum class instructionType {A_INSTRUCTION, C_INSTRUCTION, L_INSTRUCTION, P_INSTRUCTION};

class Parser {
public:
    explicit Parser(const std::string& filename);
    bool hasMoreLines() const;
    void advance();
    std::string symbol() const;
    std::string dest() const;
    std::string comp() const;
    std::string jump() const;
    instructionType currentInstructionType() const;
    std::string currentInstruction() const;
private:
    void decideInstructionType();
    instructionType current_instruction_type;
    std::string current_instruction;
    std::fstream file_stream;
};


#endif //INC_06_PARSER_H
