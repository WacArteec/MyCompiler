#include <stdio.h>
#include <math.h>

#include "Implementer.h"
#include "stack_for_comp.h"
#include "../enum.h"
#include "FileInProc.h"
#include "procstruct.h"

int Executor(struct Processor* mach_code)
{

//$$$ printf("In proc %d mach_code.count_cmd  = %u \n", __LINE__, mach_code.count_cmd);

    for(unsigned int ip = 0; ip < mach_code->count_cmd; ip++)
    {
$$$     printf("mach_code.code[%u] = %d ==", ip, mach_code->code[ip]);

        switch(mach_code->code[ip]) // ������� ������ ������� � �������
        {
            case CMD_PUSH:
            {
                ip++;

$$$ printf("Push \n");
                int push_it = 0;

                if(mach_code->code[ip] & 1)
                    push_it += mach_code->code[ip + 2];

                if(mach_code->code[ip] & 2)
                    push_it += mach_code->regs[mach_code->code[ip + 1] - 1];

                if(mach_code->code[ip] & 4)
                    push_it = mach_code->RAM[push_it];

                SPush(general, push_it);

                ip += 2;

                break;
            }
            case CMD_POP:
            {
                ip++;

$$$ printf("Pop \n");

//$$$             printf("\t RAM[%d] \n", mach_code.code[ip+2]);
                if(mach_code->code[ip] == 2)
                {
                    $$$ printf("XX\n");
                    mach_code->regs[mach_code->code[ip + 1] - 1] = SPull(general);
                }

                else if(mach_code->code[ip] == 5)
                    mach_code->RAM[mach_code->code[ip + 2]] = SPull(general);

                else if(mach_code->code[ip] == 6 || mach_code->code[ip] == 7)
                    mach_code->RAM[mach_code->code[ip + 2] + mach_code->regs[mach_code->code[ip + 1] - 1]] = SPull(general);

                ip += 2;
            break;
            }
            case CMD_OUT:
            {
$$$ printf("Out \n");
                printf("Your number = %d \n", SPull(general));

                break;
            }

            case CMD_ADD:
            {
                int addict = SPull(general);

$$$ printf("Add \n");

                SPush(general, addict + SPull(general));

            break;
            }

            case CMD_MULT:
            {
$$$ printf("Mult \n");
                SPush(general, SPull(general) * SPull(general));

            break;
            }

            case CMD_SUB:
            {
$$$ printf("Sub \n");
                int substract = SPull(general);
                SPush(general, SPull(general) - substract);

            break;
            }

            case CMD_DIV:
            {
$$$ printf("Div \n");
                int divide = SPull(general);
                SPush(general, SPull(general) / divide);

            break;
            }

            case CMD_FSQRT:
            {
$$$ printf("Fsqrt \n");
                int square = SPull(general);
                SPush(general, (int)(square));

            break;
            }

            case CMD_DRAW:
            {
$$$ printf("Draw \n");
                for(int i = 0; i < 10; i++)
                {
                    for(int j = 0; j < 10; j++)
                    {
                        if(mach_code->RAM[10*i+j] == 0)
                            printf("* ");
                        else
                            printf("# ");
                    }
                    printf("\n");
                }

            break;
            }

            case CMD_INS:
            {
$$$ printf("Ins \n");
                int insert = 0;

                printf("Insert your num\n");
                scanf("%d", &insert);

                SPush(general, insert);

            break;
            }

            case CMD_JMP:
            {
$$$ printf("Jmp \n");
                ip++;

                ip = mach_code->code[ip];
$$$ printf("to %d", ip+1);

            break;
            }

            case CMD_JA:
            {
$$$ printf("Ja \n");
                ip++;

                int cmp = SPull(general);

                if(cmp < SPull(general))
                    {
                        ip = mach_code->code[ip];
$$$ printf("to %d", ip+1);
                    }

            break;
            }

            case CMD_JB:
            {
$$$ printf("Jb ");
                ip++;

                int cmp = SPull(general);

                if(cmp > SPull(general))
                    {
                        ip = mach_code->code[ip];
$$$ printf("to %d \n", ip+1);
                    }

                else
                    ip++;

            break;
            }

            case CMD_JEQ:
            {
$$$ printf("Jeq ");
                ip++;

                int cmp = SPull(general);

                if(cmp == SPull(general))
                    {
                        ip = mach_code->code[ip];
$$$ printf("to %d \n", ip+1);
                    }

            break;
            }

            case CMD_CALL:
            {
$$$ printf("Call \n");
                ip++;

                SPush(calls, ip);

                ip = mach_code->code[ip];
$$$ printf(" to %d \n", ip+1);


            break;
            }

            case CMD_RET:
            {
$$$ printf("ret");
                int transfer = SPull(calls);
                ip = transfer;
$$$ printf(" transfer = %d \n", transfer);

            break;
            }

            case CMD_MEOW:
            {
                int count_meows = SPull(general);

                for(int i = 0; i < count_meows; i++)
                    printf("\n\tmeoooow");
            }

            case CMD_HLT:
            {
                return 0;

            break;
            }

            case CMD_ERR:
            {
                return 1;

            break;
            }

            default:
            {
                printf("error");
                return 1;

            break;
            }
        }
    }

    return 1;
}
