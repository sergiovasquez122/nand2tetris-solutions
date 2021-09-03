// constant 111
@111
D=A
@SP
A=M
M=D
@SP
M=M+1
// constant 333
@333
D=A
@SP
A=M
M=D
@SP
M=M+1
// constant 888
@888
D=A
@SP
A=M
M=D
@SP
M=M+1
// static 8
@SP
M=M-1
@SP
A=M
D=M
@StaticTest.8
M=D
// static 3
@SP
M=M-1
@SP
A=M
D=M
@StaticTest.3
M=D
// static 1
@SP
M=M-1
@SP
A=M
D=M
@StaticTest.1
M=D
// static 3
@StaticTest.3
D=M
@SP
A=M
M=D
@SP
M=M+1
// static 1
@StaticTest.1
D=M
@SP
A=M
M=D
@SP
M=M+1
// sub
@SP
M=M-1
@SP
A=M
D=M
@R13
M=D
@SP
M=M-1
@SP
A=M
D=M
@R13
D=D-M
@SP
A=M
M=D
@SP
M=M+1
// static 8
@StaticTest.8
D=M
@SP
A=M
M=D
@SP
M=M+1
// add
@SP
M=M-1
@SP
A=M
D=M
@R13
M=D
@SP
M=M-1
@SP
A=M
D=M
@R13
D=D+M
@SP
A=M
M=D
@SP
M=M+1
