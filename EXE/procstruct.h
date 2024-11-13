#ifndef PROCSTRUCT_H
#define PROCSTRUCT_H

#include <stdlib.h>

struct Processor
{
    int* code = NULL;
    
    unsigned int count_cmd = 0;

    int regs[4] = {};
    int RAM[100] = {};
};

#endif //PROCSTRUCT_H