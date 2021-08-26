#ifndef INC_06_CODE_H
#define INC_06_CODE_H
#include <unordered_map>
#include <string>
class Code {
public:
    std::string dest(const std::string& d) const;
    std::string comp(const std::string& c) const;
    std::string jump(const std::string& j) const;
    Code();
private:
    void initialize_dest();
    void initialize_comp();
    void initialize_jump();
    std::unordered_map<std::string, std::string> dest_code;
    std::unordered_map<std::string, std::string> comp_code;
    std::unordered_map<std::string, std::string> jump_code;
};


#endif //INC_06_CODE_H
