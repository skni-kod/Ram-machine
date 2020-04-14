#include <stdlib.h>
#include <stdio.h>
#include "ram_machine.h"

int main()
{
    FILE *fp;
    fp = load_file("/home/musiek/Pulpit/Ram-machine/instructions.txt");
    print_file(fp);
    printf("%d\n", count_commands(fp));
    fclose(fp);
    getchar();
}