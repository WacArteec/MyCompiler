#ifndef ASMSTRUCT_H
#define ASMSTRUCT_H

#define $$$

#define text_comp_file "../Text.asm"
#define count_proc_file "Count.bin"

#include <stdio.h>
#include <stdlib.h>

struct Marks
{
    char *name = NULL;
    //len
    int ip = 0;
};

struct Assembler
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

#endif // ASMSTRUCT_H