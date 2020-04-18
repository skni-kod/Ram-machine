#include "ram_machine.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    FILE *fp;
    Command *cmd_list;
    size_t cmd_amount;
    int *memory;
    size_t mem_size = 100;

    fp = load_file("/home/musiek/Pulpit/Ram-machine/instructions.txt");
    cmd_list = parse_commands(fp, &cmd_amount);
    fclose(fp);

    memory = init_memory(mem_size);
    save_to_memory(&memory, 0, 5);
    save_to_memory(&memory, 1, 15);

    print_memory(&memory, mem_size);
    printf("loaded:%d\n", load_from_memory(&memory, 1));
    getchar(); 

    free(cmd_list);
    free(memory);
    return 0;
}