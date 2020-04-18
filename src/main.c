#include "ram_machine.h"
#include <stdlib.h>
#include <stdio.h>

#define mem_size 100

int main()
{
    FILE *instr_fp, *input_fp;
    Command *cmd_list;
    size_t cmd_amount;
    int *memory;
    int instr_ptr = 0;

    //init
    instr_fp = load_file("/home/musiek/Pulpit/Ram-machine/instructions.txt");
    cmd_list = parse_commands(instr_fp, &cmd_amount);
    print_commands(cmd_list, cmd_amount);
    fclose(instr_fp);

    memory = init_memory(mem_size);

    input_fp = load_file("/home/musiek/Pulpit/Ram-machine/input.txt");
    
    getchar(); 

    loop(cmd_list, cmd_amount, &instr_ptr, input_fp, &memory);

    free(memory);
    free(cmd_list);
    return 0;
}