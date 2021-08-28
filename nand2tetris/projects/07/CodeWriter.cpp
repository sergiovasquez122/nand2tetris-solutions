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
}

void CodeWriter::addToStack() {

}

void CodeWriter::retrieveFromStack() {\
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

}

void CodeWriter::writePush(const std::string &segment, int index) {

}

void CodeWriter::writePop(const std::string &segment, int index) {

}

void CodeWriter::close() {
    file_stream.close();
}

std::string get_base_path(const std::string &path) {
    size_t pos_idx = path.find_last_of('.');
    return path.substr(0, pos_idx);
}
