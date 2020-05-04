#include "ram_machine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int execute_command(Command *cmd_list, size_t cmd_count, int *instruction_pointer, FILE *input_fp, int *memory)
{
    //ogarnij jaka to komenda
    //jeżeli jest to instrukcja skoku (jump, jzero, jgtz), to skocz do etykiety (zmień licznik komend na ten z etykietą)
    //uzyj do tego funkcji get_matching_label
    //jeśli nie, to wykonaj resztę komend
    //po czym zwiększ licznik komend +1
    //jeśli komenda nie rozpoznana, zakończ program
    
    if (strcmp(cmd_list[*instruction_pointer].instruction, "JUMP") == 0)
    {
        size_t tmp;
        tmp = get_matching_label(cmd_list, cmd_count,cmd_list[*instruction_pointer]);
        *instruction_pointer = tmp;
        return 0;
    }
    else if (strcmp(cmd_list[*instruction_pointer].instruction, "JZERO") == 0)
    {
        if (memory[0] == 0)
        {
            size_t tmp;
            tmp = get_matching_label(cmd_list, cmd_count,cmd_list[*instruction_pointer]);
            *instruction_pointer = tmp;
        }
        else
            *instruction_pointer += 1;

        return 0;
    }
    else if (strcmp(cmd_list[*instruction_pointer].instruction, "JGTZ") == 0)
    {
        if (memory[0] > 0)
        {
            size_t tmp;
            tmp = get_matching_label(cmd_list, cmd_count,cmd_list[*instruction_pointer]);
            *instruction_pointer = tmp;
        }
        else
            *instruction_pointer += 1;

        return 0;
    }
    //end of jump instructions, incrementing ip at the very end of the function
    else if (strcmp(cmd_list[*instruction_pointer].instruction, "LOAD") == 0)
    {
        if (cmd_list[*instruction_pointer].operand == '*')
        {
            int tmp = memory[cmd_list[*instruction_pointer].dest_adress];
            memory[0] = memory[tmp];
        }
        else if (cmd_list[*instruction_pointer].operand == '=')
            memory[0] = cmd_list[*instruction_pointer].dest_adress;
        else
            memory[0] = memory[cmd_list[*instruction_pointer].dest_adress];
    }
    else if (strcmp(cmd_list[*instruction_pointer].instruction, "STORE") == 0)
    {
        if (cmd_list[*instruction_pointer].operand == '*')
        {
            int tmp = memory[cmd_list[*instruction_pointer].dest_adress];
            memory[tmp] = memory[0];
        }
        else if (cmd_list[*instruction_pointer].operand == '=')
        {
            fprintf(stderr, "'=' OPERAND WITH STORE INSTRUCTION ERROR");
            exit(EXIT_FAILURE);
        }
        else
            memory[cmd_list[*instruction_pointer].dest_adress] = memory[0];
    }
    else if (strcmp(cmd_list[*instruction_pointer].instruction, "ADD") == 0)
    {
        if (cmd_list[*instruction_pointer].operand == '*')
        {
            int tmp = memory[cmd_list[*instruction_pointer].dest_adress];
            memory[0] += memory[tmp];
        }
        else if (cmd_list[*instruction_pointer].operand == '=')
        {
            memory[0] += cmd_list[*instruction_pointer].dest_adress;
        }
        else
            memory[0] += memory[cmd_list[*instruction_pointer].dest_adress];
    }
    else if (strcmp(cmd_list[*instruction_pointer].instruction, "SUB") == 0)
    {
        if (cmd_list[*instruction_pointer].operand == '*')
        {
            int tmp = memory[cmd_list[*instruction_pointer].dest_adress];
            memory[0] -= memory[tmp];
        }
        else if (cmd_list[*instruction_pointer].operand == '=')
        {
            memory[0] -= cmd_list[*instruction_pointer].dest_adress;
        }
        else
            memory[0] -= memory[cmd_list[*instruction_pointer].dest_adress];
    }
    else if (strcmp(cmd_list[*instruction_pointer].instruction, "MULT") == 0)
    {
        if (cmd_list[*instruction_pointer].operand == '*')
        {
            int tmp = memory[cmd_list[*instruction_pointer].dest_adress];
            memory[0] *= memory[tmp];
        }
        else if (cmd_list[*instruction_pointer].operand == '=')
        {
            memory[0] *= cmd_list[*instruction_pointer].dest_adress;
        }
        else
            memory[0] *= memory[cmd_list[*instruction_pointer].dest_adress];
    }
    else if (strcmp(cmd_list[*instruction_pointer].instruction, "DIV") == 0)
    {
        if (cmd_list[*instruction_pointer].operand == '*')
        {
            int tmp = memory[cmd_list[*instruction_pointer].dest_adress];
            memory[0] /= memory[tmp];
        }
        else if (cmd_list[*instruction_pointer].operand == '=')
        {
            memory[0] /= cmd_list[*instruction_pointer].dest_adress;
        }
        else
            memory[0] /= memory[cmd_list[*instruction_pointer].dest_adress];
    }
    else if (strcmp(cmd_list[*instruction_pointer].instruction, "READ") == 0)
    {
        //TODO additional function to get input values, tho dunno if necessarry 
        if (cmd_list[*instruction_pointer].operand == '*')
        {
            int tmp, addr_tmp;
            fscanf(input_fp, "%d", &tmp);
            addr_tmp = memory[cmd_list[*instruction_pointer].dest_adress];
            memory[addr_tmp] = tmp;
        }
        else if (cmd_list[*instruction_pointer].operand == '*')
        {
            fprintf(stderr, "'=' OPERAND WITH READ INSTRUCTION ERROR");
            exit(EXIT_FAILURE);
        }
        else
        {
            int tmp;
            fscanf(input_fp, "%d", &tmp);
            memory[cmd_list[*instruction_pointer].dest_adress] = tmp;
        }
    }
    else if (strcmp(cmd_list[*instruction_pointer].instruction, "WRITE") == 0)
    {
        //TODO output_tape
        if (cmd_list[*instruction_pointer].operand == '*')
        {
            int tmp;
            tmp = memory[cmd_list[*instruction_pointer].dest_adress];
            printf("OUTPUT:%d\n", memory[tmp]);
        }
        else if (cmd_list[*instruction_pointer].operand == '=')
        {
            printf("OUTPUT:%d\n", cmd_list[*instruction_pointer].dest_adress);
        }
        else
            printf("OUTPUT:%d\n", memory[cmd_list[*instruction_pointer].dest_adress]);
    }
    else if (strcmp(cmd_list[*instruction_pointer].instruction, "HALT") == 0)
    {
        printf("PROGRAM FINISHED");
        exit(EXIT_SUCCESS);
    }
    else
    {
        fprintf(stderr, "WRONG INSTRUCTION ERROR");
        exit(EXIT_FAILURE);
    }

    *instruction_pointer += 1;
    return 0;
}

void loop(Command *cmd_list, size_t cmd_count, FILE *input_fp, int *memory)
{
    Command current_cmd;
    int instruction_pointer = 0;

    while (1)
    {
        printf("current instr pointer:%d\n", instruction_pointer);
        execute_command(cmd_list, cmd_count, &instruction_pointer, input_fp, memory);
    }
}