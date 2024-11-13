#define $$$

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

#include "FileInputer.h"
#include "asmstruct.h"

void FileInput(struct Assembler* mach_code);
void ReplaceSymbol(struct Assembler* mach_code);
int StrCounter(struct Assembler* mach_code);
unsigned int MyFstat(struct Assembler* mach_code);

void Input(struct Assembler* mach_code)
{
    FileInput(mach_code);

    mach_code->count_lines = StrCounter(mach_code);

    ReplaceSymbol(mach_code);

}

void FileInput(struct Assembler* mach_code)
{
    mach_code->file = fopen(text_comp_file, "rb");
$$$ assert(mach_code->file);

// fstat

    mach_code->count_elements = MyFstat(mach_code);

    mach_code->text = (char*) calloc(mach_code->count_elements + 1, sizeof(char));
$$$ assert(mach_code->text);

    size_t fread_check = fread(mach_code->text, sizeof(char), mach_code->count_elements, mach_code->file);
$$$ assert(mach_code->count_elements == fread_check);

    mach_code->text[mach_code->count_elements] = '\0';

    int errclose = !fclose(mach_code->file);
$$$ assert(errclose); //!NDEBUG! !change to if!
}

int StrCounter(struct Assembler* mach_code)
{
    int count_of_lines = 1;

    for(size_t i = 0; i < mach_code->count_elements; i++)
    {
        if(mach_code->text[i] == '\n')
        {
            count_of_lines += 1;
        }
    }

    return count_of_lines;
}

void ReplaceSymbol(struct Assembler* mach_code)
{
    for(size_t i = 0; i < mach_code->count_elements; i++)
    {
        if(mach_code->text[i] == '\r')
        {
            mach_code->text[i] = '\0';
            mach_code->text[i+1] = '\0';
        }
    }

}

unsigned int MyFstat(struct Assembler* mach_code)
{
    int fseek_proof = fseek(mach_code->file, 0, SEEK_END);
$$$ assert(fseek_proof + 1);

    unsigned int count_symb_in_file = ftell(mach_code->file);

$$$ if(mach_code->count_elements == (size_t)(-1L))
        printf("!File Size is 0! : %s", strerror(errno));

    rewind(mach_code->file);

    return count_symb_in_file;
}
