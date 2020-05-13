#include "ram_machine.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    FILE *instr_fp; //*input_fp, *output_fp;
    //Command *cmd_list;
    //size_t cmd_amount;
    //int *memory;
    MachineState machine;
    MachineState *machine_ptr = &machine;
    machine.max_memory_size = 100; //TODO


    //init
    instr_fp = load_file("/home/musiek/Pulpit/Ram-machine/instructions/sumowanie_liczb.txt");
    machine.cmd_list = parse_commands(instr_fp, &(machine_ptr->cmd_count));
    print_commands(machine.cmd_list, machine.cmd_count);
    fclose(instr_fp);


    machine.memory = init_memory(machine.max_memory_size);

    //TODO output_fp
    machine.input_fp = load_file("/home/musiek/Pulpit/Ram-machine/input.txt");
    machine.output_fp = stdout;
    loop(machine_ptr);


    getchar(); 


    free(machine.memory);
    free(machine.cmd_list);
    fclose(instr_fp);
    fclose(machine.input_fp);
    return 0;
}