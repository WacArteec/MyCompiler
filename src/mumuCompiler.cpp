#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

/*jmp
add
                push [3 + rax]              ;ddawdawd
111 00010 | 0000 0011 | 0000 0001
hlt
pop

str
len
cmd_code
arg
reg*/

#include "mumuCompiler.h"
#include "ComparStr.h"
#include "structs_proc.h"
#include "FileOut.h"
#include "enum.h"
#include "FileInputer.h"

int NumLen(int a);
void CodeAndSkip (int comand, struct Processor* asmer);
void CodeIt(int comand, struct Processor* asmer);
void Skip(struct Processor* asmer);
void WritePush(struct Processor* asmer);
void TypicalJump(struct Processor* asmer, int miss);
void WritePopIt(struct Processor* asmer);

void MumuCompiler()
{
    struct Processor asmer = {};

    Input(&asmer);

    asmer.labels = (Marks*) calloc(20, sizeof(Marks));
$$$ assert(asmer.labels);

    int need_memory = 4 * asmer.count_lines;

    for(int k = 0; k < 2; k++)
    {
        asmer.code = (int*) calloc(need_memory, sizeof(int));
$$$     assert(asmer.code);

        need_memory = 0;
        asmer.count_comands = 0;
//$$$ printf("asmer.countlines = %u \n", asmer.count_lines);
//$$$ printf(" %d asmer.countelements = %u \n", __LINE__, asmer.count_elements);
//$$$ printf("\n asmer.text = %d before compile \n", asmer.text);

        for(unsigned int i = 0; i < asmer.count_lines; i++)
        {
//$$$         printf("count_comands = %d com = ", asmer.count_comands);


            while(!isalpha(*(asmer.text)) && *(asmer.text) != '\0' && *(asmer.text) != ':')
                asmer.text++;


            if(strncmp(asmer.text, "push", 4) == 0)
            {
//$$$ printf("push \n");
                need_memory += 4;

                CodeIt(cmd_push, &asmer);

                WritePush(&asmer);

                Skip(&asmer);
            }

            else if(strncmp(asmer.text, "pop", 3) == 0)
            {
//$$$ printf("pop \n");
                need_memory += 4;

                CodeIt(cmd_pop, &asmer);

                WritePopIt(&asmer);

                Skip(&asmer);
            }

            else if(strncmp(asmer.text, "out", 3) == 0)
            {
//$$$ printf("out \n");
                need_memory++;

                CodeAndSkip (cmd_out, &asmer);
            }

            else if(strncmp(asmer.text, "add", sizeof("add") - 1) == 0)         //
            {
//$$$ printf("add \n");
                need_memory++;

                CodeAndSkip (cmd_add, &asmer);
            }

            else if(strncmp(asmer.text, "mult", 4) == 0)
            {
//$$$ printf("mult \n");
                need_memory++;

                CodeAndSkip (cmd_mult, &asmer);
            }

            else if(strncmp(asmer.text, "sub", 3) == 0)
            {
//$$$ printf("sub \n");
                need_memory++;

                CodeAndSkip(cmd_sub, &asmer);
            }

            else if(strncmp(asmer.text, "idiv", 4) == 0)
            {
//$$$ printf("idiv \n");
                need_memory++;

                CodeAndSkip(cmd_div, &asmer);
            }

            else if(strncmp(asmer.text, "fsqrt", 5) == 0)
            {
//$$$ printf("fsqrt \n");
                need_memory++;

                CodeAndSkip(cmd_fsqrt, &asmer);
            }

            else if(strncmp(asmer.text, "ins", 3) == 0)
            {
//$$$ printf("ins \n");
                need_memory++;

                CodeAndSkip(cmd_ins, &asmer);
            }

            else if(strncmp(asmer.text, "draw", 4) == 0)
            {
//$$$ printf("draw \n");
                need_memory++;

                CodeAndSkip(cmd_draw, &asmer);
            }

            else if(strncmp(asmer.text, "hlt", 3) == 0)
            {
//$$$ printf("hlt \n");
                need_memory++;

                CodeAndSkip(cmd_hlt, &asmer);
            }

            else if(strncmp(asmer.text, "jmp", 3) == 0)
            {
//$$$ printf("jmp \n");
                need_memory += 2;

                CodeIt(cmd_jmp, &asmer);

                TypicalJump(&asmer, 3);

                Skip(&asmer);
            }

            else if(strncmp(asmer.text, "ja", 2) == 0)
            {
//$$$ printf("ja \n");
                need_memory += 2;

                CodeIt(cmd_ja, &asmer);

                TypicalJump(&asmer, 2);

                Skip(&asmer);
            }

            else if(strncmp(asmer.text, "jb", 2) == 0)
            {
//$$$ printf("jb \n");
                need_memory += 2;

                CodeIt(cmd_jb, &asmer);

                TypicalJump(&asmer, 2);

                Skip(&asmer);
            }

            else if(strncmp(asmer.text, "jeq", 3) == 0)
            {
//$$$ printf("jeq \n");
                need_memory += 2;

                CodeIt(cmd_jeq, &asmer);

                TypicalJump(&asmer, 3);

                Skip(&asmer);
            }

            else if(strncmp(asmer.text, "call", 4) == 0)
            {
//$$$ printf("call \n");
                need_memory += 2;

                CodeIt(cmd_call, &asmer);

                TypicalJump(&asmer, 4);

                Skip(&asmer);
            }

            else if(strncmp(asmer.text, "ret", 3) == 0)
            {
//$$$ printf("ret \n");
                need_memory += 1;

                CodeAndSkip(cmd_ret, &asmer);
            }

            else if(strncmp(asmer.text, "meow", 4) == 0)
            {
//$$$ printf("meow \n");
                need_memory += 1;

                CodeAndSkip(cmd_meow, &asmer);
            }

            else if(*(asmer.text) == ':')
            {
//$$$ printf("LABEL! \n");
                asmer.text++;

                asmer.labels[asmer.count_labels].name = (char*) calloc(20, sizeof(char));

                for(int j = 0; j < 20; j++)
                {
                    //$$$ printf(" metka");
                    if(isalpha(*(asmer.text + j)) != 0)
                    {
                        //$$$ printf(" %s", asmer.text+j);
                        asmer.labels[asmer.count_labels].name[j] = asmer.text[j];
                        //$$$ printf(" %d\n", __LINE__);
                    }

                    else
                    {
                        asmer.labels[asmer.count_labels].ip = asmer.count_comands - 1;

                        asmer.count_labels++;

                        break;
                    }
                }

                Skip(&asmer);
            }

            else if(*(asmer.text) == '\0')
                asmer.text += 2;

            else
                printf("can't found a command \n");
        }

//$$$ printf("\n asmer.text = %d after compile \n", asmer.text);
    asmer.text -= (asmer.count_elements + 2);
    }

//$$$ printf("%d After compile \n", __LINE__);
    FileOut(&asmer);
}

