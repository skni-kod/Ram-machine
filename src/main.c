#include "ram_machine.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    FILE *instr_fp; 
    MachineState machine;
    MachineState *machine_ptr = &machine;

    parse_arguments(machine_ptr, argc, argv, &instr_fp);

    machine.cmd_list = parse_commands(instr_fp, &(machine_ptr->cmd_count));
    fclose(instr_fp);

    printf("\n");

    //print_commands(machine.cmd_list, machine.cmd_count);

    machine.memory = init_memory(machine.max_memory_size);
    machine.max_used_memory_index = 0;

    loop(machine_ptr);


    free(machine.memory);
    free(machine.cmd_list);
    fclose(machine.input_fp);
    fclose(machine.output_fp);
    return 0;
}

