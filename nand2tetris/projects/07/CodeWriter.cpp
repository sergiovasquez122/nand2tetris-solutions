//
// Created by sergi on 8/27/2021.
//

#include "CodeWriter.h"

CodeWriter::CodeWriter(const std::string &filename): base_file_name(get_base_path(filename)) {
    file_stream.open(base_file_name + ".asm", std::fstream::out);
}

/**
 * sp++
 */
void CodeWriter::incrementStackPointer() {
    file_stream << "@SP" << std::endl;
    file_stream << "M=M+1" << std::endl;
}

void CodeWriter::pushSegment(const std::string &segment, int index) {
    file_stream << "@" + segment << std::endl;
    file_stream << "A=M" << std::endl;
    for(int i = 0;i < index;i++){
        file_stream << "A=A+1" << std::endl;
    }
    file_stream << "D=M" << std::endl;
    addToStack();
    incrementStackPointer();
}

/**
 * sp--, value = *sp, *(segment + i) = value
 */
void CodeWriter::popSegment(const std::string &segment, int index) {
    decrementStackPointer();
    retrieveFromStack();
    file_stream << "@" + segment << std::endl;
    file_stream << "A=M" << std::endl;
    for(int i = 0;i < index;i++){
        file_stream << "A=A+1" << std::endl;
    }
    file_stream << "M=D" << std::endl;
}

/**
 * writes the memory location the
 * stackpointer points to.
 */
void CodeWriter::addToStack() {
    file_stream << "@SP" << std::endl;
    file_stream << "A=M" << std::endl;
    file_stream << "M=D" << std::endl;
}

/**
 * Get the element the stackpointer points to
 * and stores it into the destination register.
 */
void CodeWriter::retrieveFromStack() {
    file_stream << "@SP" << std::endl;
    file_stream << "A=M" << std::endl;
    file_stream << "D=M" << std::endl;
}


/**
 * sp--
 */
void CodeWriter::decrementStackPointer() {
    file_stream << "@SP" << std::endl;
    file_stream << "M=M-1" << std::endl;
}

void CodeWriter::writeArithmetic(const std::string& command) {
    // regardless of command, we retrieve the topmost element from the stack
    decrementStackPointer();
    retrieveFromStack();
    // commands are unary operator any other would be binary
    if(command == "not" || command == "neg"){
        std::string value = (command == "not" ? "!D" : "-D");
        file_stream << value << std::endl;
    } else {
        // store the topmost stack information in temporary register, R13 is guaranteed to be allowed to be used.
        file_stream << "@R13" << std::endl;
        file_stream << "M=D" << std::endl;
        // get the second element from the stack
        decrementStackPointer();
        retrieveFromStack();
        // setup R13 to be ready to be used.
        file_stream << "@R13" << std::endl;
        // determine operation based on command.
        if(command == "add"){
            file_stream << "D=D+M" << std::endl;
        } else if(command == "sub"){
            file_stream << "D=D-M" << std::endl;
        } else if(command == "and"){
            file_stream << "D=D&M" << std::endl;
        } else if(command == "or"){
            file_stream << "D=D|M" << std::endl;
        } else if(command == "eq"){
            file_stream << "D=D-M" << std::endl;
            file_stream << "!D" << std::endl;
        } else if(command == "lt"){
            file_stream << "D=D-M" << std::endl;
        } else if(command == "gt"){
            file_stream << "D=D-M" << std::endl;
        } else {
            throw std::runtime_error("invalid argument");
        }
    }
    // add the computed value to stack and restore balance
    addToStack();
    incrementStackPointer();
}

void CodeWriter::writePush(const std::string &segment, int index) {
    if(segment == "constant"){
        pushConstant(index);
    } else if(segment == "temp"){
        int read_idx = 5 + index;
        file_stream << "@" << read_idx << std::endl;
        file_stream << "D=M" << std::endl;
        addToStack();
        incrementStackPointer();
    } else if (segment == "pointer"){
        std::string segment_translated = (index == 0) ? "this" : "that";
        writePush(segment_translated, 0);
    } else if(segment == "local" || segment == "argument" || segment == "this" || segment == "that"){
        writePush(segment, index);
    } else if(segment == "static"){
        file_stream << "@" << base_file_name << "." << index << std::endl;
        file_stream << "D=M" << std::endl;
        addToStack();
        incrementStackPointer();
    } else {
        throw std::runtime_error("unexpected arguments");
    }
}

void CodeWriter::writePop(const std::string &segment, int index) {

}

void CodeWriter::pushConstant(int index) {
    file_stream << "@" << index << std::endl;
    file_stream << "D=A" << std::endl;
    addToStack();
    incrementStackPointer();
}

void CodeWriter::close() {
    file_stream.close();
}

std::string get_base_path(const std::string &path) {
    size_t pos_idx = path.find_last_of('.');
    return path.substr(0, pos_idx);
}
