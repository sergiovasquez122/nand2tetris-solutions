// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed.
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.
//
(SETUP)
@SCREEN
D=A
@arr
M=D

// outer_loop_stopper = 32
@256
D=A
@outer_loop_stopper
M=D

// inner_loop_stopper = 32
@32
D=A
@inner_loop_stopper
M=D
@0
D=A
@i
M=D
(CHECK_KBD)
@i
M=0
@row_shift
M=0
@j
M=0
@KBD
D=M
@OUTER_LOOP
D;JGT


(OUTER_LOOP_WHITE)
@outer_loop_stopper
D=M
@i
D=D-M
@CHECK_KBD
D;JEQ
// j = 0
@j
M=0
(INNER_LOOP_WHITE)
@inner_loop_stopper
D=M
@j
D=D-M
@BEGIN_LOOP_WHITE
D;JNE
@i
M=M+1
@32
D=A
@row_shift
M=D+M
@OUTER_LOOP_WHITE
0;JMP
(BEGIN_LOOP_WHITE)
@arr
D=M
@row_shift
D=D+M
@j
A=D+M
M=0
@j
M=M+1
@INNER_LOOP_WHITE
0;JMP


(OUTER_LOOP)
@outer_loop_stopper
D=M
@i
D=D-M
@CHECK_KBD
D;JEQ
// j = 0
@0
D=A
@j
M=D
(INNER_LOOP)
@inner_loop_stopper
D=M
@j
D=D-M
@BEGIN_LOOP
D;JNE
@i
M=M+1
@32
D=A
@row_shift
M=D+M
@OUTER_LOOP
0;JMP
(BEGIN_LOOP)
@arr
D=M
@row_shift
D=D+M
@j
A=D+M
M=-1
@j
M=M+1
@INNER_LOOP
0;JMP
