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
    file_stream << "// " << command << std::endl;
    // regardless of command, we retrieve the topmost element from the stack
    decrementStackPointer();
    retrieveFromStack();
    // commands are unary operator any other would be binary
    if(command == "not" || command == "neg"){
        std::string value = (command == "not" ? "D=!D" : "D=-D");
        file_stream << value << std::endl;
        addToStack();
        incrementStackPointer();
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
            addToStack();
            incrementStackPointer();
        } else if(command == "sub"){
            file_stream << "D=D-M" << std::endl;
            addToStack();
            incrementStackPointer();
        } else if(command == "and"){
            file_stream << "D=D&M" << std::endl;
            addToStack();
            incrementStackPointer();
        } else if(command == "or"){
            file_stream << "D=D|M" << std::endl;
            addToStack();
            incrementStackPointer();
        } else if(command == "eq"){
            write_eq();
        } else if(command == "lt"){
            write_lt();
        } else if(command == "gt"){
            write_gt();
        } else {
            throw std::runtime_error("invalid argument");
        }
    }
}

void CodeWriter::write_eq(){
    file_stream << "D=D-M" << std::endl;
    // we are currently set to R13
    file_stream << "M=D" << std::endl;
    // assume that they were equal and add to stack.
    file_stream << "D=-1" << std::endl;
    addToStack();
    incrementStackPointer();
    file_stream << "@R13" << std::endl;
    file_stream << "D=M" << std::endl;
    file_stream << "@JUMP." << jump_counter << std::endl;
    file_stream << "D;JEQ" << std::endl;
    decrementStackPointer();
    retrieveFromStack();
    pushConstant(0);
    file_stream << "(JUMP." << (jump_counter++) << ")" << std::endl;
}

void CodeWriter::write_lt(){
    file_stream << "D=D-M" << std::endl;
    // we are currently set to R13
    file_stream << "M=D" << std::endl;
    // assume that they were less then and add to stack.
    file_stream << "D=-1" << std::endl;
    addToStack();
    incrementStackPointer();
    file_stream << "@R13" << std::endl;
    file_stream << "D=M" << std::endl;
    file_stream << "@JUMP." << jump_counter << std::endl;
    file_stream << "D;JLT" << std::endl;
    decrementStackPointer();
    retrieveFromStack();
    pushConstant(0);
    file_stream << "(JUMP." << (jump_counter++) << ")" << std::endl;
}

void CodeWriter::write_gt(){
    file_stream << "D=D-M" << std::endl;
    // we are currently set to R13
    file_stream << "M=D" << std::endl;
    // assume that they were less then and add to stack.
    file_stream << "D=-1" << std::endl;
    addToStack();
    incrementStackPointer();
    file_stream << "@R13" << std::endl;
    file_stream << "D=M" << std::endl;
    file_stream << "@JUMP." << jump_counter << std::endl;
    file_stream << "D;JGT" << std::endl;
    decrementStackPointer();
    retrieveFromStack();
    pushConstant(0);
    file_stream << "(JUMP." << (jump_counter++) << ")" << std::endl;
}

void CodeWriter::writePush(const std::string &segment, int index) {
    file_stream << "// " << segment << " " << index << std::endl;
    if(segment == "constant"){
        pushConstant(index);
    } else if(segment == "temp"){
        int read_idx = 5 + index;
        file_stream << "@" << read_idx << std::endl;
        file_stream << "D=M" << std::endl;
        addToStack();
        incrementStackPointer();
    } else if (segment == "pointer"){
        write_pointer(segment, index);
        addToStack();
        incrementStackPointer();
    } else if(segment == "local" || segment == "argument" || segment == "this" || segment == "that"){
        std::string segment_translated = symbol_table.at(segment);
        pushSegment(segment_translated, index);
    } else if(segment == "static"){
        file_stream << "@" << base_file_name << "." << index << std::endl;
        file_stream << "D=M" << std::endl;
        addToStack();
        incrementStackPointer();
    } else {
        throw std::runtime_error("unexpected arguments");
    }
}

