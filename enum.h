#ifndef ENUM_H
#define ENUM_H

#define $$$

#define code_proc_file "../Code.bin"

enum Cmd
{
    CMD_HLT = -1,
    CMD_ERR,
    CMD_PUSH = 1,
    CMD_OUT,
    CMD_ADD,
    CMD_MULT,
    CMD_SUB,
    CMD_DIV,
    CMD_JMP,
    CMD_POP,
    CMD_JA,
    CMD_JB,
    CMD_JEQ,
    CMD_CALL,
    CMD_RET,
    CMD_FSQRT,
    CMD_INS,
    CMD_DRAW,
    CMD_MEOW,
    CMD_PRINT
};

#endif // ENUM_H