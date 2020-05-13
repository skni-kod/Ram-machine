#include "ram_machine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int execute_command(MachineState *machine_ptr)
{
    if (strcmp(machine_ptr->cmd_list[machine_ptr->instruction_pointer].instruction, "JUMP") == 0)
    {
        size_t tmp;
        tmp = get_matching_label(machine_ptr->cmd_list, machine_ptr->cmd_count,machine_ptr->cmd_list[machine_ptr->instruction_pointer]);
        machine_ptr->instruction_pointer = tmp;
        return 0;
    }
    else if (strcmp(machine_ptr->cmd_list[machine_ptr->instruction_pointer].instruction, "JZERO") == 0)
    {
        //if (machine_ptr->memory[0] == 0)
        if (load_from_memory(machine_ptr->memory, 0) == 0)
        {
            size_t tmp;
            tmp = get_matching_label(machine_ptr->cmd_list, machine_ptr->cmd_count, machine_ptr->cmd_list[machine_ptr->instruction_pointer]);
            machine_ptr->instruction_pointer = tmp;
        }
        else
            machine_ptr->instruction_pointer += 1;

        return 0;
    }
    else if (strcmp(machine_ptr->cmd_list[machine_ptr->instruction_pointer].instruction, "JGTZ") == 0)
    {
        //if (machine_ptr->memory[0] > 0)
        if (load_from_memory(machine_ptr->memory, 0) > 0)
        {
            size_t tmp;
            tmp = get_matching_label(machine_ptr->cmd_list, machine_ptr->cmd_count, machine_ptr->cmd_list[machine_ptr->instruction_pointer]);
            machine_ptr->instruction_pointer = tmp;
        }
        else
            machine_ptr->instruction_pointer += 1;

        return 0;
    }
    //end of jump instructions, incrementing ip at the very end of the function
    else if (strcmp(machine_ptr->cmd_list[machine_ptr->instruction_pointer].instruction, "LOAD") == 0)
    {
        if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '*')
        {
            //int tmp = machine_ptr->memory[machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress];
            //machine_ptr->memory[0] = machine_ptr->memory[tmp];
            save_to_memory( machine_ptr->memory, 0,
                            load_from_memory(machine_ptr->memory,
                            machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress));
        }
        else if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '=')
            //machine_ptr->memory[0] = machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress;
            save_to_memory( machine_ptr->memory,
                            0,
                            machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress);
        else
            //machine_ptr->memory[0] = machine_ptr->memory[machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress];
            save_to_memory( machine_ptr->memory,
                            0, 
                            load_from_memory(machine_ptr->memory, machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress));
    }
    else if (strcmp(machine_ptr->cmd_list[machine_ptr->instruction_pointer].instruction, "STORE") == 0)
    {
        if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '*')
        {
            //int tmp = machine_ptr->memory[machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress];
            //machine_ptr->memory[tmp] = machine_ptr->memory[0];
            save_to_memory( machine_ptr->memory, 
                            load_from_memory(machine_ptr->memory, machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress), 
                            load_from_memory(machine_ptr->memory, 0));
        }
        else if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '=')
        {
            fprintf(stderr, "'=' OPERAND WITH STORE INSTRUCTION ERROR");
            exit(EXIT_FAILURE);
        }
        else
            //machine_ptr->memory[machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress] = machine_ptr->memory[0];
            save_to_memory( machine_ptr->memory,
                            machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress,
                            load_from_memory(machine_ptr->memory, 0));
    }
    else if (strcmp(machine_ptr->cmd_list[machine_ptr->instruction_pointer].instruction, "ADD") == 0)
    {
        if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '*')
        {
            //int tmp = machine_ptr->memory[machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress];
            int tmp = load_from_memory( machine_ptr->memory,
                                        machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress);
            save_to_memory( machine_ptr->memory,
                            0,
                            load_from_memory(machine_ptr->memory, 0) + tmp);
            //machine_ptr->memory[0] += machine_ptr->memory[tmp];
        }
        else if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '=')
        {
            //machine_ptr->memory[0] += machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress;
            save_to_memory( machine_ptr->memory,
                            0,
                            load_from_memory(machine_ptr->memory, 0) + machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress);
        }
        else
        {
            //machine_ptr->memory[0] += machine_ptr->memory[machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress];
            int tmp = load_from_memory(machine_ptr->memory, machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress);
            save_to_memory( machine_ptr->memory,
                            0,
                            load_from_memory(machine_ptr->memory, 0) + tmp);
        }
    }
    else if (strcmp(machine_ptr->cmd_list[machine_ptr->instruction_pointer].instruction, "SUB") == 0)
    {
        if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '*')
        {
            int tmp = machine_ptr->memory[machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress];
            machine_ptr->memory[0] -= machine_ptr->memory[tmp];
        }
        else if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '=')
        {
            machine_ptr->memory[0] -= machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress;
        }
        else
            machine_ptr->memory[0] -= machine_ptr->memory[machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress];
    }
    else if (strcmp(machine_ptr->cmd_list[machine_ptr->instruction_pointer].instruction, "MULT") == 0)
    {
        if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '*')
        {
            int tmp = machine_ptr->memory[machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress];
            machine_ptr->memory[0] *= machine_ptr->memory[tmp];
        }
        else if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '=')
        {
            machine_ptr->memory[0] *= machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress;
        }
        else
            machine_ptr->memory[0] *= machine_ptr->memory[machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress];
    }
    else if (strcmp(machine_ptr->cmd_list[machine_ptr->instruction_pointer].instruction, "DIV") == 0)
    {
        if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '*')
        {
            int tmp = machine_ptr->memory[machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress];
            machine_ptr->memory[0] /= machine_ptr->memory[tmp];
        }
        else if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '=')
        {
            machine_ptr->memory[0] /= machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress;
        }
        else
            machine_ptr->memory[0] /= machine_ptr->memory[machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress];
    }
    else if (strcmp(machine_ptr->cmd_list[machine_ptr->instruction_pointer].instruction, "READ") == 0)
    {
        //TODO additional function to get input values, tho dunno if necessarry 
        if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '*')
        {
            int tmp, addr_tmp;
            fscanf(machine_ptr->input_fp, "%d", &tmp);
            addr_tmp = machine_ptr->memory[machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress];
            machine_ptr->memory[addr_tmp] = tmp;
        }
        else if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '=')
        {
            fprintf(stderr, "'=' OPERAND WITH READ INSTRUCTION ERROR");
            exit(EXIT_FAILURE);
        }
        else
        {
            int tmp;
            fscanf(machine_ptr->input_fp, "%d", &tmp);
            machine_ptr->memory[machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress] = tmp;
        }
    }
    else if (strcmp(machine_ptr->cmd_list[machine_ptr->instruction_pointer].instruction, "WRITE") == 0)
    {
        //TODO output_tape
        if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '*')
        {
            int tmp;
            tmp = machine_ptr->memory[machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress];
            printf("OUTPUT:%d\n", machine_ptr->memory[tmp]);
        }
        else if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '=')
        {
            printf("OUTPUT:%d\n", machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress);
        }
        else
            printf("OUTPUT:%d\n", machine_ptr->memory[machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress]);
    }
    else if (strcmp(machine_ptr->cmd_list[machine_ptr->instruction_pointer].instruction, "HALT") == 0)
    {
        printf("PROGRAM FINISHED");
        exit(EXIT_SUCCESS);
    }
    else
    {
        fprintf(stderr, "WRONG INSTRUCTION ERROR");
        exit(EXIT_FAILURE);
    }

    machine_ptr->instruction_pointer += 1;
    return 0;
}

void loop(MachineState *machine_ptr)
{
    //int instruction_pointer = 0;
    machine_ptr->instruction_pointer = 0;

    while (1)
    {
        //temp
        //TODO printing only as much memory as used
        print_memory(machine_ptr->memory, machine_ptr->max_memory_size - 90);
        printf("current instr pointer:%d\n", machine_ptr->instruction_pointer);
        execute_command(machine_ptr);
    }
}