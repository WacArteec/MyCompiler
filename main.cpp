#include <stdio.h>

#include <mumuCompiler.h>
#include "Implementer.h"
#include "structs_proc.h"
#include "FileInputer.h"
#include "enum.h"

int main()
{
    MumuCompiler();

    int res = Implementer();
    if(res != 0) printf("smth get wrong");

    return 0;
}


