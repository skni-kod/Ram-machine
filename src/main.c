#include "ram_machine.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    FILE *instr_fp, *input_fp;
    Command *cmd_list;
    size_t cmd_amount;
    int *memory;
    

    //init
    instr_fp = load_file("/home/musiek/Pulpit/Ram-machine/instructions/test3.txt");
    cmd_list = parse_commands(instr_fp, &cmd_amount);
    print_commands(cmd_list, cmd_amount);
    fclose(instr_fp);

    memory = init_memory(MEM_SIZE);

    input_fp = load_file("/home/musiek/Pulpit/Ram-machine/input.txt");
    
    loop(cmd_list, cmd_amount, input_fp, memory);


    //getchar(); 


    free(memory);
    free(cmd_list);
    return 0;
}