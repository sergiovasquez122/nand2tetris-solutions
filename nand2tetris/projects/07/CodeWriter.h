//
// Created by sergi on 8/27/2021.
//

#ifndef INC_07_CODEWRITER_H
#define INC_07_CODEWRITER_H

#include <string>
#include <fstream>
#include <unordered_map>

class CodeWriter {
public:
    explicit CodeWriter(const std::string& filename);
    void writeArithmetic(const std::string& command);
    void writePush(const std::string& segment, int index);
    void writePop(const std::string& segment, int index);
    void close();
private:
    void incrementStackPointer();
    void addToStack();
    void retrieveFromStack();
    void decrementStackPointer();
    void pushConstant(int index);
    void pushSegment(const std::string& segment, int index);
    void popSegment(const std::string& segment, int index);
    std::string base_file_name;
    std::fstream file_stream;
};

std::string get_base_path(const std::string& path);
#endif //INC_07_CODEWRITER_H
