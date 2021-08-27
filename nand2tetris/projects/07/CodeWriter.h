//
// Created by sergi on 8/27/2021.
//

#ifndef INC_07_CODEWRITER_H
#define INC_07_CODEWRITER_H

#include <string>

class CodeWriter {
public:
    explicit CodeWriter(const std::string& filename);
    void writeArithmetic(const std::string& command);
    void writePush(const std::string& segment, int index);
    void writePop(const std::string& segment, int index);
    void close();
};


#endif //INC_07_CODEWRITER_H
