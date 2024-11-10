#ifndef ENUM_H
#define ENUM_H

#define $$$

#define text_comp_file "Text.asm"
#define code_proc_file "Code.bin"
#define count_proc_file "Count.bin"

enum Cmd
{
    cmd_hlt = -1,
    cmd_push = 1,
    cmd_out,
    cmd_add,
    cmd_mult,
    cmd_sub,
    cmd_div,
    cmd_jmp,
    cmd_pop,
    cmd_ja,
    cmd_jb,
    cmd_jeq,
    cmd_call,
    cmd_ret,
    cmd_fsqrt,
    cmd_ins,
    cmd_draw,
    cmd_meow
};

struct Marks
{
    char *name = NULL;
    //len
    int ip = 0;
};

struct Processor
{
    char* text = NULL;

    unsigned int count_lines = 0;
    unsigned int count_elements = 0;

    FILE* file = NULL;
    const char* file_name = "MyCode.asm";

    int* code = NULL;
    unsigned int count_comands = 0;

    Marks* labels = NULL;
    int count_labels = 0;
};

struct Implement
{
    int* code = NULL;
    unsigned int count_cmd = 0;
    int regs[4] = {};
};

#endif // ENUM_H
