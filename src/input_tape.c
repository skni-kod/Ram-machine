#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

struct Command *parse_commands(FILE *fp)
{
    struct Command *command_list;
    size_t cmd_amount = count_commands(fp);
    size_t line_counter = 0;
    char buffer[256];
    char *token;

    command_list = malloc(cmd_amount * sizeof(Command));

    while (line_counter < cmd_amount)
    {
        //printf("line_counter:%d", line_counter);
        //first word loaded flag
        int struct_counter = 0;
        int flag = 0;
        fgets(buffer, 256, fp);
        
        if (flag == 0)
        {
            token = strtok(buffer, ",");
        }
        
        while (token != NULL){
                        
            if (flag != 0)
            {
                token = strtok(NULL, ",\n");
                if (token == NULL)
                    continue;
            }

            printf("%s ", token);

            //wyszukiwanie końca linii
            //nie wiem czy potrzebne
            for (int i = 0; i < strlen(token); i++)
            {
                if (token[i] == ';')
                    printf("KONIEC\n");
            }

            switch (struct_counter)
            {
                //index
                case (0):
                    command_list[line_counter].cmd_index = line_counter + 1;
                    break;
                //label
                case (1):
                    strcpy(command_list[line_counter].label, token);
                    break;
                //instruction
                case (2):
                    strcpy(command_list[line_counter].instruction, token);
                    break;
                //operator
                case (3):
                    command_list[line_counter].operator = token;
                    break;
                //destination adress
                case (4):
                    command_list[line_counter].dest_adress = token;
                    break;
            }
            

            flag = 1;
            struct_counter++;
        }
        line_counter++;
    }
    

    return command_list;
}


