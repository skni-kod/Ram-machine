#include <stdlib.h>
#include <stdio.h>
#include "ram_machine.h"

int main()
{
    FILE *fp;
    Command *cmd_list;
    size_t cmd_amount;

    fp = load_file("/home/musiek/Pulpit/Ram-machine/instructions.txt");
    //print_file(fp);

    cmd_list = parse_commands(fp, &cmd_amount);
    
    print_commands(cmd_list, cmd_amount);
    int matching_label_index = get_matching_label(cmd_list, cmd_amount, cmd_list[3]);
    printf("%d", matching_label_index);

    getchar(); 

    free(cmd_list);
    fclose(fp);
    return 0;
}