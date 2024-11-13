#include "asmstruct.h"
#include "FileOut.h"
#include "FileInputer.h"
#include "mumuCompiler.h"

int main()
{
    struct Assembler asmer = {};

    Input(&asmer);

    MumuCompiler(&asmer);

    FileOut(&asmer);

    return 0;
}