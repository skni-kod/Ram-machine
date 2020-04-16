#include <stdlib.h>
#include <stdio.h>
#include "ram_machine.h"

int main()
{
    FILE *fp;
    Command *command_list;
    fp = load_file("/home/musiek/Pulpit/Ram-machine/instructions.txt");
    print_file(fp);
    printf("%d\n", count_commands(fp));

    command_list = parse_commands(fp);

    getchar();
    
    free(command_list);

    fclose(fp);
    return 0;
}