int NumLen(int a)
{
    int counter = 0;

    while(a>0)
    {
        counter++;
        a/=10;
    }

    return counter;
}

void CodeAndSkip(int comand, struct Processor* asmer)
{
$$$ assert(asmer);

    CodeIt(comand, asmer);

    Skip(asmer);
}

void CodeIt(int comand, struct Processor* asmer)
{
$$$ assert(asmer);

    asmer->code[asmer->count_comands] = comand;
    asmer->count_comands++;
}

void Skip(struct Processor* asmer)
{
$$$ assert(asmer);

    while(*(asmer->text) != '\0')
    {
        asmer->text++;
    }
    asmer->text += 2;
}

void WritePush(struct Processor* asmer)
{
    asmer->text += 4;

    while(isalnum(*(asmer->text)) == 0 && *(asmer->text) != '[')
            asmer->text++;

    if(*(asmer->text) == '[')
        asmer->code[asmer->count_comands] += 4;

    while(isalnum(*(asmer->text)) == 0)
        asmer->text++;

    if(isalpha(*(asmer->text)) != 0)
    {
        asmer->code[asmer->count_comands] += 2;

        if(strncmp(asmer->text, "AX", 2) == 0)
        {
            asmer->text += 2;

            asmer->code[asmer->count_comands + 1] = 1;
        }

        else if(strncmp(asmer->text, "BX", 2) == 0)
        {
            asmer->text += 2;

            asmer->code[asmer->count_comands + 1] = 2;
        }

        else if(strncmp(asmer->text, "CX", 2) == 0)
        {
            asmer->text += 2;

            asmer->code[asmer->count_comands + 1] = 3;
        }

        else if(strncmp(asmer->text, "DX", 2) == 0)
        {
            asmer->text += 2;

            asmer->code[asmer->count_comands + 1] = 4;
        }


        else
        {
            printf("ERROR: This register does not exists! \n %s", asmer->text);
            exit(1);
        }

        if(*(asmer->text) != '+')
        {
            asmer->code[asmer->count_comands + 2] = 0;
            asmer->count_comands += 3;
        }
    }

    int in = 0;
    if(isdigit(*(asmer->text)) != 0)
    {
        asmer->code[asmer->count_comands] += 1;

        asmer->count_comands += 2;

        in = atoi(asmer->text);

        for(int j = 0; j < NumLen(in); j++)
            asmer->text++;

        asmer->code[asmer->count_comands] = in;
        asmer->count_comands++;
    }

    if(asmer->code[asmer->count_comands - 3] == 4)
    {
        printf("Error: you can't operate with RAM without number of position \n %s", (asmer->text - NumLen(in) - 4));
    }
}

