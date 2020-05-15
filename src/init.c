#include "ram_machine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_arguments(MachineState *machine_ptr, int argc, char *argv[], FILE **instr_fp)
{
    int memory_flag = 0;
    int input_flag = 0;
    int output_flag = 0;
    int code_flag = 0;
    char cwd[256];


    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        fprintf(stderr, "Error:getcwd() error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        if (strlen(cwd) >= 255)
        {
            fprintf(stderr, "Error:cwd maximum size exceeded!\n");
            exit(EXIT_FAILURE); 
        }
        //strcat(cwd, "/");
        printf("cwd:%s/\n", cwd);
    }

    if (argc % 2 != 1)
    {
        fprintf(stderr, "Error: wrong argument count!\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-code") == 0 && (i+1) < argc)
        {
            char *tmp = malloc(sizeof(cwd) + sizeof(argv[i+1]));
            snprintf(tmp, strlen(cwd) + strlen(argv[i+1]) + 2, "%s%s", cwd, argv[i+1]);
            printf("code path:%s\n", tmp);
            *instr_fp = load_file(tmp);
            free(tmp);
            if (*instr_fp == NULL)
            {
                fprintf(stderr, "Error:unable to open code file!\n");
                exit(EXIT_FAILURE);
            }
            code_flag = 1;
        }
        else if (strcmp(argv[i], "-input") == 0 && (i+1) < argc)
        {
            char *tmp = malloc(sizeof(cwd) + sizeof(argv[i+1]));
            snprintf(tmp, strlen(cwd) + strlen(argv[i+1]) + 2, "%s%s", cwd, argv[i+1]);
            printf("input path:%s\n", tmp);
            machine_ptr->input_fp = load_file(tmp);
            free(tmp);
            if (machine_ptr->input_fp == NULL)
            {
                fprintf(stderr, "Error:unable to open input file!\n");
                exit(EXIT_FAILURE);
            }
            input_flag = 1;
        }
        else if (strcmp(argv[i], "-output") == 0 && (i+1) < argc)
        {
            if (strcmp(argv[i+1], "stdout") == 0)
            {
                machine_ptr->output_fp = stdout;
            }
            else
            {
                char *tmp = malloc(sizeof(cwd) + sizeof(argv[i+1]));
                snprintf(tmp, strlen(cwd) + strlen(argv[i+1]) + 2, "%s%s", cwd, argv[i+1]);
                printf("output path:%s\n", tmp);
                machine_ptr->output_fp = load_output_file(tmp);
                free(tmp);
                if (machine_ptr->output_fp == NULL)
                {
                    fprintf(stderr, "Error:unable to open output file!\n");
                    exit(EXIT_FAILURE);
                }
            }
            output_flag = 1;
        }
        else if (strcmp(argv[i], "-registers") == 0 && (i+1) < argc)
        {
            int tmp;
            sscanf(argv[i+1], "%d", &tmp);
            printf("registers:%d\n", tmp);
            machine_ptr->max_memory_size = tmp;
            memory_flag = 1;
        }
    }
    
    if (code_flag == 0)
    {
        fprintf(stderr, "Error:no code file provided!\n");
        exit(EXIT_FAILURE);
    }
    if (input_flag == 0)
    {
        fprintf(stderr, "Error:no input file provided!\n");
        exit(EXIT_FAILURE);
    }
    if (output_flag == 0)
    {
        printf("No output file provided. Setting the output to stdout.\n");
        machine_ptr->output_fp = stdout;
    }
    if (memory_flag == 0)
    {
        printf("No register count provided. Setting the register count to 100.\n");
        machine_ptr->max_memory_size = 100;
    }
}