void CodeWriter::pop_pointer(const std::string& segment, int index){
    std::string segment_translated = (index == 0) ? "@THIS" : "@THAT";
    file_stream << segment_translated << std::endl;
    file_stream << "M=D" << std::endl;
}

void CodeWriter::write_pointer(const std::string& segment, int index){
    std::string segment_translated = (index == 0) ? "@THIS" : "@THAT";
    file_stream << segment_translated << std::endl;
    file_stream << "D=M" << std::endl;
}

void CodeWriter::writePop(const std::string &segment, int index) {
    file_stream << "// " << segment << " " << index << std::endl;
    if(segment == "temp"){
        decrementStackPointer();
        retrieveFromStack();
        int read_idx = 5 + index;
        file_stream << "@" << read_idx << std::endl;
        file_stream << "M=D" << std::endl;
    } else if (segment == "pointer"){
        decrementStackPointer();
        retrieveFromStack();
        pop_pointer(segment, index);
    } else if(segment == "local" || segment == "argument" || segment == "this" || segment == "that"){
        std::string segment_translated = symbol_table.at(segment);
        popSegment(segment_translated, index);
    } else if(segment == "static"){
        decrementStackPointer();
        retrieveFromStack();
        file_stream << "@" << base_file_name << "." << index << std::endl;
        file_stream << "M=D" << std::endl;
    } else {
        throw std::runtime_error("unexpected arguments");
    }
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
    size_t extension_idx = path.find_last_of('.');
    size_t slash_idx = path.find_last_of('/');
    return path.substr(slash_idx + 1, extension_idx - slash_idx - 1);
}

// labels are of the form label xxx
// if a label is not of a function we can write it directly
// ie (xxx)
// if a label is in a function we can write is as follow
// (functionName$label)
void CodeWriter::writeLabel(const std::string &label) {
    std::string extensionToLabel;
    if(!functions_on_stack.empty()){
        extensionToLabel = functions_on_stack.top() + "$";
    }
    file_stream << "(" << extensionToLabel << label << ")" << std::endl;
}

void CodeWriter::writeGoto(const std::string &label){
    std::string extensionToLabel;
    if(!functions_on_stack.empty()){
        extensionToLabel = functions_on_stack.top() + "$";
    }
    file_stream << "@" << extensionToLabel << label << std::endl;
    file_stream << "0;JMP" << std::endl;
}

void CodeWriter::writeIf(const std::string &label) {
    // remove the condition from the stack
    decrementStackPointer();
    retrieveFromStack();
    // write the possible address to jump to.
    std::string extensionToLabel;
    if(!functions_on_stack.empty()){
        extensionToLabel = functions_on_stack.top() + "$";
    }
    file_stream << "@" << extensionToLabel << label << std::endl;
    file_stream << "D;JNE" << std::endl;
}

void CodeWriter::writeFunction(const std::string &function_name, int nVars) {
    // add a new function on the stack. this function will be popped in writecall
    file_stream << "(" << function_name << ")" << std::endl;
    for(int i = 0;i < nVars;i++)
        pushConstant(0);
}

void CodeWriter::writeCall(const std::string &function_name, int nArgs) {
    int running_idx = function_label_to_running_integer[function_name];
    // stores the return address
    file_stream << "@" << function_name << "$" << running_idx << std::endl;
    file_stream << "D=A" << std::endl;
    addToStack();
    incrementStackPointer();
    file_stream << "@LCL" << std::endl;
    file_stream << "D=M" << std::endl;
    addToStack();
    incrementStackPointer();;
    // save the caller's ARG
    file_stream << "@ARG" << std::endl;
    file_stream << "D=M" << std::endl;
    addToStack();
    incrementStackPointer();;
    // save the caller's THIS
    file_stream << "@THIS" << std::endl;
    file_stream << "D=M" << std::endl;
    addToStack();
    incrementStackPointer();
    // save the caller's THAT
    file_stream << "@THAT" << std::endl;
    file_stream << "D=M" << std::endl;
    addToStack();
    incrementStackPointer();
    // ARG = SP - 5 - nARGS
    file_stream << "@SP" << std::endl;
    file_stream << "D=M" << std::endl;
    file_stream << "@ARG" << std::endl;
    file_stream << "M=D" << std::endl;
    file_stream << "@5" << std::endl;
    file_stream << "D=A" << std::endl;
    file_stream << "@ARG" << std::endl;
    file_stream << "M=M-D" << std::endl;
    file_stream << "@" << nArgs << std::endl;
    file_stream << "D=A" << std::endl;
    file_stream << "@ARG" << std::endl;
    file_stream << "M=M-D" << std::endl;
    // LCL = SP
    file_stream << "@SP" << std::endl;
    file_stream << "D=M" << std::endl;
    file_stream << "@LCL" << std::endl;
    file_stream << "M=D" << std::endl;
    // go to f
    file_stream << "@" << function_name << std::endl;
    file_stream << "0;JMP" << std::endl;
    // when f returns go back here
    file_stream << "(" << function_name << "$" << running_idx << ")"  << std::endl;
}

