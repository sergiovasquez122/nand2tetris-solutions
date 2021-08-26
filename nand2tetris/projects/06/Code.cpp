//
// Created by sergi on 8/26/2021.
//

#include "Code.h"

std::string Code::jump(const std::string &j) {
    return jump_code.at(j);
}

std::string Code::comp(const std::string &c) {
    return comp_code.at(c);
}

std::string Code::dest(const std::string &d) {
    return dest_code.at(d);
}

Code::Code() {
    initialize_dest();
    initialize_comp();
    initialize_jump();
}

void Code::initialize_dest() {
    dest_code.insert({"null", "000"});
    dest_code.insert({"M", "001"});
    dest_code.insert({"D", "010"});
    dest_code.insert({"DM", "011"});
    dest_code.insert({"A", "100"});
    dest_code.insert({"AM", "101"});
    dest_code.insert({"AD", "110"});
    dest_code.insert({"ADM", "111"});
}

void Code::initialize_comp() {
    // instructions where a bit = 0
    comp_code.insert({"0", "0101010"});
    comp_code.insert({"1", "0111111"});
    comp_code.insert({"-1", "0111010"});
    comp_code.insert({"D", "00011100"});
    comp_code.insert({"A", "0110001"});
    comp_code.insert({"!D", "0001101"});
    comp_code.insert({"!A", "0110001"});
    comp_code.insert({"-D", "0001111"});
    comp_code.insert({"-A", "0110011"});
    comp_code.insert({"D+1", "0011111"});
    comp_code.insert({"A+1", "0110111"});
    comp_code.insert({"D-1", "0001110"});
    comp_code.insert({"A-1", "0110010"});
    comp_code.insert({"D+A", "0000010"});
    comp_code.insert({"D-A", "0010011"});
    comp_code.insert({"A-D", "0000111"});
    comp_code.insert({"D&A", "0000000"});
    comp_code.insert({"D|A", "0010101"});
    // instructions where a = 1
    comp_code.insert({"M", "1110000"});
    comp_code.insert({"!M", "1110001"});
    comp_code.insert({"-M", "1110011"});
    comp_code.insert({"M+1", "1110111"});
    comp_code.insert({"M-1", "1110010"});
    comp_code.insert({"D+M", "1000010"});
    comp_code.insert({"D-M", "1010011"});
    comp_code.insert({"M-D", "1000111"});
    comp_code.insert({"D&M", "1000000"});
    comp_code.insert({"D|M", "1010101"});
}

void Code::initialize_jump() {
    dest_code.insert({"null", "000"});
    dest_code.insert({"JGT", "001"});
    dest_code.insert({"JEG", "010"});
    dest_code.insert({"JGE", "011"});
    dest_code.insert({"JLT", "100"});
    dest_code.insert({"JNE", "101"});
    dest_code.insert({"JLE", "110"});
    dest_code.insert({"JMP", "111"});
}
