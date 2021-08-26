//
// Created by sergi on 8/26/2021.
//

#ifndef INC_06_PARSER_H
#define INC_06_PARSER_H
#include <string>
#include <filesystem>

class Parser {
public:
    explicit Parser(const std::string& filename);
    bool hasMoreLines() const;
    void advance();
    std::string symbol() const;
    std::string dest() const;
    std::string comp() const;
    std::string jump() const;
    enum class instruction_type {A_INSTRUCTION, C_INSTRUCTION, L_INSTRUCTION};
private:
    instruction_type current_instruction_type;
    std::string current_instruction;
};


#endif //INC_06_PARSER_H
