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

(INIT)
    @8192
    D=A
    @cnt
    M=D

    @SCREEN
    D=A
    @scr
    M=D

    @KBD
    D=M
    @PUSHED
    D;JNE

    @flag
    M=0

    @LOOP
    0;JMP

(PUSHED)
    @flag
    M=1

    @LOOP
    0;JMP

(LOOP)
    @flag
    D=M
    @FILL
    D;JNE

    @scr
    A=M
    M=0
    @NEXT
    0;JMP

(FILL)
    @scr
    A=M
    M=-1
    @NEXT
    0;JMP

(NEXT)
    @scr
    M=M+1

    @cnt
    MD=M-1
    @INIT
    D;JEQ

    @LOOP
    0;JMP

