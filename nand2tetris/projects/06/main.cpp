#include <iostream>
#include <bitset>
#include "Parser.h"
#include "Code.h"

void initialize_symbol_table(std::unordered_map<std::string, int>& symbol_table){
    for(int i = 0;i <= 15;i++){
        std::string symbol{"R" + std::to_string(i)};
        symbol_table.insert({symbol, i});
    }
    symbol_table.insert({"SCREEN", 16384});
    symbol_table.insert({"KBD", 24576});
}

bool isNumber(const std::string& str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

std::string generate_machine_language_path(const std::string& path){
    size_t pos_idx = path.find_last_of('.');
    std::string machine_language = path.substr(0, pos_idx) + ".hack";
    return machine_language;
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
            symbol_table.insert({loop_symbol, line_number});
        } // the instruction is a pseudo-instruction. ignore for now
    }
    // second pass
    int n = 16;
    parser = Parser{argv[1]};
    Code code;
    std::string file_name_to_write_to = generate_machine_language_path(argv[1]);
    std::fstream file;
    file.open(file_name_to_write_to, std::fstream::out);
    while(parser.hasMoreLines()){
        parser.advance();
        if(parser.currentInstructionType() == instructionType::C_INSTRUCTION){
            std::string comp_code = code.comp(parser.comp());
            std::string dest_code = code.dest(parser.dest());
            std::string jump_code = code.jump(parser.jump());
            std::string full_code{"111"};
            // the full code
            full_code.append(comp_code).append(dest_code).append(jump_code);
            file << full_code << std::endl;
        } else if(parser.currentInstructionType() == instructionType::A_INSTRUCTION){
            std::string symbol{parser.symbol()};
            if(isNumber(symbol)){
                symbol_table.insert({symbol, std::stoi(symbol)});
            }
            // we have a new symbol, that references a variable
            if(!symbol_table.count(symbol)){
                symbol_table.insert({symbol, n++}); // we have a new symbol, that references a variable
            }
            int value{symbol_table.at(symbol)};
            std::string sixteen_bit_representation = std::bitset<16>(value).to_string();
            file << sixteen_bit_representation << std::endl;
        }
    }
    file.close();
}