void TypicalJump(struct Processor* asmer, int miss)
{
    asmer->text += miss;

    while(isalpha(*(asmer->text)) == 0)
        asmer->text++;

    asmer->code[asmer->count_comands] = -1;

    for(int j = 0; j < asmer->count_labels; j++)
    {
        if(strncmp(asmer->text, asmer->labels[j].name, strlen(asmer->labels[j].name)) == 0)
        {
            asmer->code[asmer->count_comands] = asmer->labels[j].ip;

            break;
        }

    }

    asmer->count_comands++;
}

void WritePopIt(struct Processor* asmer)
{
    asmer->text += 3;

    while(isalnum(*(asmer->text)) == 0 && *(asmer->text) != '[')
        asmer->text++;

    if(*(asmer->text) == '[')
        asmer->code[asmer->count_comands] += 4;

    while(isalnum(*(asmer->text)) == 0)
        asmer->text++;

    if(isalpha(*(asmer->text)) != 0)
    {
        asmer->code[asmer->count_comands] += 2;

        if(strncmp(asmer->text, "AX", 2) == 0)
        {
            asmer->text += 2;
//$$$ printf(" %d Pop in AX \n", __LINE__);

            asmer->code[asmer->count_comands + 1] = 1;
        }

        else if(strncmp(asmer->text, "BX", 2) == 0)
        {
            asmer->text += 2;
//$$$ printf(" %d Pop in BX \n", __LINE__);

            asmer->code[asmer->count_comands + 1] = 2;
        }

        else if(strncmp(asmer->text, "CX", 2) == 0)
        {
            asmer->text += 2;
//$$$ printf(" %d Pop in CX \n", __LINE__);

            asmer->code[asmer->count_comands + 1] = 3;
        }

        else if(strncmp(asmer->text, "DX", 2) == 0)
        {
            asmer->text += 2;
//$$$ printf(" %d Pop in DX \n", __LINE__);

            asmer->code[asmer->count_comands + 1] = 4;
        }

        else
        {
            printf("ERROR: This register does not exists! \n %s", asmer->text);
            exit(1);
        }

        if(*(asmer->text) != '+')
        {
            asmer->code[asmer->count_comands + 2] = 0;
            asmer->count_comands += 3;
        }
    }

    int in = 0;
    if(isdigit(*(asmer->text)) != 0 )
    {
        asmer->code[asmer->count_comands] += 1;

        asmer->count_comands += 2;

        in = atoi(asmer->text);

        for(int j = 0; j < NumLen(in); j++)
            asmer->text++;

        asmer->code[asmer->count_comands] = in;
        asmer->count_comands++;
    }

    if(asmer->code[asmer->count_comands - 3] == 1)
    {
        printf("Error: you can't pop into number \n %s", (asmer->text - NumLen(in) - 4));
    }

    if(asmer->code[asmer->count_comands - 3] == 3)
    {
        printf("Error: you can't pop into register number \n %s", (asmer->text - NumLen(in) - 4));
    }

    if(asmer->code[asmer->count_comands - 3] == 4)
    {
        printf("Error: you can't operate with RAM without number of position \n %s", (asmer->text - NumLen(in) - 4));
    }
}
