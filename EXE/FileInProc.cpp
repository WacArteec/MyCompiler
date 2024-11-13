#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "FileInProc.h"
#include "../enum.h"
#include "procstruct.h"

unsigned int FileSize(FILE* file);

void ProcInput(struct Processor* mach_code)
{
//$$$ printf("After entering in proc %d \n", __LINE__);

    FILE* code_file = fopen(code_proc_file, "rb");
$$$ assert(code_file);

    mach_code->count_cmd = FileSize(code_file)/sizeof(int);

//$$$ printf("\ncount_cmd = %d \n", mach_code->count_cmd);

    mach_code->code = (int*) calloc(mach_code->count_cmd, sizeof(int));
$$$ assert(mach_code->code);

    fread(mach_code->code, sizeof(int), mach_code->count_cmd, code_file);

    fclose(code_file);
}

unsigned int FileSize(FILE* file)
{
    int fseek_proof = fseek(file, 0, SEEK_END);
$$$ assert(fseek_proof + 1);

    unsigned int count_symb_in_file = ftell(file);

    rewind(file);

    return count_symb_in_file;
}