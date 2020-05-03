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
    else if (strcmp(cmd_list[*instruction_pointer].instruction, "JGZT") == 0)
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
    //get HALT on the end
    else if (strcmp(cmd_list[*instruction_pointer].instruction, "HALT") == 0)
    {
        printf("KONIEC PROGRAMU");
        exit(EXIT_SUCCESS);
    }
    //end of jump instructions, incrementing ip at the very end of the function
    else if (strcmp(cmd_list[*instruction_pointer].instruction, "LOAD") == 0)
    {
        memory[0] = memory[cmd_list[*instruction_pointer].dest_adress];
    }
    else if (strcmp(cmd_list[*instruction_pointer].instruction, "STORE") == 0)
    {
        memory[cmd_list[*instruction_pointer].dest_adress] = memory[0];
    }
    //add operands
    else if (strcmp(cmd_list[*instruction_pointer].instruction, "ADD") == 0)
    {
        memory[0] += memory[cmd_list[*instruction_pointer].dest_adress];
    }
    else if (strcmp(cmd_list[*instruction_pointer].instruction, "SUB") == 0)
    {
        memory[0] -= memory[cmd_list[*instruction_pointer].dest_adress];
    }
    else if (strcmp(cmd_list[*instruction_pointer].instruction, "MULT") == 0)
    {
        memory[0] *= memory[cmd_list[*instruction_pointer].dest_adress];
    }
    else if (strcmp(cmd_list[*instruction_pointer].instruction, "DIV") == 0)
    {
        memory[0] /= memory[cmd_list[*instruction_pointer].dest_adress];
    }
    else if (strcmp(cmd_list[*instruction_pointer].instruction, "READ") == 0)
    {
        int tmp;
        fscanf(input_fp, "%d", &tmp);
        memory[cmd_list[*instruction_pointer].dest_adress] = tmp;
    }
    else if (strcmp(cmd_list[*instruction_pointer].instruction, "WRITE") == 0)
    {
        printf("OUTPUT:%d\n", memory[cmd_list[*instruction_pointer].dest_adress]);
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
        //current_cmd = cmd_list[*instruction_pointer];
        execute_command(cmd_list, cmd_count, &instruction_pointer, input_fp, memory);
        
    }
}