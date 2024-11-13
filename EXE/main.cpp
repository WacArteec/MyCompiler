#include <stdio.h>

#include "FileInProc.h"
#include "Implementer.h"
#include "procstruct.h"

int main()
{
    struct Processor mach_code = {};

    ProcInput(&mach_code);

    int result = Executor(&mach_code);
    if(result != 0)
        printf("somethung got wrong");

    return 0;
}