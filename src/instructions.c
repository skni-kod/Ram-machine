#include "ram_machine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int execute_command(MachineState *machine_ptr)
{
    if (strcmp(machine_ptr->cmd_list[machine_ptr->instruction_pointer].instruction, "JUMP") == 0)
    {
        size_t tmp;
        tmp = machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress;
        machine_ptr->instruction_pointer = tmp;
        return 0;
    }
    else if (strcmp(machine_ptr->cmd_list[machine_ptr->instruction_pointer].instruction, "JZERO") == 0)
    {
        if (load_from_memory(machine_ptr, 0) == 0)
        {
            size_t tmp;
            tmp = machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress;
            machine_ptr->instruction_pointer = tmp;
        }
        else
            machine_ptr->instruction_pointer += 1;

        return 0;
    }
    else if (strcmp(machine_ptr->cmd_list[machine_ptr->instruction_pointer].instruction, "JGTZ") == 0)
    {
        if (load_from_memory(machine_ptr, 0) > 0)
        {
            size_t tmp;
            tmp = machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress;
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
            save_to_memory( machine_ptr, 0,
                            load_from_memory(machine_ptr,
                            machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress));
        }
        else if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '=')
            save_to_memory( machine_ptr,
                            0,
                            machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress);
        else
            save_to_memory( machine_ptr,
                            0, 
                            load_from_memory(machine_ptr, machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress));
    }
    else if (strcmp(machine_ptr->cmd_list[machine_ptr->instruction_pointer].instruction, "STORE") == 0)
    {
        if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '*')
        {
            save_to_memory( machine_ptr, 
                            load_from_memory(machine_ptr, machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress), 
                            load_from_memory(machine_ptr, 0));
        }
        else if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '=')
        {
            fprintf(stderr, "'=' OPERAND WITH STORE INSTRUCTION ERROR");
            exit(EXIT_FAILURE);
        }
        else
            save_to_memory( machine_ptr,
                            machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress,
                            load_from_memory(machine_ptr, 0));
    }
    else if (strcmp(machine_ptr->cmd_list[machine_ptr->instruction_pointer].instruction, "ADD") == 0)
    {
        if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '*')
        {
            int tmp = load_from_memory( machine_ptr,
                                        machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress);
            save_to_memory( machine_ptr,
                            0,
                            load_from_memory(machine_ptr, 0) + tmp);
        }
        else if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '=')
        {
            save_to_memory( machine_ptr,
                            0,
                            load_from_memory(machine_ptr, 0) + machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress);
        }
        else
        {
            int tmp = load_from_memory(machine_ptr, machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress);
            save_to_memory( machine_ptr,
                            0,
                            load_from_memory(machine_ptr, 0) + tmp);
        }
    }
    else if (strcmp(machine_ptr->cmd_list[machine_ptr->instruction_pointer].instruction, "SUB") == 0)
    {
        if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '*')
        {
            int tmp = load_from_memory( machine_ptr,
                                        machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress);
            save_to_memory( machine_ptr,
                            0,
                            load_from_memory(machine_ptr, 0) - tmp);
        }
        else if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '=')
        {
            save_to_memory( machine_ptr,
                            0,
                            load_from_memory(machine_ptr, 0) - machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress);
        }
        else
        {
            int tmp = load_from_memory(machine_ptr, machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress);
            save_to_memory( machine_ptr,
                            0,
                            load_from_memory(machine_ptr, 0) - tmp);
        }
    }
    else if (strcmp(machine_ptr->cmd_list[machine_ptr->instruction_pointer].instruction, "MULT") == 0)
    {
        if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '*')
        {
            int tmp = load_from_memory( machine_ptr,
                                        machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress);
            save_to_memory( machine_ptr,
                            0,
                            load_from_memory(machine_ptr, 0) * tmp);
        }
        else if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '=')
        {
            save_to_memory( machine_ptr,
                            0,
                            load_from_memory(machine_ptr, 0) * machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress);
        }
        else
        {
            int tmp = load_from_memory(machine_ptr, machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress);
            save_to_memory( machine_ptr,
                            0,
                            load_from_memory(machine_ptr, 0) * tmp);
        }
    }
    else if (strcmp(machine_ptr->cmd_list[machine_ptr->instruction_pointer].instruction, "DIV") == 0)
    {
        if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '*')
        {
            int tmp = load_from_memory( machine_ptr,
                                        machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress);
            save_to_memory( machine_ptr,
                            0,
                            load_from_memory(machine_ptr, 0) / tmp);
        }
        else if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '=')
        {
            save_to_memory( machine_ptr,
                            0,
                            load_from_memory(machine_ptr, 0) / machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress);
        }
        else
        {
            int tmp = load_from_memory(machine_ptr, machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress);
            save_to_memory( machine_ptr,
                            0,
                            load_from_memory(machine_ptr, 0) / tmp);
        }
    }
    else if (strcmp(machine_ptr->cmd_list[machine_ptr->instruction_pointer].instruction, "READ") == 0)
    {
        if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '*')
        {
            int addr_tmp = load_from_memory(machine_ptr, 
                                            machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress);
            save_to_memory( machine_ptr,
                            addr_tmp,
                            get_new_input(machine_ptr->input_fp));
        }
        else if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '=')
        {
            fprintf(stderr, "'=' OPERAND WITH READ INSTRUCTION ERROR");
            exit(EXIT_FAILURE);
        }
        else
        {
            save_to_memory( machine_ptr,
                            machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress,
                            get_new_input(machine_ptr->input_fp));
        }
    }
    else if (strcmp(machine_ptr->cmd_list[machine_ptr->instruction_pointer].instruction, "WRITE") == 0)
    {
        if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '*')
        {
            int tmp = load_from_memory(machine_ptr, machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress);
            fprintf(machine_ptr->output_fp, "%d\n", load_from_memory(machine_ptr, tmp));
        }
        else if (machine_ptr->cmd_list[machine_ptr->instruction_pointer].operand == '=')
        {
            fprintf(machine_ptr->output_fp, "%d\n", machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress);
        }
        else
            fprintf(machine_ptr->output_fp, "%d\n", load_from_memory(machine_ptr, machine_ptr->cmd_list[machine_ptr->instruction_pointer].dest_adress));
    }
    else if (strcmp(machine_ptr->cmd_list[machine_ptr->instruction_pointer].instruction, "HALT") == 0)
    {
        //returning -1 will exit the main loop
        printf("\nPROGRAM FINISHED.\n");
        return -1;
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
    machine_ptr->instruction_pointer = 0;
    int work_state = 0;

    while (work_state != -1)
    {
        //TODO printing only as much memory as used
        //print_memory(machine_ptr, machine_ptr->max_used_memory_index);
        //printf("current instr pointer:%d\n", machine_ptr->instruction_pointer);
        work_state = execute_command(machine_ptr);
    }
}