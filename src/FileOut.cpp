#include <stdio.h>
#include <assert.h>

#include "FileOut.h"
#include "structs_proc.h"
#include "enum.h"

void CodeOut(struct Processor* asmer);
void CountOut(struct Processor* asmer);

void FileOut(struct Processor* asmer)
{
$$$ assert(asmer);

    CodeOut(asmer);
    CountOut(asmer);
}

void CodeOut(struct Processor* asmer)
{
$$$ assert(asmer);

    FILE* code_file = fopen(code_proc_file, "wb");
$$$ assert(code_file);

    fwrite(asmer->code, sizeof(int), asmer->count_comands, code_file);

//$$$ printf("array: \n");
//$$$ for(int i = 0; i < asmer->count_comands; i++)
//$$$ {
//$$$ printf("asmer->code[%d] = %d \n", i, asmer->code[i]);
//$$$ }

//$$$ printf("\n %d \n", __LINE__);

//$$$ printf("asmer->count_comands = %d\n", asmer->count_comands);

//$$$ printf("%d \n", __LINE__);

    int err_close = !fclose(code_file);
$$$ assert(err_close);
}

void CountOut(struct Processor* asmer)
{
$$$ assert(asmer);

    FILE* count_file = fopen(count_proc_file, "wb");
$$$ assert(count_file);

    fprintf(count_file, "%d", asmer->count_comands);

    int err_close = !fclose(count_file);
$$$ assert(err_close);
}

