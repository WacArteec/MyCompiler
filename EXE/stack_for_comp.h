#ifndef STACK_FOR_COMP_H
#define STACK_FOR_COMP_H

enum Stacks
{
    general = 1,
    calls = 2
};

void SPush(int num, int in);
int SPull(int num);

#endif // STACK_FOR_COMP_H
