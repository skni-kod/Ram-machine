#include <stdio.h>
#include <stdlib.h>
#include "ram_machine.h"

FILE *load_file(char *file_path)
{
    FILE *fp = fopen(file_path, "r");

    if (fp == NULL)
    {
        fprintf(stderr, "Error loading a file!");
        exit(EXIT_FAILURE);
    }

    return fp;
}

void print_file(FILE *fp)
{
    //TODO dynamic allocation
    int index = 1;
    char buffer[256];
    while (fgets(buffer, 256, fp) != NULL)
    {
        printf("%d: %s", index, buffer);
        index++;
    }
    printf("\n");
    rewind(fp);
}

size_t count_commands(FILE *fp)
{
    size_t amount = 0;
    for (char c = getc(fp); c != EOF; c = getc(fp))
    {
        if (c == ';')
            amount++;
    }
    rewind(fp);
    return amount;
}

struct command **parse_commands(FILE *fp)
{
    struct command **command_list;
    size_t command_amount = count_commands(fp);
    //command_list = (struct command**)malloc(command_amount * sizeof(command*));

}


