#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ram_machine.h"

FILE *load_file(char *file_path)
{
    FILE *fp = fopen(file_path, "r");

    if (fp == NULL)
    {
        fprintf(stderr, "Error loading a file!\n");
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

struct Command *parse_commands(FILE *fp, size_t *cmd_amount)
{
    //TODO dynamically allocated line reading
    //TODO dynamically allocated structures
    struct Command *command_list;
    size_t line_counter = 0;
    char buffer[256];
    char *token;

    *cmd_amount = count_commands(fp);
    command_list = malloc(*cmd_amount * sizeof(Command));

    while (line_counter < *cmd_amount)
    {   int flag = 0;
        int cmd_counter = 0;

        command_list[line_counter].cmd_index = line_counter;
        fgets(buffer, 256, fp);
        token = strtok(buffer, ",\n");

        while (flag != 1)
        {
            //switch filling the cmd struct up
            switch (cmd_counter)
            {
                case (0):
                    strcpy(command_list[line_counter].label, token);
                    break;
                case (1):
                    strcpy(command_list[line_counter].instruction, token);
                    break;
                case (2):
                    command_list[line_counter].operator = token[0];
                    break;
                case (3): ;
                    size_t tmp = -1;

                    sscanf(token, "%d", &tmp);
                    command_list[line_counter].dest_adress = tmp;
                    break;
            }

            //searching for EOL
            for (int i = 0; i < strlen(token); i++)
            {
                if (token[i] == ';')
                {
                    flag = 1;
                    break;
                }
            }

            token = strtok(NULL, ",\n"); 
            cmd_counter++;
        }

        line_counter++;
    }
    
    rewind(fp);
    return command_list;
}

void print_commands(Command *cmd_list, size_t cmd_count)
{
    for (int i = 0; i < cmd_count; i++)
    {
        printf("index:%d\n", cmd_list[i].cmd_index);
        printf("label:%s\n", cmd_list[i].label);
        printf("instruction:%s\n", cmd_list[i].instruction);
        printf("operator:%c\n", cmd_list[i].operator);
        printf("dest_adress:%i\n", cmd_list[i].dest_adress);
        printf("\n");
    }
}

size_t get_matching_label(Command *cmd_list, size_t cmd_count, Command cmd)
{
    for (int i = 0; i < cmd_count; i++)
    {
        if (i != cmd.cmd_index && strcmp(cmd.label, cmd_list[i].label) == 0)
            return i;
    }
    //matching label not found means that the program itself has to be wrong
    fprintf(stderr, "Error while searching for a matching \"%s\" label:matching label not found!\n", cmd.label);
    exit(EXIT_FAILURE);
}