#include <stdio.h>
#include <assert.h>

#include "FileInProc.h"
#include "enum.h"

void ProcInput(struct Implement* mach_code)
{
    FILE* count_file = fopen(count_proc_file, "rb");
$$$ assert(count_file);

    fscanf(count_file, "%u", &(mach_code->count_cmd));
//$$$ printf("After entering in proc %d \n", __LINE__);

    mach_code->code = (int*) calloc(mach_code->count_cmd, sizeof(int));
$$$ assert(mach_code->code);

    FILE* code_file = fopen(code_proc_file, "rb");
$$$ assert(code_file);

    fread(mach_code->code, sizeof(int), mach_code->count_cmd, code_file);

    fclose(count_file);
    fclose(code_file);
}
