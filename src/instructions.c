#include "ram_machine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void execute_command(Command *cmd_list, size_t cmd_count, int *instruction_pointer, FILE *input_fp, int **memory)
{
    //ogarnij jaka to komenda
    //jeżeli jest to instrukcja skoku (jump, jzero, jgtz), to skocz do etykiety (zmień licznik komend na ten z etykietą)
    //uzyj do tego funkcji get_matching_label
    //jeśli nie, to wykonaj resztę komend
    //po czym zwiększ licznik komend +1
    //jeśli komenda nie rozpoznana, zakończ program
    if (strcmp(cmd_list[*instruction_pointer].instruction, "JUMP") == 0)
    {
        size_t tmp;
        tmp = get_matching_label(cmd_list, cmd_count,cmd_list[*instruction_pointer]);
        *instruction_pointer = tmp;
        return 0;
    }
    else if (strcmp(cmd_list[*instruction_pointer].instruction, "JZERO") == 0)
    {
        return 0;

    }
    
}

void loop(Command *cmd_list, size_t cmd_count, int *instruction_pointer, FILE *input_fp, int **memory)
{
    return 0;

}