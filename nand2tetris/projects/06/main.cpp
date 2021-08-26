#include <iostream>
#include <fstream>
#include "Parser.h"
#include "Code.h"

bool getLine(std::string& line){
    std::getline(std::cin, line);
    return !line.empty();
}

void initialize_symbol_table(std::unordered_map<std::string, int>& symbol_table){
    for(int i = 0;i <= 15;i++){
        std::string symbol{"R" + std::to_string(i)};
        symbol_table.insert({symbol, i});
    }
    symbol_table.insert({"SCREEN", 16384});
    symbol_table.insert({"KBD", 24576});
}

int main(int argc, char* argv[]) {
    if(argc != 2){
        std::cerr << "usage: ./out file.asm" << std::endl;
    }
    Parser parser(argv[1]);
    std::unordered_map<std::string, int> symbol_table;
    initialize_symbol_table(symbol_table);
    // first_pass
    int line_number = 0;
    while(parser.hasMoreLines()){
        parser.advance();
        if(parser.currentInstructionType() == instructionType::A_INSTRUCTION ||
           parser.currentInstructionType() == instructionType::C_INSTRUCTION){
            line_number++;
            continue;
        } else if(parser.currentInstructionType() == instructionType::L_INSTRUCTION){
            std::string loop_symbol{parser.symbol()};
            symbol_table.insert({loop_symbol, line_number + 1});
        } // the instruction is a pseudo-instruction. ignore for now
    }
    // second pass
    int n = 16;
    parser = Parser{argv[1]};
    Code code;
    while(parser.hasMoreLines()){
        parser.advance();
        if(parser.currentInstructionType() == instructionType::C_INSTRUCTION){
            std::string comp_code = code.comp(parser.comp());
            std::string dest_code = code.dest(parser.dest());
            std::string jump_code = code.jump(parser.jump());
            std::string full_code{"111"};
            // the full code
            full_code.append(comp_code).append(dest_code).append(jump_code);
            // to-do: append content to a file
        }
    }
}
