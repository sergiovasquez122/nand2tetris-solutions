//
// Created by sergi on 8/27/2021.
//

#include "CodeWriter.h"

CodeWriter::CodeWriter(const std::string &filename): base_file_name(get_base_path(filename)) {
    file_stream.open(base_file_name + ".asm", std::fstream::out);
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