void CodeWriter::writeReturn() {

    // frame = LCL
    file_stream << "@LCL" << std::endl;
    file_stream << "D=M" << std::endl;
    file_stream << "@FRAME" << std::endl;
    file_stream << "M=D" << std::endl;

    // retAddress = *(frame-5)
    file_stream << "@FRAME" << std::endl;
    file_stream << "D=M" << std::endl;
    for(int i = 0; i < 5;i++) {
        file_stream << "D=D-1" << std::endl;
    }
    file_stream << "A=D" << std::endl;
    file_stream << "D=A" << std::endl;
    file_stream << "@RETURN_ADDRESS" << std::endl;
    file_stream << "M=D" << std::endl;
    // *ARG = POP()
    decrementStackPointer();
    retrieveFromStack();
    file_stream << "@ARG" << std::endl;
    file_stream << "A=M" << std::endl;
    file_stream << "M=D" << std::endl;
    // SP = ARG + 1
    file_stream << "@ARG" << std::endl;
    file_stream << "A=M" << std::endl;
    file_stream << "D=A+1" << std::endl;
    file_stream << "@SP" << std::endl;
    file_stream << "M=D" << std::endl;
    // THAT = *(frame - 1)
    file_stream << "@FRAME" << std::endl;
    file_stream << "D=M" << std::endl;
    for(int i = 0;i < 1;i++)
        file_stream << "D=D-1" << std::endl;
    file_stream << "A=D" << std::endl;
    file_stream << "D=M" << std::endl;
    file_stream << "@THAT" << std::endl;
    file_stream << "M=D" << std::endl;
    // THIS = *(frame - 2)
    file_stream << "@FRAME" << std::endl;
    file_stream << "D=M" << std::endl;
    for(int i = 0;i < 2;i++)
        file_stream << "D=D-1" << std::endl;
    file_stream << "A=D" << std::endl;
    file_stream << "D=M" << std::endl;
    file_stream << "@THIS" << std::endl;
    file_stream << "M=D" << std::endl;
    // ARG =  *(frame - 3)
    file_stream << "@FRAME" << std::endl;
    file_stream << "D=M" << std::endl;
    for(int i = 0;i < 3;i++)
        file_stream << "D=D-1" << std::endl;
    file_stream << "A=D" << std::endl;
    file_stream << "D=M" << std::endl;
    file_stream << "@ARG" << std::endl;
    file_stream << "M=D" << std::endl;
    // LCL =  *(frame - 4)
    file_stream << "@FRAME" << std::endl;
    file_stream << "D=M" << std::endl;
    for(int i = 0;i < 4;i++)
        file_stream << "D=D-1" << std::endl;
    file_stream << "A=D" << std::endl;
    file_stream << "D=M" << std::endl;
    file_stream << "@LCL" << std::endl;
    file_stream << "M=D" << std::endl;
    // goto retAddr
    file_stream << "@RETURN_ADDRESS" << std::endl;
    file_stream << "A=M" << std::endl;
    file_stream << "0;JMP" << std::endl;
}

void CodeWriter::bootStrapCode() {
    file_stream << "@256" << std::endl;
    file_stream << "D=A" << std::endl;
    file_stream << "@SP" << std::endl;
    file_stream << "M=D" << std::endl;
    // sys.init is the function we start off with.
    writeCall("sys.init", 0);
}
