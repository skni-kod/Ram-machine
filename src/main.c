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
    //print_commands(machine.cmd_list, machine.cmd_count);
    fclose(instr_fp);

    machine.memory = init_memory(machine.max_memory_size);

    loop(machine_ptr);


    getchar(); 


    free(machine.memory);
    free(machine.cmd_list);
    fclose(instr_fp);
    fclose(machine.input_fp);
    fclose(machine.output_fp);
    return 0;
}

