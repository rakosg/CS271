// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

    @R2
    M=0 //R2 = 0
    
(ADD_LOOP)
    @R0
    D=M
    @END
    D;JLE

    @R1
    D=M //D = R1
    @R2 // M = R2
    M=M+D //R2 = R2 + R1
    
    @R0 
    M=M-1 //R0 = R0-1

    @ADD_LOOP
    0;JMP //Loop back if R0 is greater than 0
    
(END)
    @END
    0;JMP
